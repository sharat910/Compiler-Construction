f2 = open("line_numbered_grammar_normal1.txt",'w')

with open("line_numbered_grammar_reverse1.txt",'r') as f:
	while True:
		line_no = f.readline()
		if line_no == "#":
			break
		f2.write(line_no)
		lhs = f.readline()
		f2.write(lhs)
		num_rhs = int(f.readline())
		f2.write(str(num_rhs)+"\n")
		rhs = []
		for i in range(num_rhs):
			rhs.append(f.readline())
		rhs.reverse()
		for item in rhs:
			f2.write(item)