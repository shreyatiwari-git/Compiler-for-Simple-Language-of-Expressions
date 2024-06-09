/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line
int NodeHeight(SymNode *sym) {
    int hl;
    int hr;
    if(sym==NULL) return -1;
    hl = (sym && sym->left) ? sym->left->height : -1;
    hr = (sym && sym->right) ? sym->right->height : -1;
 
    return hl > hr ? hl + 1 : hr + 1;
}
int BalanceFactor(SymNode *p) {
    int hl;
    int hr;
    hl = (p && p->left) ? p->left->height : -1;
    hr = (p && p->right) ? p->right->height : -1;
    return hl - hr;
}
SymNode*InPre(SymNode *p) {
    while (p && p->right != NULL){
        p = p->right;
    }
    return p;
}
 
SymNode* InSucc(SymNode *p) {
    while (p && p->left != NULL){
        p = p->left;
    }
    return p;
}


SymbolTable::SymbolTable(){
    size=0;
    root=NULL;
}

void SymbolTable::insert(string k){
    if (root==NULL) {
        root=new SymNode(k);
        size++;
        return;
    }
SymNode* t=root;
SymNode* u=root;
while(t!=NULL)
{
    if(t->key==k) {
        return;
    } else if(t->key>k) {
        u=t;
        t=t->left;
    } else {
        u=t;
        t=t->right;
    }
}
if(u->key>k) {
    u->left=new SymNode(k);
    u->left->par=u;
} else {
    u->right=new SymNode(k);
    u->right->par=u;
}
size++;
    t=u;
    int bf;
    while(t!=NULL)
    {
        bf=BalanceFactor(t);
        // Balance Factor and Rotation
        if(bf==0||bf==1||bf==-1) {
            u=t;
            int hl,hr;
            hl = (t->left) ? t->left->height : -1;
            hr = (t->right) ? t->right->height : -1;
            t->height=(hl>hr?hl+1:hr+1);   // in other 4 cases height is itself assigned correctly by rotation fn implied in symnode.cpp
        } else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == -1) {
               u=t->LeftLeftRotation();
        } else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == 1) {
               u=t->RightRightRotation();
        } else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == 1) {
               u=t->LeftRightRotation();
        } else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == -1) {
               u=t->RightLeftRotation();
        }
        if(t==root) {
            root=u;
            t=u;
        } else {
            t=u;
        }
        t=t->par;
    }
return;
}

void SymbolTable::remove(string k){
    if (root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        size--;
            return ;
    } 
    SymNode* t=root;
    SymNode* u=NULL;
    SymNode* v;
    while(t->key!=k) {
        if(t->key>k) {
            u=t;
            t=t->left;
        } else if(t->key<k){
            u=t;
            t=t->right;
        }
    }
    if(t->left==NULL && t->right==NULL) {
        if(u->left==t) {
            u->left=NULL;
        } else {
            u->right=NULL;
        }
        t->par = NULL;
        delete t;
    } else if(t->left==NULL) {
        if(u==NULL){
            SymNode* temp=root;
            root=temp->right;
            temp->right->par=NULL;
            t=temp;
            u=root;
        } else if(u->left==t) {
            u->left=t->right;
            t->right->par=u;
        } else {
            u->right=t->right;
            t->right->par=u;
        }
        t->right=NULL;
        t->par = NULL;
        delete t;
    } else if(t->right==NULL) {
        if(u==NULL){
            SymNode* temp=root;
            root=temp->left;
            temp->left->par=NULL;
            t=temp;
            u=root;
        } else if(u->left==t) {
            u->left=t->left;
            t->left->par=u;
        } else {
            u->right=t->left;
            t->left->par=u;
        }
        t->left=NULL;
        t->par = NULL;
        delete t;
    } else {
        if (NodeHeight(t->left) > NodeHeight(t->right)){
            v = InPre(t->left);
            t->key = v->key;
            t->address=v->address;
            u=v->par;
            t=v;
        } else {
            v = InSucc(t->right);
            t->key = v->key;
            t->address=v->address;
            u=v->par;
            t=v;
        }
        if(t->left==NULL && t->right==NULL) {
            if(u->left==t) {
                u->left=NULL;
            } else {
                u->right=NULL;
            }
            t->par = NULL;
            delete t;
        } else if(t->left==NULL) {
            if(u->left==t) {
                u->left=t->right;
                t->right->par=u;
            } else {
                u->right=t->right;
                t->right->par=u;
            }
            t->right=NULL;
            t->par = NULL;
            delete t;
        } else if(t->right==NULL) {
            if(u->left==t) {
                u->left=t->left;
                t->left->par=u;
            } else {
                u->right=t->left;
                t->left->par=u;
            }
            t->left=NULL;
            t->par = NULL;
            delete t;
        }
    }
    t=u;
    int bf;
    while(t!=NULL)
    {
        bf=BalanceFactor(t);
        // Balance Factor and Rotation
        if(bf==0||bf==1||bf==-1) {
            u=t;
            int hl,hr;
            hl = (t->left) ? t->left->height : -1;
            hr = (t->right) ? t->right->height : -1;
            t->height=(hl>hr?hl+1:hr+1);   // in other 4 cases height is itself assigned correctly by rotation fn implied in symnode.cpp
        } else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) == -1) {
               u=t->LeftLeftRotation();
        } else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) == 1) {
               u=t->RightRightRotation();
        } else if (BalanceFactor(t) == -2 && BalanceFactor(t->right) <= 1) {
               u=t->LeftRightRotation();
        } else if (BalanceFactor(t) == 2 && BalanceFactor(t->left) >= -1) {
               u=t->RightLeftRotation();
        }
        if(t==root) {
            root=u;
            t=u;
        } else {
            t=u;
        }
        t=t->par;
    }
    size--;
}

int SymbolTable::search(string k){
    SymNode* t=root;
        while(t!=NULL)
        {
            if(t->key==k) {
                return t->address;
            } else if(t->key>k) {
                t=t->left;
            } else {
                t=t->right;
            }
        }
        return -2;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* t=root;
        while(t!=NULL)
        {
            if(t->key==k) {
                t->address=idx;
                return;
            } else if(t->key>k) {
                t=t->left;
            } else {
                t=t->right;
            }
        }
        return;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}
