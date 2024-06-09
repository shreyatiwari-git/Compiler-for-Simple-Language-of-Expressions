/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line
void traverse(ExprTreeNode* exp_root,vector<string> * targ_output) {
    if(exp_root==NULL) return;
    traverse(exp_root->right, targ_output);
    traverse(exp_root->left, targ_output);
    if(exp_root->type=="ADD") {
        targ_output->push_back("ADD");
    } else if (exp_root->type=="SUB") {
        targ_output->push_back("SUB");
    } else if (exp_root->type=="MUL") {
        targ_output->push_back("MUL");
    } else if (exp_root->type=="DIV") {
        targ_output->push_back("DIV");
    } else if (exp_root->type=="VAL") {
        targ_output->push_back("PUSH "+to_string(exp_root->num));
    } else if (exp_root->type=="VAR") {
        targ_output->push_back("PUSH mem["+to_string(exp_root->num)+"]");
    }
    return;
}

EPPCompiler::EPPCompiler(){

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file=out_file;
    memory_size=mem_limit;
    for(int i=0;i<memory_size;i++)
    {
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
for(auto itr:code)
{
    targ.parse(itr);
    ExprTreeNode* exp_root= targ.expr_trees[targ.expr_trees.size()-1];
    if(exp_root->left->type=="DEL") {
        mem_loc.push_back(targ.last_deleted);
    } else if(exp_root->left->type=="RET") {
        
    } else {
        if(exp_root->left->num==-1) {
            int free=mem_loc.back();
            mem_loc.pop_back();
            targ.symtable->assign_address(exp_root->left->id, free);
            exp_root->left->num=free;  // storing address that is available in symtable so that we can use this in travese fn
        }
    }
    write_to_file(generate_targ_commands());
    //generate_targ_commands();
    
}
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> targ_output;
    ExprTreeNode* exp_root= targ.expr_trees[targ.expr_trees.size()-1];
    if(exp_root->left->type=="DEL") {
        targ_output.push_back("DEL = mem["+to_string(targ.last_deleted)+"]");
        return targ_output;
    } else {
        traverse(exp_root->right, &targ_output);
        if(exp_root->left->type=="RET") {
            targ_output.push_back("RET = POP");
        } else if(exp_root->left->type=="VAR") {
            targ_output.push_back("mem[" + to_string(exp_root->left->num)+"] = POP");
        }
    }
    return targ_output;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream outfile(output_file,ios::app);
    for(auto itr:commands) {
        outfile<<itr<<endl;
    }
}

EPPCompiler::~EPPCompiler(){
    
}
