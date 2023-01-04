#include <iostream>
#include <queue>
using namespace std;

struct treeNode {
    struct treeNode *leftPtr;
    int data;
    struct treeNode *rightPtr;
};
typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

queue<TreeNodePtr> list;

void insert(TreeNodePtr *sPtr, int value);
void inorder(TreeNodePtr treePtr);
void preorder(TreeNodePtr treePtr);
void postorder(TreeNodePtr treePtr);

int main(){
    int num = 0;int length = 0; int a = 0;
    cin >> num;
    
    for(int i = 0; i < num; i++){
        cin >> length;
        TreeNodePtr rootPtr = NULL;
        TreeNodePtr startPtr = NULL;
        for(int j = 0; j < length; j++){
            if(j == 0){
                cin >> a;
                insert(&startPtr, a);
                rootPtr = startPtr;
            }
            else{
                cin >> a;
                insert(&startPtr, a);
            }
        }
        preorder(rootPtr);
        cout << endl;
        inorder(rootPtr);
        cout << endl;
        postorder(rootPtr);
        cout << endl;
        while(!list.empty()){
            list.pop();
        }
    }
    
}

void insert(TreeNodePtr *sPtr, int value){
    TreeNodePtr tempPtr = NULL;
    if(*sPtr == NULL){
        (*sPtr) = new TreeNode;
        (*sPtr)->data = value;
        (*sPtr)->leftPtr = NULL;
        (*sPtr)->rightPtr = NULL;
        tempPtr = (*sPtr);
        list.push(tempPtr);
    }
    else{
        if((*sPtr)->leftPtr == NULL){
            insert(&(*sPtr)->leftPtr, value);
        }
        else if((*sPtr)->rightPtr == NULL){
            insert(&(*sPtr)->rightPtr, value);
        }
        else{
            list.pop();
            (*sPtr) = list.front();
            insert(&(*sPtr), value);
        }
    }
}

void inorder(TreeNodePtr treePtr){
    if(treePtr != NULL){
        inorder(treePtr->leftPtr);
        cout << treePtr->data << " ";
        inorder(treePtr->rightPtr);
    }
}

void preorder(TreeNodePtr treePtr){
    if(treePtr != NULL){
        cout << treePtr->data << " ";
        preorder(treePtr->leftPtr);
        preorder(treePtr->rightPtr);
    }
}

void postorder(TreeNodePtr treePtr){
    if(treePtr != NULL){
        postorder(treePtr->leftPtr);
        postorder(treePtr->rightPtr);
        cout << treePtr->data << " ";
    }
}