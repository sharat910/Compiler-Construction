#ifndef _codegen
#define _codegen

#include "ast.h"
#include "symbolTable.h"

void bss();
void data();
void input(AST_NODE *root);
void output(AST_NODE* root);
void while_gen(AST_NODE* root);
void for_gen(AST_NODE* root);
void process(AST_NODE* root);
void traverseAST(AST_NODE* root);
void switch_gen(AST_NODE* root);
void for_gen(AST_NODE* root);
void assignment_gen(AST_NODE* root);
void boolean_gen(AST_NODE* root);
void generate_code(AST_NODE* root);
void operate(AST_NODE* op);
int N4(AST_NODE* n4);
int N5(AST_NODE* n5);
void AE(AST_NODE* ae,int flag);
void term(AST_NODE* term);
void factor(AST_NODE* factor);



#endif