#include "ast2.h"
#include <stdio.h>
int non_term_to_remove(char *non_terminal){  

	if( 
	(strcmp(non_terminal, "<moduleDeclarations>") == 0) || 
	(strcmp(non_terminal, "<otherModules>") == 0) || 
	(strcmp(non_terminal, "<fieldDefinitions>") == 0) || 
	(strcmp(non_terminal, "<moduleDeclaration>") == 0) || 	
	(strcmp(non_terminal, "<input_plist>") == 0) || 	
	(strcmp(non_terminal, "<output_plist>") == 0) ||
	(strcmp(non_terminal, "<ret>") == 0) || 
	(strcmp(non_terminal, "<input_plist_ex>") == 0) ||
	(strcmp(non_terminal, "<onput_plist_ex>") == 0) ||
	(strcmp(non_terminal, "<dataType>") == 0) || 
	(strcmp(non_terminal, "<statements>") == 0) ||
	(strcmp(non_terminal, "<type>") == 0) ||
	(strcmp(non_terminal, "<range>") == 0) ||
	(strcmp(non_terminal, "<moduleDef>") == 0) ||
	(strcmp(non_terminal, "<statement>") == 0) ||
	(strcmp(non_terminal, "<var>") == 0) ||
	(strcmp(non_terminal, "<whichId>") == 0) ||
    (strcmp(non_terminal, "<simpleStmt>") == 0) ||
    (strcmp(non_terminal, "<whichStmt>") == 0) ||
	(strcmp(non_terminal, "<expression>") == 0) ||
	(strcmp(non_terminal, "<index>") == 0) ||
	(strcmp(non_terminal, "<optional>") == 0) ||
	(strcmp(non_terminal, "<AOBE>") == 0) ||
	(strcmp(non_terminal, "<negOrPosAE>") == 0) ||
	(strcmp(non_terminal, "<AnyTerm>") == 0) ||
	(strcmp(non_terminal, "<WithLogOp>") == 0) ||
	(strcmp(non_terminal, "<logicalOp>") == 0) ||
	(strcmp(non_terminal, "<AnyTerm2>") == 0) ||
	(strcmp(non_terminal, "<WithRelOp>") == 0) ||
	(strcmp(non_terminal, "<alpha>") == 0) ||
	(strcmp(non_terminal, "<all_ops>") == 0) ||
	(strcmp(non_terminal, "<op1>") == 0) ||
	(strcmp(non_terminal, "<op2>") == 0) ||
	(strcmp(non_terminal, "<N4>") == 0) ||
	(strcmp(non_terminal, "<N5>") == 0) ||	
	(strcmp(non_terminal, "<idList_ex>") == 0) ||
	(strcmp(non_terminal, "<factor>") == 0) ||
	(strcmp(non_terminal, "<relationalOp>") == 0) ||
	(strcmp(non_terminal, "<BorNBAE>") == 0) ) return 1;
	else return 0;	
}

//Terminals which are pointing to epsilon.
int to_eps(char *non_terminal){

	if( (strcmp(non_terminal, "<moduleDeclarations>") == 0) || 
		(strcmp(non_terminal, "<otherModules>") == 0) ||
		(strcmp(non_terminal, "<ret>") == 0) ||
		(strcmp(non_terminal, "<input_plist_ex>") == 0) ||
		(strcmp(non_terminal, "<output_plist_ex>") == 0) ||
		(strcmp(non_terminal, "<statements>") == 0) ||
		(strcmp(non_terminal, "<whichId>") == 0) ||
		(strcmp(non_terminal, "<optional>") == 0) ||
		(strcmp(non_terminal, "<idList_ex>") == 0) ||
		(strcmp(non_terminal, "<WithLogOp>") == 0) ||
		(strcmp(non_terminal, "<WithRelOp>") == 0) ||
		(strcmp(non_terminal, "<alpha>") == 0) ||
		(strcmp(non_terminal, "<N4>") == 0) ||
		(strcmp(non_terminal, "<N5>") == 0) ||
		(strcmp(non_terminal, "<MultiCase>") == 0) ||
		(strcmp(non_terminal, "<default>") == 0) ) return 1;
		else return 0;	

}

//Function to check the terminals to be removed.
int term_to_remove(char *terminal){	
	if( (strcmp(terminal, "SEMICOL") == 0) ||
	(strcmp(terminal, "BO") == 0) ||
	(strcmp(terminal, "BC") == 0) ||
	(strcmp(terminal, "START") == 0) ||
	(strcmp(terminal, "END") == 0) ||
	(strcmp(terminal, "CASE") == 0) ||
	(strcmp(terminal, "DECLARE") == 0) ||
	(strcmp(terminal, "COMMA") == 0) ||
	(strcmp(terminal, "ASSIGNOP") == 0) ||
	(strcmp(terminal, "COMMA") == 0) ||
	(strcmp(terminal, "COLON") == 0) ||
	(strcmp(terminal, "DEF") == 0) ||
	(strcmp(terminal, "ENDDEF") == 0) ||
	(strcmp(terminal, "TAKES") == 0) ||
	(strcmp(terminal, "MODULE") == 0) ||		
	(strcmp(terminal, "PROGRAM") == 0) ||
	(strcmp(terminal, "DRIVERDEF")==0) ||
    (strcmp(terminal, "DRIVERENDDEF") == 0) ||
    (strcmp(terminal, "PARAMETERS") == 0) ||
    (strcmp(terminal, "WITH") == 0) ||
    (strcmp(terminal, "e") == 0) ) return 1;
    else return 0;
}


void create2AST(TREE_NODE_PTR parent, TREE_NODE_PTR child){
	if(child==NULL) return;
	// printf("%s\n",parent->NodeSymbol );
	if((child->isLeafNode==0 && non_term_to_remove(child->NodeSymbol)==0 ) || (child->isLeafNode==1 && term_to_remove(child->NodeSymbol)==0) ){
	
	if(to_eps(child->NodeSymbol)==1 && (strcmp(child->child->NodeSymbol,"e")==0)){
		
	}else{

		TREE_NODE_PTR temp=parent->ASTchild;
		TREE_NODE_PTR prevtemp;

		if(temp==NULL){
			parent->ASTchild=child;
			child->ASTparent=parent;
		}
		else{
			while(temp!=NULL){
				prevtemp=temp;
				temp=temp->ASTsibling;
			}
			prevtemp->ASTsibling=child;
			child->ASTparent=parent;
		}
			
	
		create2AST(child,child->child);
	}

	}else{
		create2AST(parent,child->child);
	}
		create2AST(parent,child->sibling);
	
	return;
}

void construct2AST(TREE_NODE_PTR root){
	create2AST(root,root->child);
	return;
}



//Function to print the complete AST
void print2AST(TREE_NODE_PTR root){
	if(root==NULL){ return; } 
   
	if(strcmp(root->NodeSymbol,"ASSIGNOP")!=0){   
    printf("%-20s",root->lexemeCurrentNode);
    
    if(root->isLeafNode==1){
        printf("%-20d",root->lineno);
        printf("%-20s",root->lexemeCurrentNode);
        }
    }else{
        printf("%-20s"," - ");
        printf("%-20s"," - ");
         
    }
    if(strcmp(root->NodeSymbol,"NUM")==0 || strcmp(root->NodeSymbol,"RNUM")==0){
        printf("%-20s",root->lexemeCurrentNode);
        
    }else{
        printf("%-20s"," - ");
    }

	if(root->ASTparent!=NULL)
    printf("%-20s",root->ASTparent->NodeSymbol);
    else
   	printf("%-20s"," - ");
   	    
    if(root->isLeafNode==1){
        printf("%-20s","yes ");
        printf("%-20s\n"," - ");
        
    }else{
        printf("%-20s","no ");
        printf("%-20s\n",root->NodeSymbol);
        
    }
    print2AST(root->ASTchild);
    print2AST(root->ASTsibling);
    
    
    return;
}


// //Function to calculate the nodes in AST
// void countAST(treeNode *root){
// 	if(root==NULL) return;
// 	if(strcmp(root->nodeSymbol,"TK_ASSIGNOP")!=0 ){
// 	astcount++;
// 	countAST(root->ASTchild);
// 	countAST(root->ASTnext);
// 	}
	
// }

// void countPST(treeNode * t){
// 	if(t==NULL) return;

// 	pstcount++;
// 	countPST(t->child);
// 	countPST(t->next);
	
// }