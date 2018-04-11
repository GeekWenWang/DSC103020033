#include <iostream>
#include <cstdio>
#include <set>
#include <string>

using namespace std;

/* code reference:http://alrightchiu.github.io/SecondRound/stack-yi-arrayyu-linked-listshi-zuo.html*/
class StackArray{
private:
    char capacity;            // allocated memory space of array
    char *mystack;  // array representing stack
    int top;
    void DoubleCapacity();   // double the capacity of stack
public:
    StackArray():top(-1),capacity(1){    // constructor
        mystack = new char[capacity];       // initial state: top=-1, capacity=1
    }
    void Push(char x);
    void Pop();
    bool IsEmpty();
    char Top();
    int getSize();
};
void StackArray::DoubleCapacity(){

    capacity *= 2;                            // double capacity
    char *newStack = new char[capacity];        // create newStack

    for (int i = 0 ; i < capacity/2; i++) {   // copy element to newStack
        newStack[i] = mystack[i];
    }

    delete [] mystack;              // release the memory of stack
    mystack = newStack;             // redirect stack to newStack
}

void StackArray::Push(char x){

    if (top == capacity - 1) {    // if stack is full, double the capacity
        DoubleCapacity();
    }
    mystack[++top] = x;             // update top and put x into stack
}

void StackArray::Pop(){

    if (IsEmpty()) {          // if stack is empty, there is nothing to pop
        cout << "Stack is empty.\n";
        return;
    }
    top--;                    // update top
//    stack[top] = 0;         // (*1)
//    stack[top].~T();        // (*2)
}

bool StackArray::IsEmpty(){

    //    if (top == -1) {
    //        return true;
    //    }
    //    else {
    //        return false;
    //    }
    return (top == -1);
}

char StackArray::Top(){

    if (IsEmpty()) {     // check if stack is empty
        cout << "Stack is empty.\n";
        return -1;
    }
    return mystack[top];   // return the top element
}

int StackArray::getSize(){

    return top+1;        // return the number of elements in stack
}


StackArray route;

//stack<char> route;
int Matrix_check[100][100] = {0};//check if the matrix condition


int isDigit(char target);
int isOperator(char target);
int isFrontbraket(char target);
int isBackbraket(char target);

bool evaluation_function(int pre_one, int new_one);
bool solve(char M[100][100],int Mt[100][100],int x,int y,int column,int row,int record);
bool bracketValid(StackArray route);
string presentation(string s);
int priority(char op);
void printMatrix(int column,int row,int Matrix[100][100]);


int main()
{
    int test = 0;
    int test_count = 0;
    cin >> test;
    //cout << test <<endl;

    for(int i=0;i<100;i++)
    {
        for(int j =0;j<100;j++)
        {
            if(Matrix_check[i][j] != 1)
            {
                Matrix_check[i][j] = 1;
            }
        }
    }

    while(test !=0)
    {
        int column = 0;
        int row = 0;
        cin >> row >> column;
        //cout << row << endl;
        //cout << column <<endl;
        char Matrix[100][100];
        int Matrix_type[100][100];

        test_count = test_count+1;
        for(int i=0;i<column;i++)
        {
            for(int j=0;j<row;j++)
            {
                cin >> Matrix[i][j];//input all matrix element
                if(isDigit(Matrix[i][j]) == 1)
                {
                    Matrix_type[i][j] = 0;
                }
                else if(isOperator(Matrix[i][j]) == 1)
                {
                    Matrix_type[i][j] = 1;
                }
                else if(isFrontbraket(Matrix[i][j]) == 1)
                {
                    Matrix_type[i][j] = 2;
                }
                else if(isBackbraket(Matrix[i][j]) == 1)
                {
                    Matrix_type[i][j] = 3;
                }
                else
                {
                    Matrix_type[i][j] = -1;
                }
            }
        }
        /*for(int i = 0 ; i<column ; i++)//repeat all input matrix
        {
            for(int j = 0; j<row;j++)
            {
                if(j == row-1)
                {
                    cout << Matrix[i][j];
                    cout << endl;
                }
                else
                {
                    cout << Matrix[i][j]<<" ";
                }
            }
        }*/
        /*for(int i = 0 ; i<column ; i++)//repeat all input matrix
        {
            for(int j = 0; j<row;j++)
            {

                cout << Matrix[i][j]<<" ";
            }
        }
        cout << endl;*/


        //set<int> record;
        //stack<char> route;

        StackArray posfix_op;
        if(test_count==1)
        {
            cout << test <<endl;
            cout << row << endl;
            cout << column <<endl;

            for(int i = 0 ; i<column ; i++)//repeat all input matrix
            {
                for(int j = 0; j<row;j++)
                {
                    if(j == row-1)
                    {
                        cout << Matrix[i][j] <<" ";
                        cout << endl;
                    }
                    else
                    {
                        cout << Matrix[i][j]<<" ";
                    }
                }
            }

            if(solve(Matrix,Matrix_type,0,0,column,row,0) && Matrix_type[0][0]!=1 && Matrix_type[0][0]!=3 &&Matrix_type[column-1][row-1]!=1 && Matrix_type[column-1][row-1]!=2 )
            {
                string infix_s = "";
                string posfix_s = "";
                while(!route.IsEmpty())//printroute
                {
                    if(route.Top()>='0'&&route.Top()<='9')
                    {
                        infix_s = route.Top()+ infix_s;
                        route.Pop();
                    }
                    else
                    {
                        infix_s = route.Top()+ infix_s;
                        route.Pop();
                    }
                }

                cout<< "Yes" <<endl;
            //cout << s <<endl;
            //cout << s << endl;
            //infixToPosfix
                cout << presentation(infix_s) <<endl;
                for(int i = 0; i< infix_s.length(); i ++)
                {
                    if(isFrontbraket(infix_s[i])==1)
                    {
                        posfix_op.Push(infix_s[i]);
                    }
                    else if(isDigit(infix_s[i])==1)
                    {
                        posfix_s += infix_s[i];
                    }
                    else if(isOperator(infix_s[i])==1)
                    {

                        if(!posfix_op.IsEmpty())
                        {
                            while(!posfix_op.IsEmpty() &&priority(posfix_op.Top())>= priority(infix_s[i]))
                            {
                                //cout << priority(posfix_op.top()) << priority(infix_s[i]) <<endl;
                                posfix_s += " ";
                                posfix_s += posfix_op.Top();
                                posfix_op.Pop();
                            }

                        }
                        posfix_s += " ";
                        posfix_op.Push(infix_s[i]);
                    }
                    else
                    {
                        //posfix_s += posfix_op.top();
                        while(posfix_op.Top() != '(')
                        {
                            posfix_s += " ";
                            posfix_s += posfix_op.Top();
                            posfix_op.Pop();
                        }
                        posfix_op.Pop();

                    }

                }
                posfix_s += " ";
                while(!posfix_op.IsEmpty())
                {
                    posfix_s += posfix_op.Top();
                    posfix_s += " ";
                    posfix_op.Pop();
                }



                cout << posfix_s <<endl;
            }
            else
            {
                string s;
                while(!route.IsEmpty())//printroute
                {
                    if(route.Top()>='0'&&route.Top()<='9')
                    {
                        s = route.Top()+s;
                        route.Pop();
                    }
                    else
                    {
                        s = route.Top()+s;
                        route.Pop();
                    }
                }
                cout <<"No" <<endl;
            }

            string s;
            while(!route.IsEmpty())//printroute
            {
                if(route.Top()>='0'&&route.Top()<='9')
                {
                    s = route.Top()+s;
                    route.Pop();
                }
                else
                {
                    s = route.Top()+s;
                    route.Pop();
                }
            }



            for(int i=0;i<column;i++)
            {
                for(int j =0;j<row;j++)
                {
                    if(Matrix_check[i][j] != 1)
                    {
                        Matrix_check[i][j] = 1;
                    }
                }
            }

        }
        else
        {
            cout << row << endl;
            cout << column <<endl;

            for(int i = 0 ; i<column ; i++)//repeat all input matrix
            {
                for(int j = 0; j<row;j++)
                {
                    if(j == row-1)
                    {
                        cout << Matrix[i][j] << " ";
                        cout << endl;
                    }
                    else
                    {
                        cout << Matrix[i][j]<<" ";
                    }
                }
            }
            if(solve(Matrix,Matrix_type,0,0,column,row,0) && Matrix_type[0][0]!=1 && Matrix_type[0][0]!=3 &&Matrix_type[column-1][row-1]!=1 && Matrix_type[column-1][row-1]!=2 )
            {
                string infix_s = "";
                string posfix_s = "";
                while(!route.IsEmpty())//printroute
                {
                    if(route.Top()>='0'&&route.Top()<='9')
                    {
                        infix_s = route.Top()+ infix_s;
                        route.Pop();
                    }
                    else
                    {
                        infix_s = route.Top()+ infix_s;
                        route.Pop();
                    }
                }

                cout<< "Yes" <<endl;
                //cout << s <<endl;
                //cout << s << endl;
                //infixToPosfix
                cout << presentation(infix_s) <<endl;
                for(int i = 0; i< infix_s.length(); i ++)
                {
                    if(isFrontbraket(infix_s[i])==1)
                    {
                        posfix_op.Push(infix_s[i]);
                    }
                    else if(isDigit(infix_s[i])==1)
                    {
                        posfix_s += infix_s[i];
                    }
                    else if(isOperator(infix_s[i])==1)
                    {

                        if(!posfix_op.IsEmpty())
                        {
                            while(!posfix_op.IsEmpty() &&priority(posfix_op.Top())>= priority(infix_s[i]))
                            {
                                //cout << priority(posfix_op.top()) << priority(infix_s[i]) <<endl;
                                posfix_s += " ";
                                posfix_s += posfix_op.Top();
                                posfix_op.Pop();
                            }

                        }
                        posfix_s += " ";
                        posfix_op.Push(infix_s[i]);
                    }
                    else
                    {
                        //posfix_s += posfix_op.top();
                        while(posfix_op.Top() != '(')
                        {
                            posfix_s += " ";
                            posfix_s += posfix_op.Top();
                            posfix_op.Pop();
                        }
                        posfix_op.Pop();

                    }

                }
                posfix_s += " ";
                while(!posfix_op.IsEmpty())
                {
                    posfix_s += posfix_op.Top();
                    posfix_s += " ";
                    posfix_op.Pop();
                }



                cout << posfix_s <<endl;
            }
            else
            {
                string s;
                while(!route.IsEmpty())//printroute
                {
                    if(route.Top()>='0'&&route.Top()<='9')
                    {
                        s = route.Top()+s;
                        route.Pop();
                    }
                    else
                    {
                        s = route.Top()+s;
                        route.Pop();
                    }
                }
                cout <<"No" <<endl;
            }

            string s;
            while(!route.IsEmpty())//printroute
            {
                if(route.Top()>='0'&&route.Top()<='9')
                {
                    s = route.Top()+s;
                    route.Pop();
                }
                else
                {
                    s = route.Top()+s;
                    route.Pop();
                }
            }



            for(int i=0;i<column;i++)
            {
                for(int j =0;j<row;j++)
                {
                    if(Matrix_check[i][j] != 1)
                    {
                        Matrix_check[i][j] = 1;
                    }
                }
            }
        }

        //test_count = test_count+1;
        test = test - 1;
    }

    return 0;
}



int isDigit(char target)
{
	if(target >= '0' && target <= '9')
    {
        return 1;
    }
	else{
        return 0;
	}
}

int isOperator(char target)
{
	if(target == '+' || target == '-' || target == '*' || target == '/' )
    {
        return 1;
    }
    else{ return 0;}

}

int isFrontbraket(char target)
{
	if(target == '(')
    {
        return 1;
    }
	else
    {
        return 0;
    }
}

int isBackbraket(char target)
{
	if(target == ')')
    {
        return 1;
    }
	else
    {
        return 0;
    }
}

bool evaluation_function(int pre_one, int new_one)
{
    if(pre_one == 0)
    {
        if(new_one == 0 || new_one == 1 || new_one == 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(pre_one == 1)
    {
        if(new_one == 0 || new_one == 2)
        {
            return true;
        }
        else{
            return false;
        }
    }
    else if(pre_one == 2)
    {
        if(new_one == 0 || new_one==2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(pre_one == 3)
    {
        if(new_one == 1 || new_one == 3)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool solve(char M[100][100],int Mt[100][100],int x,int y,int column,int row,int record)
{
    //cout << "my pos: " << x << y << M[y][x]<< endl;//still have problem about unlimit loop and bad answer ();
    //printMatrix(column,row,Matrix_check);
    route.Push(M[y][x]);
    Matrix_check[y][x] = 0;
    if(y == column-1&& x==row-1)
    {
        if(bracketValid(route)==true)
        {
            return true;
        }
        else
        {

            //return false;
            if(record == 1)
            {
                Matrix_check[y][x] = 1;
                y = y-1;//back one step
                //cout << "my pos: " << x << y << M[y][x]<< endl;
                route.Pop();
                return false;
            }
            else if(record == 2)
            {
                Matrix_check[y][x] = 1;
                x = x-1;
                //cout << "my pos: " << x << y << M[y][x]<< endl;
                route.Pop();
                return false;
            }
            else if(record == 3)
            {
                Matrix_check[y][x] = 1;
                x = x+1;
                //cout << "my pos: " << x << y << M[y][x]<< endl;
                route.Pop();
                return false;
            }
            else if(record == 4)
            {
                Matrix_check[y][x] = 1;
                y = y+1;
                //cout << "my pos: " << x << y << M[y][x]<< endl;
                route.Pop();
                return false;
            }
            else
            {
                Matrix_check[y][x] = 1;
                return false;
            }

        }

    }

    if(y< column-1 && evaluation_function(Mt[y][x],Mt[y+1][x]) && record !=4 && Matrix_check[y+1][x] !=0 && solve(M,Mt,x,y+1,column,row,1) )
    {
        return true;
    }
    if(x <row-1 && evaluation_function(Mt[y][x],Mt[y][x+1]) && record != 3 && Matrix_check[y][x+1] !=0 &&solve(M,Mt,x+1,y,column,row,2) )
    {
        return true;
    }
    if(x>0&& evaluation_function(Mt[y][x],Mt[y][x-1]) && record != 2 &&Matrix_check[y][x-1] !=0 && solve(M,Mt,x-1,y,column,row,3))
    {
        return true;
    }
    if(y>0 && evaluation_function(Mt[y][x],Mt[y-1][x]) && record != 1 && Matrix_check[y-1][x] !=0 && solve(M,Mt,x,y-1,column,row,4))
    {
        return true;
    }
    if(record == 1)
    {
        Matrix_check[y][x] = 1;
        y = y-1;//back one step
        //cout << "my pos: " << x << y << M[y][x]<< endl;
        route.Pop();
        return false;
    }
    else if(record == 2)
    {
        Matrix_check[y][x] = 1;
        x = x-1;
        //cout << "my pos: " << x << y << M[y][x]<< endl;
        route.Pop();
        return false;
    }
    else if(record == 3)
    {
        Matrix_check[y][x] = 1;
        x = x+1;
        //cout << "my pos: " << x << y << M[y][x]<< endl;
        route.Pop();
        return false;
    }
    else if(record == 4)
    {
        Matrix_check[y][x] = 1;
        y = y+1;
        //cout << "my pos: " << x << y << M[y][x]<< endl;
        route.Pop();
        return false;
    }
    else
    {
        Matrix_check[y][x] = 1;
        return false; //we cannot go any step further
    }

}

bool bracketValid(StackArray route)
{
    int countBra = 0;
    int countKet = 0;
    while(!route.IsEmpty())
    {
        if(route.Top() == '(')
        {
            countBra = countBra+1;
            if(countBra + countKet == 1)//last element can not be bra
            {
                return false;
            }
        }
        if(route.Top()== ')')
        {
            countKet = countKet+1;
        }
        route.Pop();
    }
    return (countBra==countKet);
}

string presentation(string s)
{
    string revise;
    int length = 0;
    length = s.length();
    for(int i = 0; i < length ;i++)
    {
        if((isDigit(s[i]) != isDigit(s[i-1]) ||  isOperator(s[i]) != isOperator(s[i-1]) || isFrontbraket(s[i]) != isFrontbraket(s[i-1]) || isBackbraket(s[i]) != isBackbraket(s[i-1]) )&& i!=0)
        {
            revise = revise+" ";
        }
        if(i!= 0&&((isFrontbraket(s[i])==1&&isFrontbraket(s[i-1])==1)||(isBackbraket(s[i])==1&&isBackbraket(s[i-1])==1)))
        {
            revise = revise+" ";
        }
        if(isDigit(s[i]) == 1)
        {
            revise = revise + s[i];
        }
        else if(isDigit(s[i])== 0)
        {
            revise = revise + s[i];
        }
    }
    //cout << revise <<endl;
    revise = revise + " " ;
    return revise;
}

int priority(char op)
{
    /*switch(op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;

    }*/
    if(op == '+' || op=='-')
    {
        return 1;
    }
    else if(op == '*' || op=='/')
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

void printMatrix(int column,int row,int Matrix[100][100])
{
    for(int i = 0 ; i<column ; i++)//repeat all input matrix
    {
        for(int j = 0; j<row;j++)
        {
            if(j == row-1)
            {
                cout << Matrix[i][j];
                cout << endl;
            }
            else
            {
                cout << Matrix[i][j]<<" ";
            }
        }
    }

}
