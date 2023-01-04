#include <iostream>
using namespace std;

struct element{
    int row;
    int col;
    int dir;
    struct element *nextPtr;
};

struct offsets{
    int vert;
    int horiz;
};

typedef struct element Element;
typedef Element *ElementPtr;
typedef struct offsets Offsets;

void push(ElementPtr *topPtr, Element data);
Element pop(ElementPtr *topPtr);
void print_f(ElementPtr currentPtr);

int main(){
    int length = 0;//row
    int width = 0;//column
    int n = 0;
    cin >> length >> width;
    int maze[length+2][width+2] = {};
    int mark[length+2][width+2] = {};
    for(int i = 0; i < length+2; i++){
        for(int j = 0; j < width+2; j++){
            if(i == 0 || j == 0 || i == length+1 || j == width+1)
                maze[i][j] = 1;
            else{
                cin >> n;
                maze[i][j] = n;
            }
        }
    }//end for

    ElementPtr stackPtr = NULL;
    Offsets move[4];
    Element position;
    move[0].vert = 1; move[0].horiz = 0;//North
    move[1].vert = 0; move[1].horiz = 1;//East
    move[2].vert = -1; move[2].horiz = 0;//South
    move[3].vert = 0; move[3].horiz = -1;//West
    int now_col = 0; int now_row = 0; int now_dir = 0;
    int next_row = 0; int next_col = 0;
    bool found = false;
    mark[length][width] = 1;
    position.col = width; position.row = length; position.dir = 0;
    push(&stackPtr, position);
    while(stackPtr != NULL && !found){
        position = pop(&stackPtr);
        now_row = position.row; now_col = position.col; now_dir = position.dir;
        while(now_dir < 4 && !found){
            next_row = now_row + move[now_dir].vert;
            next_col = now_col + move[now_dir].horiz;
            if(next_row == 1 && next_col == 0)
                found = true;
            else if(maze[next_row][next_col] == 0 && mark[next_row][next_col] == 0){
                mark[next_row][next_col] = 1;
                position.row = now_row;
                position.col = now_col;
                position.dir = now_dir++;
                push(&stackPtr, position);
                now_row = next_row; now_col = next_col; now_dir = 0;
            }
            else
                now_dir++;
        }
    }
    if(found){
        cout << "(0,0) ";
        print_f(stackPtr);
    }
    else
        cout << "Can't reach the exit!" << endl;
}

void push(ElementPtr *topPtr, Element data){
    ElementPtr newPtr = new Element;
    newPtr->row = data.row;
    newPtr->col = data.col;
    newPtr->dir = data.dir;
    newPtr->nextPtr = NULL;
    if(*topPtr == NULL){
        (*topPtr) = newPtr;
    }
    else{
        newPtr->nextPtr = (*topPtr);
        (*topPtr) = newPtr;
    }
}

Element pop(ElementPtr *topPtr){
    ElementPtr tempPtr = (*topPtr);
    Element value;
    value.row = (*topPtr)->row;
    value.col = (*topPtr)->col;
    value.dir = (*topPtr)->dir;
    (*topPtr) = (*topPtr)->nextPtr;
    free(tempPtr);
    return value;
}

void print_f(ElementPtr currentPtr){
    while(currentPtr != NULL){
        cout << "(" << currentPtr->row-1 << "," << currentPtr->col-1 << ") ";
        currentPtr = currentPtr->nextPtr;
    }
}