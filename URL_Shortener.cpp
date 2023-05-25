#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

class Node
{
public:
    string first;
    string second;

    Node(string first, string second)
    {
        this->first = first;
        this->second = second;
    }
};

class ListNode
{
public:
    Node *pair;
    ListNode *next;

    ListNode(Node *pair)
    {
        this->pair = pair;
        this->next = NULL;
    }

    ~ListNode()
    {
        string val = this->pair->first;
        string val2 = this->pair->second;

        if (this->next != NULL)
        {
            this->next = NULL;
            delete next;
        }
        cout << "\nRecord with data "
             << " '" << val << " : " << val2 << "' "
             << " is deleted.\n";
    }
};

void insertAtHead(ListNode *&head, string f, string s)
{
    ListNode *newNode = new ListNode(new Node(f, s));
    if (head == NULL)
    {
        head = newNode;
        return;
    }

    newNode->next = head;
    head = newNode;
}

void insertAtTail(ListNode *&head, string f, string s)
{
    ListNode *newNode = new ListNode(new Node(f, s));

    ListNode *temp = head;
    if (temp == NULL)
    {
        head = newNode;
        return;
    }

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void deleteHead(ListNode *&head)
{
    ListNode *temp = head;
    if (temp == NULL)
    {
        cout << "List is empty!!!\n";
        return;
    }

    head = temp->next;
    delete temp;
}

void deleteTail(ListNode *&head)
{
    ListNode *temp = head;
    if (temp == NULL)
    {
        cout << "List is empty!!!\n";
        return;
    }
    ListNode *prev = temp;
    while (temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    delete temp;
}

void deleteKeyNode(ListNode *&head)
{
    cout << "Enter a short URL to be deleted\n";
    string f;
    cin >> f;
    ListNode *temp = head;
    if (temp == NULL)
    {
        cout << "List is empty!!!\n";
        return;
    }
    if (temp->pair->first == f)
    {
        deleteHead(head);
        return;
    }

    ListNode *prev = temp;
    while (temp->pair->first != f && temp != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    if (!temp)
    {
        cout << "Key not found!\n";
        return;
    }

    prev->next = temp->next;
    delete temp;
}

pair<string, bool> searchKeyNode(ListNode *&head, string &f)
{

    ListNode *temp = head;
    if (temp == NULL)
    {
        return {"", false};
    }
    if (temp->pair->first == f)
    {
        return {temp->pair->second, true};
    }

    ListNode *prev = temp;
    while (temp != NULL && temp->pair->first != f)
    {
        prev = temp;
        temp = temp->next;
    }

    if (!temp)
    {
        return {"", false};
    }
    return {temp->pair->second, true};
}

void display(ListNode *&head)
{
    ListNode *temp = head;
    if (temp == NULL)
    {
        cout << "\nEmpty !!!\n";
        return;
    }

    cout << "\nYour history: \n\n";
    while (temp != NULL)
    {
        cout << temp->pair->first << " : " << temp->pair->second << endl;
        temp = temp->next;
    }
    cout << endl;
}

void openWebsite(ListNode *&head){
    ListNode *temp = head;
    cout<<"\nEnter the short URL : ";
    string str;
    cin>>str;
    while(temp->pair->first != str){
        temp = temp->next;
    }
    if(temp->pair->first == str){
        string s = temp->pair->second;
        char* char_arr = &s[0];
        ShellExecute(NULL, "open", char_arr, NULL, NULL, SW_SHOWNORMAL);
        cout<<"\nURL opened on browser !!!"<<endl;
    }else{
        cout<<"\nNo such short URL was created."<<endl;
    }
}

int hashfunc0(int num)
{
    int number = (num % 3) + 1;
    return number;
}

char hashfunc1(int num)
{
    int number = (num % 26) + 97;
    return char(number);
}

char hashfunc2(int num)
{
    int number = (num % 26) + 65;
    return char(number);
}

char hashfunc3(int num)
{
    int number = (num % 10) + 48;
    return char(number);
}

string hashKey()
{
    int num;
    char c;
    string str = "";
    for (int i = 0; i < 6; i++)
    {
        int n = hashfunc0(rand());
        switch (n)
        {
        case 1:
        {
            // c = hashfunc2(hashfunc1(rand()));
            c = hashfunc1(rand());
            str.push_back(c);
            break;
        }
        case 2:
        {
            // c = hashfunc1(hashfunc2(rand()));
            c = hashfunc2(rand());
            str.push_back(c);
            break;
        }
        case 3:
        {
            c = hashfunc3(rand());
            str.push_back(c);
            break;
        }
        }
    }
    return str;
}

void encode(ListNode *&head)
{
    cout << "\nEnter the link --> ";
    string longURL;
    cin >> longURL;
    string header = "https://shrinkr.com/";
    string str = hashKey();

    // cout << str  << endl;
    pair<string, bool> p = searchKeyNode(head, str);
    // cout << p.first << endl;
    // cout << p.second<< endl;
    while (p.second)
    {
        str += hashKey();
    }

    string shortURL = header + str;
    insertAtTail(head, shortURL, longURL);
    cout << "\nShort URL for above link --> " << shortURL << endl;
}

void decode(ListNode *&head)
{
    cout << "\nEnter the short URL --> ";
    string shortURL;
    cin >> shortURL;
    pair<string, bool> p = searchKeyNode(head, shortURL);
    if (p.second)
    {
        cout << "\nOriginal link --> ";
        cout << p.first << endl;
    }
    else
    {
        cout << "\nNo such short URL was created before." << endl;
    }
}

void program(ListNode *&head)
{
    cout << "\nChoose the operation --> " << endl;
    cout << "1) Create short URL \n2) Get the original link from short URL \n3) My history \n4) Delete history element \n5) Open website using short URL \n6) Exit \n"
         << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {

    case 1:
    {
        encode(head);
        program(head);
        break;
    }

    case 2:
    {
        decode(head);
        program(head);
        break;
    }

    case 3:
    {
        display(head);
        program(head);
        break;
    }

    case 4:
    {
        deleteKeyNode(head);
        program(head);
        break;
    }

    case 5:
    {
        openWebsite(head);
        program(head);
        break;
    }

    case 6:
    {
        cout << "\nExited Successfully !!!" << endl;
        return;
    }

    default:
    {
        cout << "\nOperation not available !" << endl;
        program(head);
    }
    }
}

int main()
{
    ListNode *head = NULL;
    srand(time(nullptr));
    program(head);
    return 0;
}