file_name = 'test.txt'

def tokenise(code):
    print(code)
    
    
def compile(file_name):
    with open(file_name, 'r') as file:
        tokens = tokenise(file.read())

def main():
    compile(file_name)
    
if __name__ == '__main__':
    main()