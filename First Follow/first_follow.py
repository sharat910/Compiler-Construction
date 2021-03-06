from copy import deepcopy

rules = []  # Raw grammar rules

def usefull(string):
    if string == "":
        return False
    else:
        return True

def non_term_appender(dict, nonterminals):
    for nt in nonterminals:
        dict[nt] = set()

def is_non_term(symbol):
    if symbol[0] == '<' and symbol[-1] == '>' :
        return True 
    else:
        return False

def get_first(symbol):
    if is_non_term(symbol):
        return firsts_dict[symbol]
    else:
        return symbol

def compare_dicts(dic1,dic2):
    #Initial case
    if dic1 == None:
        return False
    keys = dic2.keys()
    for key in keys:
        if dic1[key] != dic2[key]:
            return False
    return True

bigarr = []
fwarr = []
with open("line_separated_grammar.txt", "r") as fp:
    lines = fp.read().splitlines()
    for line in lines:
        arr = map(lambda x: x.strip(),line.strip().split(' '))
        arr = filter(usefull, arr)
        bigarr += arr
        fwarr.append(arr[0])
        rules.append(arr)

terminals = set(filter(lambda x: not is_non_term(x),bigarr))

nonterminals = set(fwarr)

with open("non-terminals.txt","w") as f:
    for nt in nonterminals:
        f.write(str(nt) + "\n")

with open("terminals.txt","w") as f:
    for nt in terminals:
        f.write(str(nt) + "\n")

# ++++++    Following code is used to find firsts   +++++++++

firsts_dict = {}
non_term_appender(firsts_dict, nonterminals)

for rule in rules: 
    if not is_non_term(rule[2]):
        firsts_dict[rule[0]].add(rule[2])

# with open("firsts_prelim.txt", "w") as f:
#     for key in nonterminals:
#         f.write("%s: %s\n" % (str(key),str(list(firsts_dict[key]))))

oldfirsts_dict = None
while(not compare_dicts(oldfirsts_dict,firsts_dict)):
    print "ll"
    oldfirsts_dict = deepcopy(firsts_dict)
    for rule in rules:
        print rule
        if is_non_term(rule[2]):
            i = 2            
            while i<len(rule) and 'e' in get_first(rule[i]) and (not isinstance(get_first(rule[i]),basestring)):
                firsts_dict[rule[0]] = firsts_dict[rule[0]] | (get_first(rule[i]))
                i += 1
            if i != len(rule):
                if isinstance(get_first(rule[i]),basestring):
                    firsts_dict[rule[0]].add(get_first(rule[i]))
                else:
                    firsts_dict[rule[0]] = firsts_dict[rule[0]] | (get_first(rule[i]))


with open("firsts.txt", "w+") as wp:
    for k in firsts_dict:
        wp.write("first(%s): \t " % k)
        wp.write("%s\n" % ", ".join(list(firsts_dict[k])))


# ++++++    Following code is used to find the follows  ++++++

followdict = {}
oldfollowdict = None
non_term_appender(followdict,nonterminals)

while(not compare_dicts(oldfollowdict,followdict)):
    oldfollowdict = deepcopy(followdict)
    for rule in rules:
        lhs = rule[0]
        rhs = rule[2:]
        if lhs == "<program>":
            followdict[lhs].add('$')
        for nt in nonterminals:
            if nt in rhs:
                nt_index = list(rhs).index(nt)
                if nt_index == (len(rhs) - 1):
                    followdict[nt] = followdict[lhs] | followdict[nt]
                else:
                    if 'e' in get_first(rhs[nt_index+1]):
                        followdict[nt] = followdict[lhs] | followdict[nt]
                    if isinstance(get_first(rhs[nt_index+1]),basestring):
                        followdict[nt].add(get_first(rhs[nt_index+1]))
                    else:
                        followdict[nt] = set(get_first(rhs[nt_index+1])) - set(['e']) | followdict[nt]


with open("follows.txt", "w+") as wp:
    for k in followdict:
        wp.write("follow(%s): \t" % k)
        wp.write("%s\n" % ", ".join(list(followdict[k])))