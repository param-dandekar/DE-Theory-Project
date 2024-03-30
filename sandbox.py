unary = [['increment', '++', 'x -> x+1', 'post'],
         ['decrement', '--', 'x -> x-1', 'post'],
         ['negate', '-', 'x -> -x', 'pre'], 
]

binary = [['add', '+', 'x, y -> x+y', 'in'],
          ['subtract', '-', 'x, y -> x-y', 'in'],
          ['assign', '=', 'Assignment', 'in'],
          ['goto', '?', 'GOTO', 'in'],
]

for operator in unary:
    print(operator)
    