#include <iostream>
#include <iostream>
#include <cstdlib>

using namespace std;

/*reference:http://alrightchiu.github.io/SecondRound/queue-yi-arrayshi-zuo-queue.html*/

int visit=0;

class QueueArrayCircular;
class MatrixTree;
class TreeNode{
public:
    TreeNode *LeftChild;
    TreeNode *DownChild;
    TreeNode *RightChild;
    TreeNode *Upchild;
    TreeNode *parent;
    int data;

    TreeNode():LeftChild(0),DownChild(0),RightChild(0),Upchild(0),parent(0),data(0){};
    TreeNode(int x):LeftChild(0),DownChild(0),RightChild(0),Upchild(0),parent(0),data(x){};

    friend class MatrixTree;
    friend class QueueArrayCircular;
};

class MatrixTree{
public:
    TreeNode *root;
    int numberOfElement;
    MatrixTree():root(0),numberOfElement(0){};
    MatrixTree(TreeNode* node):root(node),numberOfElement(0){};

    void Levelorder();
    void Preorder(TreeNode* currentNode);
    void Postorder(TreeNode* currentNode);


};



class QueueArrayCircular{
private:
    int capacity;
    int front, back;
    TreeNode **queue;
    void DoubleCapacity();
public:
    QueueArrayCircular():capacity(2),front(0),back(0){     // 從0開始, 第一個位置放掉
        queue = new TreeNode*[capacity];
    }
    void Push(TreeNode* x);
    void Pop();
    bool IsEmpty();
    bool IsFull();
    TreeNode* getFront();
    TreeNode* getBack();
    int getSize();
    int getCapacity();    // 驗證用, 可有可無
};

void QueueArrayCircular::DoubleCapacity(){

    TreeNode **newQueue = new TreeNode*[capacity*2];

    int j = front;
    int size = getSize();
    for (int i = 1; i <= size; i++) {
        newQueue[i] = queue[++j % capacity];    // j 要先加一, 因為 front 沒有東西
    }

    back = getSize();   // 要在更改 capacity 之前抓住 back
    front = 0;          // 改變 front 要在 getSize() 之後
    capacity *= 2;

    delete [] queue;
    queue = newQueue;
}
void QueueArrayCircular::Push(TreeNode* x){

    if (IsFull()) {
        DoubleCapacity();
    }

    back = (back + 1)%capacity;
    queue[back] = x;
}
void QueueArrayCircular::Pop(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }

    front = (front + 1)%capacity;
}
bool QueueArrayCircular::IsEmpty(){

    return (front == back);
}
bool QueueArrayCircular::IsFull(){

    return ((back + 1)%capacity == front);
}
TreeNode* QueueArrayCircular::getFront(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return 0;
    }
    return queue[(front + 1)%capacity];
}
TreeNode* QueueArrayCircular::getBack(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return 0;
    }

    return queue[back];
}
int QueueArrayCircular::getSize(){

    int size;
    if (front < back) {
        size = back - front;
    }
    else {
        size = capacity - (front - back);
    }

    return size;
}
int QueueArrayCircular::getCapacity(){

    return capacity;
}

void printCircularQueue (QueueArrayCircular queue){
    cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
    << "capacity: " << queue.getCapacity() << "  number of elements: " << queue.getSize() << "\n\n";
}



int alreadyVisit[200][200] = {0};

bool MatrixTraversal(int X,int Y,int height,int width,int Matrix[200][200],int tag,TreeNode *parent);

MatrixTree *T = 0;
TreeNode *current = 0;


int commandToInteger(string command);

int main()
{
    int numberOfMatrix = 0;
    int width = 0, height = 0;
    int X = 0,Y = 0; //position of mario
    cin >> numberOfMatrix;
    while(numberOfMatrix > 0)
    {
        cin >> width >>height;
        cin >> Y >> X;
        int Matrix[200][200] = {0};
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                cin >> Matrix[i][j];
            }
        }
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                alreadyVisit[i][j] = 1;
            }
        }
        //int level = 0;
        //cin >> level;
        MatrixTraversal(X,Y,height,width,Matrix,0,0);
        //maximum = 0;

        string command = "";
        cin >> command;
        int commandNumber = 0;
        commandNumber = commandToInteger(command);
        switch(commandNumber)
        {
        case 1:
            visit=0;
            T->Levelorder();
            break;
        case 2:
            visit=0;
            T->Preorder(T->root);
            break;
        case 3:
            visit=0;
            T->Postorder(T->root);
            break;
        default:
            break;
        }



        numberOfMatrix -= 1;
    }



}

int commandToInteger(string command)
{
    if(command == "Level-order-traversal")
    {
        return 1;
    }
    else if(command == "Pre-order-traversal")
    {
        return 2;
    }
    else if(command == "Post-order-traversal")
    {
        return 3;
    }
    else{
        return -1;
    }

}

bool MatrixTraversal(int X, int Y,int height,int width, int Matrix[200][200],int tag,TreeNode *parent)
{
    //cout << X << " " << Y << " "  << Matrix[X][Y] <<endl; //debug
    if(tag == 0)
    {
       TreeNode *root = new TreeNode(Matrix[X][Y]);
       T = new MatrixTree(root);
       parent = root;
    }
    if(tag == 1)
    {
        TreeNode *left = new TreeNode(Matrix[X][Y]);
        parent->LeftChild = left;
        T->numberOfElement += 1;
        parent = left;
    }
    if(tag == 2)
    {
        TreeNode *down = new TreeNode(Matrix[X][Y]);
        parent->DownChild = down;
        T->numberOfElement += 1;
        parent = down;
    }
    if(tag == 3)
    {
        TreeNode *right = new TreeNode(Matrix[X][Y]);
        parent->RightChild = right;
        T->numberOfElement += 1;
        parent = right;
    }
    if(tag == 4)
    {
        TreeNode *up = new TreeNode(Matrix[X][Y]);
        parent->Upchild = up;
        T->numberOfElement += 1;
        parent = up;
    }
    //current = new TreeNode(Matrix[X][Y]);
    alreadyVisit[X][Y] = 0;
    if(Y > 0 && Matrix[X][Y-1] != 0  && alreadyVisit[X][Y-1] == 1 && MatrixTraversal(X, Y-1,height,width, Matrix,tag=1,parent))//move left
    {
        return true;
    }
    if(X < height && Matrix[X+1][Y] != 0  && alreadyVisit[X+1][Y]==1 && MatrixTraversal(X+1, Y,height,width, Matrix,tag=2,parent))//move down
    {
        return true;
    }
    if(Y < width && Matrix[X][Y+1] != 0  && alreadyVisit[X][Y+1]==1 && MatrixTraversal(X, Y+1,height,width, Matrix,tag=3,parent))//move right
    {
        return true;
    }
    if(X > 0 && Matrix[X-1][Y] != 0  && alreadyVisit[X-1][Y]==1 && MatrixTraversal(X-1, Y,height,width, Matrix,tag=4,parent))//move up
    {
        return true;
    }


    return false;
}

void MatrixTree::Levelorder(){
QueueArrayCircular q;
int visit = 0;
q.Push(this->root);

while(!q.IsEmpty()){
    TreeNode *current = q.getFront();
    q.Pop();
    visit = visit + 1;
    if(this->numberOfElement+1 == visit)
    {
        cout << current->data <<endl;
    }
    else
    {
        cout << current->data <<" ";
    }
    if(current->LeftChild != 0){
        q.Push(current->LeftChild);
    }
    if(current->DownChild != 0){
        q.Push(current->DownChild);
    }
    if(current->RightChild != 0){
        q.Push(current->RightChild);
    }
    if(current->Upchild != 0){
        q.Push(current->Upchild);
    }
}

}

void MatrixTree::Preorder(TreeNode* currentNode)
{


    if(currentNode !=0)
    {
        visit = visit +1;
        //cout << this->numberOfElement << endl;
        if(this->numberOfElement+1 == visit)
        {
            cout << currentNode->data << endl;
        }
        else
        {
            cout << currentNode->data << " ";
        }

        Preorder(currentNode->LeftChild);
        Preorder(currentNode->DownChild);
        Preorder(currentNode->RightChild);
        Preorder(currentNode->Upchild);
    }
}

void MatrixTree::Postorder(TreeNode* currentNode)
{
    if(currentNode != 0)
    {
        Postorder(currentNode->LeftChild);
        Postorder(currentNode->DownChild);
        Postorder(currentNode->RightChild);
        Postorder(currentNode->Upchild);
        visit = visit + 1;
        if(this->numberOfElement+1 == visit)
        {
            cout << currentNode->data << endl;
        }
        else
        {
            cout << currentNode->data << " ";
        }
    }
}
