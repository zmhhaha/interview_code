#include <iostream>
#include <queue>
#include <string>
using namespace std;

int ans;

class Node
{
public:
	Node(int value) : _pLeft(nullptr), _pRight(nullptr), _value(value) { }

	~Node()
	{
		delete _pLeft;
		delete _pRight;
	}

public:
	int _value;
	Node* _pLeft;
	Node* _pRight;
};

Node* makeTree()
{
	int rootValue;
	cin >> rootValue;

	Node* pRoot = new Node(rootValue);
	queue<Node*> nodes;
	nodes.push(pRoot);

	while (!nodes.empty())
	{
		Node* pNode = nodes.front();
		nodes.pop();

		int leftValue, rightValue;
		cin >> leftValue >> rightValue;

		if (leftValue != -1)
		{
			pNode->_pLeft = new Node(leftValue);
			nodes.push(pNode->_pLeft);
		}
		if (rightValue != -1)
		{
			pNode->_pRight = new Node(rightValue);
			nodes.push(pNode->_pRight);
		}
	}

	return pRoot;
}

void dfs(Node* pRoot, int cur) {
	if (!pRoot) return;
	cur = cur * 10 + pRoot->_value;
	if (!pRoot->_pLeft&&!pRoot->_pRight) {
		ans += cur;
		return;
	}
	dfs(pRoot->_pLeft, cur);
	dfs(pRoot->_pRight, cur);
}

int sumPath(Node* pRoot)
{
	ans = 0;
	dfs(pRoot, ans);
	return ans;
}

int main()
{	
	Node* pRoot = makeTree();
	cout << sumPath(pRoot) << endl;

	delete pRoot;
	return 0;
}
