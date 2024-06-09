/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line
void update_height(SymNode* sym)
{
    int hl,hr;
    hl=(sym->left)?sym->left->height:-1;
    hr=(sym->right)?sym->right->height:-1;
    sym->height=(hl>hr)?hl+1:hr+1;
    return;
    
}

SymNode::SymNode(){

}

SymNode::SymNode(string k){
    key=k;
    height=0;
}

SymNode* SymNode::LeftLeftRotation(){  //right right imbalance
    if(par==NULL)
    {
        right->par=par;
    }
    else if(par->left==this)
    {
        right->par=par;
        par->left=right;
    }
    else
    {
        right->par=par;
        par->right=right;
    }
    par=right;
    right=right->left;
    if(right!=NULL){
        right->par=this;
    }
    par->left=this;
    update_height(this);
    update_height(this->par);
    return par;
}

SymNode* SymNode::RightRightRotation(){   //left left imbalance
    if(par==NULL) {
        left->par=par;
    } else if(par->left==this) {
        left->par=par;
        par->left=left;
    } else {
        left->par=par;
        par->right=left;
    }
    par=left;
    left=left->right;
    if(left!=NULL){
        left->par=this;
    }
    par->right=this;
    update_height(this);
    update_height(this->par);
    return par;
}

SymNode* SymNode::LeftRightRotation(){     //right left imbalance
    right->RightRightRotation();
    this->LeftLeftRotation();
    return par;
}

SymNode* SymNode::RightLeftRotation(){   //left right imbalance
    left->LeftLeftRotation();
    this->RightRightRotation();
    return par;
}

SymNode::~SymNode(){
    delete left;
    delete right;
}
