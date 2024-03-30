file_name = 'test.txt'

operators = {
    '+': 'add',
    '-': 'subtract',
    '==': 'equal',
    '!=': 'not_equal',
    }

actions = {
    'unary': {
        '++': 'increment',
        '--': 'decrement',
        '<-': 'label',
        },
    'binary': {
        '=': 'assign',
        '?': 'goto',
    }
}

class Expression:
    operation: str
    operands: list
    
    def __init__(self, *opds, opn=None) -> None:
        self.operation = opn
        self.operands = opds
    
    def __repr__(self) -> str:
        return str(self)
    
    def __str__(self) -> str:
        if self.operation:
            string_rep = f"""Expression:
operation: "{self.operation}",
operands: [{self.operands}]"""

        else: 
            string_rep = f'Expression: {self.operands[0]}'
            
        return string_rep
        
class Statement:
    LHS: str
    expression: Expression
    action: str
    
    def __init__(self, LHS, expr, action) -> None:
        self.LHS = LHS
        self.expr = expr
        self.action = action
    
    def __repr__(self) -> str:
        return str(self)
    
    def __str__(self) -> str:
        if self.LHS:
            string_rep = f"""Statement:
LHS: "{self.LHS}",
expression:
{self.expr},
action: {self.action}"""
        else:
            string_rep = f"""Statement:
expression: {self.expr},
action: {self.action}"""
        return string_rep
        
def parse_expr(expr: list) -> Expression:
    if len(expr) == 1:
        expr = expr[0]
        
    
    stack = []
    expression = []
    
    for element in expr:
        if element in operators:
            operands = stack
            if expression: operands.append(expression)
            expression = Expression(*operands, opn=element)
        else:
            stack.append(element)
    
    if not expression: expression = Expression(*stack)
            
    return expression

def read_and_format(raw_code: str) -> list:
    raw_code = raw_code.replace('\n', '')
    raw_code = raw_code.replace('{', ';').replace('}', ';')
    code = raw_code.split(';')
    return code

def get_program(code: list[str]) -> dict[str, list]:
        program = {
            'VARS': [],
            'FUNC': [],
            'MAIN': []
            }
        
        current_section = ''
        for line in code:
            if line.strip() == 'VARS':
                current_section = line.strip()
            elif line.strip() == 'FUNC':
                current_section = line.strip()
            elif line.strip() == 'MAIN':
                current_section = line.strip()
            
            else:
                statement = parse_line(line)
                if statement:
                    program[current_section].append(statement)
        
        return program

def parse_line(line: str):
    if not line:
        return None
    parts = line.split()
    
    statement = []
    
    for action in actions['unary']:
        if action in parts:
            label = parts[1]
            return Statement(None, parse_expr(label), actions['unary'][action])
        
    for action in actions['binary']:
        if action in parts:
            LHS = parts[0]
            RHS = parts[2:]
            return Statement(LHS, parse_expr(RHS), actions['binary'][action])
    
    return parse_expr(parts)

def compile(file_name):
    with open(file_name, 'r') as file:
        code = read_and_format(file.read())
        
        program = get_program(code)
        
        
        for line in program['VARS']:
            print(line)
        
def main():
    compile(file_name)
    
if __name__ == '__main__':
    main()