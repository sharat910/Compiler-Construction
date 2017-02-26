##ifndef _parser
#define _parser


FirstAndFollow  ComputeFirstAndFollowSets(grammar G);
void createParseTable(FirstAndFollow  F, table T);
parseTree  parseInputSourceCode(char *testcaseFile, table T);
void printParseTree(parseTree  PT, char *outfile);

#endif