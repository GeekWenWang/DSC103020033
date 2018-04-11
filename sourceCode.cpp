#include "iostream"
#include <string>

using namespace std;

int recursion_check(string s);
string generate_s(string s, int n);
string cut_a_string(string s, int pos);
string recursive_number_check(string s,int n_ignore);

int main(void)
{
    int n_ignore = 0; //tolerence you can delete
    int start = 0;
    //cin<< n <<endl;
    cin >> n_ignore;
    string s;

    while(getline(cin,s))
    {
        int checkValid=0;
        if(start)
        {
            checkValid = recursion_check(s);
            if(checkValid == 1)
            {
                cout<<"Yes"<<endl;
            }
            else
            {
                //cout <<generate_s(s,checkValid);
                /*while(n_ignore>0)
                {
                    n_ignore = n_ignore -1;
                    s = generate_s(s,checkValid);
                    s.erase(0,1);
                    checkValid = recursion_check(s);
                    if(checkValid == 1)
                    {
                        cout<<"Yes"<<endl;
                        break;
                    }
                    else
                    {
                        cout<<"No"<<endl;
                        break;
                    }
                }*/
                cout<<recursive_number_check(s,n_ignore)<<endl;

            }
        }
        else
        {
            start = 1;
        }
    }
    return 0;
}

int recursion_check(string s)
{
    int lengthOfLine = 0;
    lengthOfLine = s.length();
    //cout<<"origin:"<<s<<endl;
    //cout<<"lengthOfLine  "<<lengthOfLine<<endl;
    if(lengthOfLine>1)
    {
        if(s[0]==s[lengthOfLine-1])
        {
            s.erase(0,1);
            s.erase(lengthOfLine-2,1);
            //cout<<"recusivecheck:"<<s<<endl;
            return recursion_check(s);
        }
        else
        {
            //cout<<s<<endl;
            return lengthOfLine;
        }
    }
    else
    {
        return 1;
    }
}

string generate_s(string s, int length)
{
    int origin_length =0;
    origin_length = s.length();
    int erase_parameter = 0;
    //cout << origin_length <<length<<endl;
    erase_parameter = (origin_length - length)/2;
    //cout<<"origin_gen"<<s<<endl;
    s.erase(0,erase_parameter);
    s.erase(origin_length-erase_parameter-erase_parameter,erase_parameter);
    //cout<<"origin_gen_out"<<s<<endl;
    return s;
}

string cut_a_string(string s, int pos)
{
    s.erase(pos,1);
    return s;
}

string recursive_number_check(string s,int n_ignore)
{
    int lengthOfString = 0;
    lengthOfString = s.length();
    //cout<<"n_ignore"<<n_ignore<<endl;
    //cout<<"lengthOfString" <<lengthOfString<<endl;
    //cout<<"string"<<s<<endl;
    if(s[0]!=s[lengthOfString-1])
    {
        //cout<<"number_of_text" << recursion_check(cut_a_string(s,0)) <<endl;
        if(n_ignore>0)
        {
            if((recursive_number_check(cut_a_string(s,0),n_ignore-1))=="Yes" || (recursive_number_check(cut_a_string(s,lengthOfString-1),n_ignore-1))=="Yes")
            {
                return "Yes";
            }
            else
            {
                return "No";

            }
        }
        else
        {
            return "No";
        }
    }
    else
    {
        int checkValid = 0;
        checkValid = recursion_check(s);
        if(checkValid == 1)
        {
            return "Yes";
        }
        else
        {


            s = generate_s(s,checkValid);
            //cout <<"check_Valid"<< checkValid<<endl;
            //cout<<"gen_s: "<<s<<endl;
            return recursive_number_check(s,n_ignore);


        }
    }

}
