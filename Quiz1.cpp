#include <iostream>
#include <cstdlib>
#include <stack>

using namespace std;

int MatrixValid[200][200] = {0};

bool eval(int pre,int next);
bool solve(int matrix[200][200], int x,int y ,int column , int row);
void printMatrix(int column,int row,int Matrix[200][200]);

int main()
{
    int test_count = 0;
    int test = 0;
    cin >> test;
    //cout << test <<endl;

    for(int i = 0 ; i<200 ; i++)
    {
        for(int j = 0; j<200;j++)
        {
            MatrixValid[i][j] = 1;
        }
    }

    while(test != 0)
    {
        test_count += 1;
        int column = 0;
        int row = 0;
        cin>>row>>column;
        //int x,y = 0;
        int matrix[200][200] = {0};


        for(int i = 0 ; i<column ; i++)
        {
            for(int j = 0; j<row;j++)
            {
                cin >>matrix[i][j];
            }
        }
        /*for(int i = 0 ; i<column ; i++)
        {
            for(int j = 0; j<row;j++)
            {
                MatrixValid[i][j] = 1;
            }
        }*/

        stack<int> mystack;
        if(test_count == 1)
        {
        if(solve(matrix,0,0,column,row))
        {
            cout <<test<< endl;
            cout << row << endl;
            cout << column << endl;

            for(int i = 0 ; i<column ; i++)
            {
                for(int j = 0; j<row;j++)
                {
                    if(j == row-1)
                    {
                        cout << matrix[i][j];
                        cout << endl;

                    }

                    else{
                        cout << matrix[i][j]<<" ";
                    }
                }
            }


            cout << "Yes" <<endl;
        }
        else
        {
            cout << test <<endl;
            cout << row << endl;
            cout << column << endl;
            for(int i = 0 ; i<column ; i++)
            {
            for(int j = 0; j<row;j++)
            {

                if(j == row-1)
                {
                    cout << matrix[i][j];
                    cout << endl;
                }
                else{
                cout << matrix[i][j]<< " ";
                }
            }
            }


            cout << "No"<<endl;
        }
        }

        else
        {
         if(solve(matrix,0,0,column,row))
        {
            //cout <<test<< endl;
            cout << row << endl;
            cout << column << endl;

            for(int i = 0 ; i<column ; i++)
            {
                for(int j = 0; j<row;j++)
                {
                    if(j == row-1)
                    {
                        cout << matrix[i][j];
                        cout << endl;

                    }

                    else{
                        cout << matrix[i][j]<<" ";
                    }
                }
            }


            cout << "Yes" <<endl;
        }
        else
        {
            //cout << test <<endl;
            cout << row << endl;
            cout << column << endl;
            for(int i = 0 ; i<column ; i++)
            {
            for(int j = 0; j<row;j++)
            {

                if(j == row-1)
                {
                    cout << matrix[i][j];
                    cout << endl;
                }
                else{
                cout << matrix[i][j]<< " ";
                }
            }
            }


            cout << "No"<<endl;
        }

        }
        //printMatrix(column,50,MatrixValid);
        for(int i = 0 ; i<column ; i++)
        {
            for(int j = 0; j<row;j++)
            {
                if(MatrixValid[i][j] != 1)
                {
                    MatrixValid[i][j] = 1;
                }
            }
        }
        test = test-1;
    }

    return 0;
}

bool eval(int pre,int next)
{
    if(next%pre==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool solve(int matrix[200][200], int x,int y,int column,int row)
{
    //cout << y << x << matrix[y][x] << endl;
    MatrixValid[y][x] = 0;
    //printMatrix(column,row,MatrixValid);

    if(y == column-1 && x== row -1)
    {
        return true;
    }
    if(x<row-1 && eval(matrix[y][x],matrix[y][x+1]) &&  MatrixValid[y][x+1]==1 && solve(matrix,x+1,y,column,row)   )
    {
        return true;
    }
    if(y< column-1 &&eval(matrix[y][x],matrix[y+1][x])&&  MatrixValid[y+1][x]==1 && solve(matrix,x,y+1,column,row)   )
    {
        return  true;
    }
    if(x>0 && eval(matrix[y][x],matrix[y][x-1])&&  MatrixValid[y][x-1]==1 && solve(matrix,x-1,y,column,row)   )
    {
        return true;
    }

    if(y>0 && eval(matrix[y][x],matrix[y-1][x])&&  MatrixValid[y-1][x]==1 && solve(matrix,x,y-1,column,row)   )
    {
        return true;
    }


    //cout << y << x << matrix[y][x] << endl;
    //matrix[y][x] = 1;
    MatrixValid[y][x] = 2;

    return false;

}


void printMatrix(int column,int row,int Matrix[200][200])
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
