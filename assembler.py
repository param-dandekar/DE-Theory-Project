import sys 

mnemonic_to_code_file = 'mnemonic_to_code.txt'

def get_codes():
    with open(mnemonic_to_code_file, 'r') as file:
        lines = map(
            lambda line:
                list(
                    map(
                        # Getting each line, stripping it, and splitting it by column
                        lambda el: el.strip(),
                        line.strip().split('|')
                    )
                )[1:3], # We only want columns 1 and 2
            file.readlines()[2:]
            )
        
    # Returning dict with the conversions
    return {line[1]: line[0] for line in lines}

def assemble(in_file_name: str, out_file_name: str):
    with open(in_file_name, 'r') as in_file:
        
        # Getting each line, stripping it, and splitting it by spaces
        lines = map(
            lambda line: line.strip().split(),
            in_file.readlines()
            )
        
        # Adding a null operand when it is not specified
        lines = [(line + [None] * (2-len(line))) for line in lines]
        
        conversion = get_codes()
        
        # Making a JSONesque object to store the instructions
        instructions = []
        for line in lines:
            try:
                instructions += [{'mnemonic': line[0], 'operand': line[1], 'code': conversion[line[0]]}]
            except KeyError as e:
                print('error:', line)
        
        with open(out_file_name, 'wb') as out_file:
            for instruction in instructions:
                # print(instruction)
                code = int(instruction['code'], 16)
                operand = int(instruction['operand'], 16)
                out_file.write(code.to_bytes())
                out_file.write(operand.to_bytes())
                
                
        
def main():
    # in_file_name = sys.argv[1]
    in_file_name = 'program.txt'
    
    try:
        out_file_name = sys.argv[2]
    except IndexError:
        # If the output file name is not specified, change the extension to .bin
        out_file_name = ''.join(in_file_name.split('.')[:-1])+'.bin'
    assemble(in_file_name, out_file_name)

if __name__ == '__main__':
    main()