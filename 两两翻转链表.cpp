#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
	Node(int value) : _next(nullptr), _value(value) { }

	~Node()
	{
		delete _next;
	}

public:
	int _value;
	Node* _next;
};

Node* makeList()
{
	int rootValue;
	Node* head = new Node(-1);
	Node* pRoot = head;
	while (cin >> rootValue) {
		if (rootValue == -1) break;
		head->_next = new Node(rootValue);
        head=head->_next;
        //printf("%d\n",rootValue);
	}
    /*while(pRoot){
        cout << pRoot->_value << endl;
        pRoot=pRoot->_next;
    }*/
	return pRoot->_next;
}

Node* helper(Node* head)
{
    if(!head) return head;
    if(!head->_next) return head;
	Node* one=head;
    Node* two=head->_next;
    Node* last=two->_next;
    one->_next=helper(last);
    two->_next=one;
    return two;
}

int main()
{
	Node* pRoot = makeList();
    if(!pRoot) return 0;
    if(!pRoot->_next) {
        cout<< pRoot->_value<<endl;
        return 0;
    } 
    Node* ans=pRoot->_next;
    helper(pRoot);
    while(ans){
        cout<<ans->_value<<endl;
        ans=ans->_next;
    }
	delete pRoot;
	return 0;
}