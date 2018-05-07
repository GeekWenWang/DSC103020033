#include <iostream>
#include <cstdlib>
#include <queue>

using namespace std;

int maximum = 0;

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
};

class MatrixTree{
public:
    TreeNode *root;
    MatrixTree():root(0){};
    MatrixTree(TreeNode* node):root(node){};

    void Levelorder();
    int findMaximumInNLevel(TreeNode *current,int level);

};

void MatrixTree::Levelorder(){
queue<TreeNode*> q;
q.push(this->root);

while(!q.empty()){
    TreeNode *current = q.front();
    q.pop();
    cout << current->data <<" ";
    if(current->LeftChild != 0){
        q.push(current->LeftChild);
    }
    if(current->DownChild != 0){
        q.push(current->DownChild);
    }
    if(current->RightChild != 0){
        q.push(current->RightChild);
    }
    if(current->Upchild != 0){
        q.push(current->Upchild);
    }
}

}

int MatrixTree::findMaximumInNLevel(TreeNode *current,int level)
{
    //
    if (current == NULL)
    return 0;
    if (level == 1)
    {
        if(current->data > maximum)
        {
            maximum = current->data;
            //cout <<maximum;
        }
    }
    else if (level > 1)
    {
        findMaximumInNLevel(current->LeftChild, level-1);
        findMaximumInNLevel(current->DownChild, level-1);
        findMaximumInNLevel(current->RightChild, level-1);
        findMaximumInNLevel(current->Upchild, level-1);
    }
    return 0;
}

int alreadyVisit[200][200] = {0};

bool MatrixTraversal(int X,int Y,int height,int width,int Matrix[200][200],int tag,TreeNode *parent);

MatrixTree *T = 0;
TreeNode *current = 0;

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
        int level = 0;
        cin >> level;
        MatrixTraversal(X,Y,height,width,Matrix,0,0);
        maximum = 0;
        //T->Levelorder();
        //cout << endl;
        T->findMaximumInNLevel(T->root,level+1);
        cout << maximum <<endl;

        //TreeNode *root = new TreeNode(Matrix[X][Y]);


        numberOfMatrix -= 1;
    }
    return 0;
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
        parent = left;
    }
    if(tag == 2)
    {
        TreeNode *down = new TreeNode(Matrix[X][Y]);
        parent->DownChild = down;
        parent = down;
    }
    if(tag == 3)
    {
        TreeNode *right = new TreeNode(Matrix[X][Y]);
        parent->RightChild = right;
        parent = right;
    }
    if(tag == 4)
    {
        TreeNode *up = new TreeNode(Matrix[X][Y]);
        parent->Upchild = up;
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



