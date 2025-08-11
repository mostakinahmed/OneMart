#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int val;
    Node *next;
    Node *prev;
    Node(int val){
        this->val=val;
        this->next=NULL;
        this->prev=NULL;
    }
};

class mystack{
    public:
    Node *head=NULL;
    Node *tail=NULL;
    int sz=0;
    void spush(int val){sz++;
        Node *newnode=new Node(val);
        if(head==NULL){head=newnode;tail=newnode;return;}
        tail->next=newnode;
        newnode->prev=tail;
        tail=newnode;
    }
    void spop(){sz--;
        Node *deletenode=tail;
        tail=tail->prev;
        delete deletenode;
        if(tail==NULL){head=NULL;return ;}
    }
    int top(){return tail->val;}
   int ssize(){return sz;}
   bool sempty(){
    if(head==NULL)return true; 
    else return false;
   }
};
class myqueue{
 public:
    Node *head=NULL;
    Node *tail=NULL;
    int qsz=0;
void qpush(int val){qsz++;
        Node *newnode=new Node(val);
        if(head==NULL){head=newnode;tail=newnode;return;}
        tail->next=newnode;
        newnode->prev=tail;
        tail=newnode;
    }
void qpop(){qsz--;
        Node *deletenode=head;
        head=head->next;
        delete deletenode;
        if(head==NULL){tail=NULL;return ;}
    }
int front(){return head->val;}
int qsize(){return qsz;}
bool qempty(){return head==NULL;}
};
int main()
{
    int n,m;
    cin >> n,m;
    mystack a;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        a.spush(val);
    }

    myqueue b;
    for (int i = 0; i < m; i++)
    {
        int val;
        cin >> val;
        b.qpush(val);
    }

    if (a.ssize() != b.qsize())
    {
        cout << "NO";
    }
    else
    {
        bool flag = true;
        while (!a.sempty() && !b.qempty())
        {
            if (a.top() != b.front())
            {
                flag = false;
                break;
            }
            a.spop();
            b.qpop();
        }
        if (flag == true)
        {
            cout << "YES";
        }
        else
        {
            cout << "NO";
        }
    }

    return 0;
}