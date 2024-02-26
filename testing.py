from old.processor import Processor, assemble

p = Processor()

def show():
    p.display('ABIJXMFP', bus=True)
    print()

program_file = 'test_program'

assemble(program_file)
with open(f'{program_file}.bin', 'rb') as f:
    p.load_program(f)
    pass

show()
p.cycle()
show()
p.cycle()
show()
p.cycle()
show()
# print(p._memory)

# CYCLE IS NOT WORKING


