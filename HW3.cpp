#include<iostream>
#include<string>

using namespace std;

/*referrence:http://alrightchiu.github.io/SecondRound/linked-list-introjian-jie.html*/
class LinkedList;

class ListNode{
    private:
        string gift;
        int price;
        ListNode *next;
    public:
        ListNode():gift(""),price(0),next(0){};
        ListNode(string gn,int p):gift(gn),price(p),next(0){};

        friend class LinkedList;
    };

class LinkedList{
private:
    ListNode *first;
public:
    LinkedList():first(0){};
    bool IsEmpty();
    void PrintList();
    bool Search(int price);
    void Push_back(string gift,int price);
    void InsertAfter(string gift,int price,int priceToInsertAfter);
    void Delete(int price);
    void Reverse();
    };

void LinkedList::PrintList()
{
    if(first == 0){
        //cout<< "List is empty.\n";
        return;
    }
    ListNode *current = first;
    while(current !=0)
    {
        if(current == first)
        {
            cout << "(" << current->gift << "," << current->price << ")";
            current = current->next;
            //return;
        }
        else
        {
            cout << "->" ;
            cout <<"(" << current->gift << "," << current->price << ")";
            current = current->next;
            //return;
        }

    }
    cout << endl;

}

void LinkedList::Push_back(string gift,int price){
    ListNode *newNode = new ListNode(gift,price);
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

void LinkedList::Delete(int price){
    ListNode *current = first;
    ListNode *previous = 0;
    while(current != 0 && current->price != price){
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

bool LinkedList::Search(int price)
{
    ListNode *current = first;
    ListNode *previous = 0;
    while(current != 0 && current->price != price){
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

void LinkedList::InsertAfter(string gift,int price,int priceToInsertAfter)
{
    ListNode *newNode = new ListNode(gift,price);
    newNode->next = 0;
    ListNode *current = first;
    while(current->price != priceToInsertAfter)
    {
        //cout << current->price;
        /*if(current->price == priceToInsertAfter)
        {
            newNode->next = current->next;
            current->next = newNode;
        }*/
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}

void LinkedList::Reverse(){
    if(first ==0 || first->next==0){

        return;
    }
    ListNode *previous=0,
            *current = first,
            *preceding = first->next;
    while(preceding != 0)
    {
        current->next = previous;
        previous = current;
        current = preceding;
        preceding = preceding->next;
    }
    current->next = previous;
    first = current;
}

LinkedList giftList;

int commandToInteger(string command);

int main()
{

    string command = "";
    while(cin >> command)
    {
        int command_num = 0;
        string nameOfGift = "";
        int price = 0;
        int priceToInsertAfter = 0;
        command_num = commandToInteger(command);

        switch(command_num)
        {
        case 0:
        return 0;
        case 1:
            nameOfGift = "";
            price = 0;
            cin >> nameOfGift;
            cin >> price;
            if(!giftList.Search(price) && price>=0 && price < 1000)
            {
                giftList.Push_back(nameOfGift,price);
            }
            break;
        case 2:
            nameOfGift = "";
            price = 0;
            priceToInsertAfter = 0;
            cin >> nameOfGift;
            cin >> price;
            cin >> priceToInsertAfter;
            if(giftList.Search(priceToInsertAfter) && price>=0 && price < 1000)
            {
                if(!giftList.Search(price))
                {
                    giftList.InsertAfter(nameOfGift,price,priceToInsertAfter);
                }

            }
            break;
        case 3:
            nameOfGift = "";
            price = 0;
            cin >> price;
            if(giftList.Search(price))
            {
                giftList.Delete(price);
            }

            break;
        case 4:
            giftList.Reverse();
            break;
        case 5:
            if(giftList.IsEmpty())
            {
                cout << "Empty" << endl;
            }
            else
            {
                cout << "List" <<endl;
                giftList.PrintList();
            }

            return 0;
        }
    }

    return 0;
}

int commandToInteger(string command)
{
    if (command == "InsertBack")
    {
        return 1;
    }
    else if(command == "InsertAfter")
    {
        return 2;
    }
    else if(command == "Delete")
    {
        return 3;
    }
    else if(command == "Reverse")
    {
        return 4;
    }
    else if(command == "End")
    {
        return 5;
    }
    else{return 0;}
}

