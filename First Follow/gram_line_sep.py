with open("grammar.txt","r") as f:
	lines = f.read().splitlines()

def usefull(string):
	if string == "":
		return False
	else:
		return True

lines = filter(usefull,lines)

def write_line(f,line):
	f.write(line)
	f.write("\n")
	return

with open("ggrammar.txt",'w') as f:	
	for line in lines:
		if "|" in line:
			lhs,rhs = line.split("->")
			sep_lines = rhs.split("|")
			for l in sep_lines:
				write_line(f,lhs+ "->"+l)
		else:
			write_line(f,line)			
