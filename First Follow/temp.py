with open("temp.txt", "r") as f:
	tokens = map(lambda x: x.split(" ")[1],f.read().splitlines())
	tokens = set(tokens)

seta = set(['REAL', 'USE', 'WITH', 'BC', 'DEFAULT', 'BO', 'WHILE', 'PROGRAM', 'PRINT', 'MUL', 'DIV', 'TRUE', 'MINUS', 'DEF', 'CASE', 'ENDDEF', 'LE', 'SQBO', 'PARAMETERS', 'SWITCH', 'SQBC', 'GET_VALUE', 'NE', 'DECLARE', 'LT', 'NUM', 'COMMA', 'COLON', 'ARRAY', 'PLUS', '@', 'IN', 'GT', 'END', 'TAKES', 'FOR', 'RANGEOP', 'DRIVER', 'MODULE', 'START', 'RETURNS', 'INTEGER', 'INPUT', 'EQ', 'ID', 'AND', 'ASSIGNOP', 'FALSE', 'OF', 'SEMICOL', 'GE', 'BREAK', 'BOOLEAN', '->', 'OR', 'RNUM'])

print seta - tokens