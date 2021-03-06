with open("line_separated_grammar.txt","r") as f:
	lines = f.read().splitlines()

def write_line(f,line):
	f.write(line)
	f.write("\n")
	return

def usefull(string):
	if string == "":
		return False
	else:
		return True

def clean(x):
	return x.strip()

with open("line_numbered_grammar_normal.txt",'w') as f:	
	for i,line in enumerate(lines):
		lhs,rhs = map(clean,line.split("->"))
		write_line(f,str(i + 1))
		write_line(f,str(lhs))
		rhs_terms = filter(usefull,rhs.split(" "))
		write_line(f,str(len(rhs_terms)))
		for term in rhs_terms:
			write_line(f,str(term))

with open("line_numbered_grammar_reverse.txt",'w') as f:	
	for i,line in enumerate(lines):
		lhs,rhs = map(clean,line.split("->"))
		write_line(f,str(i + 1))
		write_line(f,str(lhs))
		rhs_terms = filter(usefull,rhs.split(" "))
		write_line(f,str(len(rhs_terms)))
		rhs_terms.reverse()
		for term in rhs_terms:
			write_line(f,str(term))
