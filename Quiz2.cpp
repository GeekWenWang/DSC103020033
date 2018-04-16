#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

class LinkedList;

class ListNode{
private:
    string name;
    string gift;
    ListNode *next;
public:
    ListNode():name(""),gift(""),next(0){};
    ListNode(string sn,string sg):name(sn),gift(sg),next(0){};

    friend class LinkedList;
};
class LinkedList{
private:
    ListNode  *first;
public:
    LinkedList():first(0){};
    void PrintList();
    void Push_back(string sn,string sg);
    void Delete(string sn);
    bool Search(string sn);
    bool IsEmpty();
};

void LinkedList::PrintList(){
    if(first == 0){
        //cout<< "List is empty.\n";
        return;
    }
    ListNode *current = first;
    while(current !=0)
    {
        if(current == first)
        {
            cout << "(" << current->name << "," << current->gift << ")";
            current = current->next;
            //return;
        }
        else
        {
            cout << "->" ;
            cout <<"(" << current->name << "," << current->gift << ")";
            current = current->next;
            //return;
        }

    }
    //cout <<endl;
}

void LinkedList::Push_back(string sn,string sg){
    ListNode *newNode = new ListNode(sn,sg);
    if(first == 0){
        first = newNode;
        return;
    }
    ListNode *current = first;
    while(current->next != 0){
        current = current->next;
    }
    current->next = newNode;
}

void LinkedList::Delete(string sn){
    ListNode *current = first;
    ListNode *previous = 0;
    while(current != 0 && current->name != sn){
        previous = current;
        current = current->next;
    }
    if(current == 0){
        //cout << "There is no" << sn <<"in list.\n";
    }
    else if(current ==first){
        first = current->next;
        delete current;
        current = 0;
    }
    else{
        previous->next = current->next;
        delete current;
        current = 0;
    }
}

bool LinkedList::Search(string sn)
{
    ListNode *current = first;
    ListNode *previous = 0;
    while(current != 0 && current->name != sn){
        previous = current;
        current = current->next;
    }
    if(current == 0){
        return false;
    }
    else{return true;}
}

bool LinkedList::IsEmpty()
{
    if(first == 0){
        //cout<< "List is empty.\n";
        return true;
    }
    else{return false;}
}
LinkedList giftList;
LinkedList naughtyList;


int commandToInt(string command);


int main()
{
    string command = "";
    int commandNum = 0;
    int test = 0;
    int test_count = 0;
    string name = "";
    string gift = "";


    //giftList.PrintList();
    cin >> command;

    //cout << command << endl;

    commandNum = commandToInt(command);

    //cout << commandNum << endl;

    while(commandNum != 4)
    {

        commandNum = commandToInt(command);
        switch(commandNum)
        {
        case 1:
            cin >>test;
            while(test != 0)
            {
                test_count += 1;
                name = "";
                gift = "";
                cin >> name;
                cin >> gift;
                if(giftList.Search(name) == true)
                {
                    giftList.Delete(name);
                    giftList.Push_back(name,gift);
                }
                else
                {
                    giftList.Push_back(name,gift);
                }
                //giftList.Push_back(name,gift);
                /*if(test_count != 1)
                {
                    cout << "->" ;
                }*/
                //giftList.PrintList();

                test = test -1;
            }
            cin >> command;
            break;
        case 2:
            cin >>test;
            while(test != 0)
            {
                name = "";
                gift = "";
                cin >> name;
                cin >> gift;
                if(giftList.Search(name) == true)
                {
                    //giftList.Delete(name);
                    //giftList.Push_back(name,gift);
                }
                else
                {
                    giftList.Push_back(name,gift);
                }

                if(naughtyList.Search(name) == true)
                {
                    naughtyList.Delete(name);
                }
                //giftList.PrintList();
                //cout << "->" ;
                test = test -1;
            }
            cin >> command;
            break;
        case 3:
            cin >>test;
            while(test != 0)
            {
                name = "";
                cin >> name;
                //naughtyList.Push_back(name,"coal");
                if(giftList.Search(name)==true)
                {
                    giftList.Delete(name);
                    naughtyList.Push_back(name,"coal");

                }
                //else{naughtyList.Push_back(name,"coal");}
                if(naughtyList.Search(name)==true)
                {
                   naughtyList.Delete(name);
                   naughtyList.Push_back(name,"coal");
                }

                //giftList.PrintList();
                test = test -1;
            }
            cin >> command;
            break;
        case 4:
            if(giftList.IsEmpty() && naughtyList.IsEmpty() || (giftList.IsEmpty()))
            {
                cout << "Empty" <<endl;
                return 0;
            }
            else{
                cout<<"SantaFinalList"<<endl;
            }

            break;
        case -1:
            return 0;
        }
    }
    giftList.PrintList();
    if(naughtyList.IsEmpty() == false)
    {
        cout << "->" ;
        naughtyList.PrintList();
        cout <<endl;

    }
    else
    {
        cout <<endl;
    }
    /*cout << "->" ;
    naughtyList.PrintList();
    cout <<endl;*/

    //system("pause");



    return 0;
}

int commandToInt(string command)
{
    if(command == "SantaList")
    {
        return 1;
    }
    if(command == "AppendList")
    {
        return 2;
    }
    if(command == "NaughtyKid")
    {
        return 3;
    }
    if(command == "End")
    {
        return 4;
    }
    else{return -1;}
}
