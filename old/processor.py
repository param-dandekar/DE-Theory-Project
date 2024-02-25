from dataclasses import dataclass
from numpy import int8, int16
from time import sleep

CLK_TIME = 1

@dataclass
class Register:
    _data: int8
    _WE: bool # write enable
    _RE: bool # read enable

    def __init__(self):
        self._data = 0x00
        self._WE = False
        self._RE = False

    def load(self):
        self._WE = True

    def enable(self):
        self._RE = True

    @property
    def zero(self) -> bool:
        return not self._data
    
    @property
    def data(self) -> int8:
        return self._data
    
    @data.setter
    def data(self, val):
        self._data = val
    
    def inc(self):
        self._data += 1
        
    def check_bit(self, n) -> bool:
        return bool((self._data >> n) & 1)

    def set_bit(self, n):
        self._data |= 1<<n
        
    def reset_bit(self, n):
        self._data &= (1<<n)^0b1111
    
    
class Processor:
    _reg_A: Register
    _reg_B: Register
    _reg_C: Register
    _reg_L: Register
    _reg_M: Register
    _addr: Register
    _ins_code: Register
    _ins_data: Register
    _prog_ctr: Register
    _flags: Register

    _registers = dict[str, Register]

    _bus: int8
    _clock: int

    _memory: list[int8]
    _program: list[int8]

    instructions: dict[str, int8]
    instructions = {'NOP': 0x0,
                    'LDA': 0x1,
                    'LDB': 0x2,
                    'LDC': 0x3,
                    'LDIA': 0x4,
                    'LDIB': 0x5,
                    'LDIC': 0x6,
                    'STA': 0x7,
                    'STB': 0x8,
                    'STC': 0x9,
                    'ADD': 0xA,
                    'SUB': 0xB,
                    'JMP': 0xC,
                    'JMPZ': 0xD,
                    'SWP': 0xE,
                    'SWPC': 0xF
                    }

    def __init__(self):
        self._reg_A = Register()
        self._reg_B = Register()
        self._reg_C = Register()
        self._reg_L = Register()
        self._reg_M = Register()
        self._addr = Register()
        self._ins_code = Register()
        self._ins_data = Register()
        self._prog_ctr = Register()
        self._flags = Register()

        self._registers = {'A': self._reg_A,
                           'B': self._reg_B,
                           'C': self._reg_C,
                           'L': self._reg_L,
                           'M': self._reg_M,
                           'X': self._addr,
                           'I': self._ins_code,
                           'J': self._ins_data,
                           'P': self._prog_ctr,
                           'F': self._flags
                           }

        self._bus = 0x00
        self._clock = 0
        self._program = []
        self._memory = [0 for i in range(0xFF)]

        self.update_ALU()
        self.update_flags()
    
    def check_flag(self, n) -> bool:
        return self._flags.check_bit(n)

    def set_flag(self, n):
        self._flags.set_bit(n)

    def reset_flag(self, n):
        self._flags.reset_bit(n)

    def write_from_bus(self):
        for register in self._registers.values():
            if register._WE:
                register.data = self._bus
                register._WE = False
    
    def read_to_bus(self):
        for register in self._registers.values():
            if register._RE:
                self._bus = register.data
                register._RE = False
    
    def load_program(self, program_file):
        program = program_file.read()
        for instruction in program:
            # print(instruction, end=' ')
            self._program.append(instruction)
        print(self._program)

    def IC(self): self.set_flag(4); self.cycle()          # Sel advance counter flag

    def SU(self): self.set_flag(3); self.cycle()         # Set subtraction flag

    def ZE(self):
        if self.check_flag(0): self._prog_ctr.load(); self.cycle()      # Read to program counter if zero flag is set

    def RA(self): self._reg_A.enable(); self.cycle()     # Read from register A to bus
    def RB(self): self._reg_B.enable(); self.cycle()     # Read from register B to bus
    def RC(self): self._reg_C.enable(); self.cycle()     # Read from register C to bus
    def RM(self): self._reg_M.enable(); self.cycle()     # Read from memory refister to bus
    def RI(self): self._ins_data.enable(); self.cycle()   # Read from lower byte of instruction register to bus
    def RX(self): self._addr.enable(); self.cycle()      # Read from address register to bus
    def RL(self): self._reg_L.enable(); self.cycle()     # Read from sum register to bus

    def WA(self): self._reg_A.load(); self.cycle()       # Read from bus to register A
    def WB(self): self._reg_B.load(); self.cycle()       # Read from bus to register B
    def WC(self): self._reg_C.load(); self.cycle()       # Read from bus to register C
    def WM(self): self._reg_M.load(); self.cycle()       # Read from bus to memory register
    def WX(self): self._addr.load(); self.cycle()        # Read from bus to address register
    def WP(self): self._prog_ctr.load(); self.cycle()    # Read from bus to program counter

    def NOP(self): self.IC()
    def LDA(self): self.RI(); self.WX(); self.RM(); self.WA(); self.IC()
    def LDB(self): self.RI(); self.WX(); self.RM(); self.WB(); self.IC()
    def LDC(self): self.RI(); self.WX(); self.RM(); self.WC(); self.IC()
    def LDIA(self): self.RI(); self.WA(); self.IC(); print('LOAD IMM TO A')
    def LDIB(self): self.RI(); self.WB(); self.IC()
    def LDIC(self): self.RI(); self.WC(); self.IC()
    def STA(self): self.RI(); self.WX(); self.RA(); self.WM(); self.IC(); print('STORE FROM A')
    def STB(self): self.RI(); self.WX(); self.RB(); self.WM(); self.IC()
    def STC(self): self.RI(); self.WX(); self.RC(); self.WM(); self.IC()
    def ADD(self): self.RL(); self.WA(); self.IC(); print('ADD')
    def SUB(self): self.SU(); self.RL(); self.WA(); self.IC()
    def JMP(self): self.RI(); self.WP()
    def JMPZ(self): self.IC(); self.RI(); self.ZE()
    def SWP(self): self.RA(); self.WX(); self.RB(); self.WA(); self.RX(); self.WB(); self.IC()
    def SWPC(self): self.RA(); self.WX(); self.RC(); self.WA(); self.RX(); self.WC(); self.IC()

    def update_flags(self):
        if self._reg_A.check_bit(7):
            self.set_flag(3)
        else:
            self.reset_flag(3)
        
        if self._reg_A.zero:
            self.set_flag(0)
        else:
            self.reset_flag(0)
            
        self.reset_flag(4)

    def update_ALU(self):
        sub = 0xFF if self.check_flag(3) else 0x00
        addend = self._reg_B.data ^ sub
        s = self._reg_A.data + addend + self.check_flag(1)
        self._reg_L.data = s & 0xFF
        carry = s >> 8
        if carry:
            self.set_flag(1)
        else:
            self.reset_flag(1)

    def fetch(self):
        try:
            code = self._ins_code.data = self._program[self._prog_ctr.data]
            self._prog_ctr.inc()
            ins = self._ins_data.data = self._program[self._prog_ctr.data]
            self._prog_ctr.inc()
            return 0
        except IndexError as e:
            return 1

    def decode(self):
        ins = self._ins_code.data
        
        if ins == 0x0: self.NOP()
        if ins == 0x1: self.LDA()
        if ins == 0x2: self.LDB()
        if ins == 0x3: self.LDC()
        if ins == 0x4: self.LDIA()
        if ins == 0x5: self.LDIB()
        if ins == 0x6: self.LDIC()
        if ins == 0x7: self.STA()
        if ins == 0x8: self.STB()
        if ins == 0x9: self.STC()
        if ins == 0xA: self.ADD()
        if ins == 0xB: self.SUB()
        if ins == 0xC: self.JMP()
        if ins == 0xD: self.JMPZ()
        if ins == 0xE: self.SWP()
        if ins == 0xF: self.SWPC()

    def execute(self):
        self.update_ALU()

        self.write_from_bus()
        self.read_to_bus()

        self.update_flags()
        self._reg_M.data = self._memory[self._addr.data]

    def cycle(self):
        fetch_fail = False
        if self.check_flag(4):
            fetch_fail = self.fetch()
        if fetch_fail:
            raise RuntimeError
        
        self._clock += 1

        if self._clock > 20:
            raise RuntimeError

        self.display('ABIJXMFP', bus=True)
        print()

        self.decode()
        self.execute()

        return 0
    
    def display(self, registers, bus=False):
        print('\r| ', end='')
        for register in registers:
            data = f'{self._registers[register]._data & 0b1111:04b}' if register == 'F' else f'{self._registers[register]._data:02X}'
            print(f'{ register:}: {data} | ', end='')
        print(f'--- | Clock: {self._clock:05d}', end='')
        if bus:
            print(f' | Bus: {self._bus:08b}', end='')
            
    def display_all(self):
        self.display('ABCLXMFIJP', bus=True)
    
    def load_ins_data(self, data):
        self._ins_data.data = data

def assemble(program_file: str, ext: str = 'txt'):
    with open(f'{program_file}.{ext}', 'r') as input:
        with open(f'{program_file}.bin', 'bw') as output:
            for line in input.readlines():
                ins, *op = line.strip().split()
                data = 0x0 if not op else int(op[0])
                code = Processor.instructions[ins]
                output.write(code.to_bytes())
                output.write(data.to_bytes())
