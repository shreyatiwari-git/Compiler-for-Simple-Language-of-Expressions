/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    symtable=new SymbolTable();
}

void Parser::parse(vector<string> expression){
       ExprTreeNode* root=new ExprTreeNode(expression[1],0);
    if(expression[0]=="del"){
        root->left=new ExprTreeNode("DEL",0);
        root->right=new ExprTreeNode("VAR",-1);
        root->right->id=expression[2];
        last_deleted=symtable->search(expression[2]);
        symtable->remove(expression[2]);
        expr_trees.push_back(root);
        return;
    } else {
        if(expression[0]=="ret"){
            root->left=new ExprTreeNode("RET",0);
        } else {
            root->left=new ExprTreeNode("VAR",-1);
            root->left->id=expression[0];
            if(symtable->search(expression[0])==-2) {
                symtable->insert(expression[0]);
            } else {
                root->left->num=symtable->search(expression[0]);
            }
        }
        vector<ExprTreeNode*> stack;
        stack.push_back(root);
        for(int i=2;i<expression.size();i++)
        {
            if(expression[i]=="(") {
                ExprTreeNode* buffer=new ExprTreeNode("",0);
                stack.push_back(buffer);
                buffer=NULL;
            } else if(expression[i]=="+"||expression[i]=="-"||expression[i]=="*"||expression[i]=="/") {
                if(expression[i]=="+") {
                    stack[stack.size()-1]->type="ADD";
                } else if(expression[i]=="-") {
                    stack[stack.size()-1]->type="SUB";
                } else if(expression[i]=="*") {
                    stack[stack.size()-1]->type="MUL";
                } else if(expression[i]=="/") {
                    stack[stack.size()-1]->type="DIV";
                }
            } else if(expression[i]==")") {
                ExprTreeNode* top=stack[stack.size()-1];
                stack.pop_back();
                if( stack[stack.size()-1]->left==NULL) {
                    stack[stack.size()-1]->left=top;
                } else {
                    stack[stack.size()-1]->right=top;
                }
                top=NULL;
            } else {
                string node_type;
                if(expression[i][0]=='-'||expression[i][0]=='1'||expression[i][0]=='2'||expression[i][0]=='3'||expression[i][0]=='4'||expression[i][0]=='5'||expression[i][0]=='6'||expression[i][0]=='7'||expression[i][0]=='8'||expression[i][0]=='9'||expression[i][0]=='0') {
                    node_type="VAL";
                } else {
                    node_type="VAR";
                }
                if( stack[stack.size()-1]->left==NULL) {
                    if(node_type=="VAL") {
                        stack[stack.size()-1]->left=new ExprTreeNode(node_type,stoi(expression[i]));
                    } else {
                        stack[stack.size()-1]->left=new ExprTreeNode(node_type,-1);
                        stack[stack.size()-1]->left->id=expression[i];
                        stack[stack.size()-1]->left->num=symtable->search(expression[i]);
                    }
                } else {
                    if(node_type=="VAL") {
                       stack[stack.size()-1]->right=new ExprTreeNode(node_type,stoi(expression[i]));
                    } else {
                        stack[stack.size()-1]->right=new ExprTreeNode(node_type,-1);
                        stack[stack.size()-1]->right->id=expression[i];
                        stack[stack.size()-1]->right->num=symtable->search(expression[i]);
                    }
                }
            }
        }
        stack.pop_back();
        expr_trees.push_back(root);
        root=NULL;
    }
}

Parser::~Parser(){
    delete symtable;
}

