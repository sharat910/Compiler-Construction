import glob

filenames = glob.glob("*")

def line_prepender(filename, line):
    with open(filename, 'r+') as f:
        content = f.read()
        f.seek(0, 0)
        f.write(line.rstrip('\r\n') + '\n' + content)

headers = filter(lambda x: ".h" in x,filenames)
cfiles = filter(lambda x: ".c" in x,filenames)

for file in list(headers)+list(cfiles):
	line_prepender(file,"\n\n")
	line_prepender(file,"// M Sharat Chandra (2014A7PS108P)")
	line_prepender(file,"// Rishabh Garg (2014A7PS065P)")
	line_prepender(file,"// Group 56")
