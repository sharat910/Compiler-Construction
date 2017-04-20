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


#endif