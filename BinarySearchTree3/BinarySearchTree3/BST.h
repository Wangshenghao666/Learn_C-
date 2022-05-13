#pragma once


//key
template<class K>

struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
	{

	}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	BSTree()
		:_root(nullptr)
	{

	}
	//Insert实现
	bool Insert(const K& key)
	{
		_Insert(_root, key);
		return true;
	}

	//删除
	bool Erase(const K& key)
	{
		_Erase(_root, key);
		return true;
	}

	//中序遍历
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	//查找
	Node* FindR(const K& key)
	{
		_FindR(_root, key);
	}
private:
	Node* _Find(Node* root, const K& key)
	{
		if (root == nullptr)
		{
			return nullptr;
		}
		if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else
		{
			return root;
		}
	}
	bool _Insert(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key < key)
		{
			return _Insert(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _Insert(root->_left, key);
		}
		else
		{
			return false;
		}
	}
	bool _Erase(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			return false;
		}
		if (root->_key < key)
		{
			return _Erase(root->_right, key);
		}
		else if (root->_key > key)
		{
			return _Erase(root->_left, key);
		}
		else
		{
			Node* del = root;
			if (root->_left == nullptr)
			{
				root = root->_right;
				delete del;

			}
			else if (root->_right == nullptr)
			{
				root = root->_left;
				delete del;

			}

			else
			{
				Node* min = root->_right;
				while (min->_left)
				{
					min = min->_left;
				}
				swap(min->_key, root->_key);
				return _Erase(root->_right, key);
			}
		}
		return true;
	}
protected:
	Node* _root;
};

void TestBSTree()
{
	BSTree<int> t;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
	t.Erase(7);
	t.InOrder();

	t.Erase(5);
	t.InOrder();

	t.Erase(0);
	t.InOrder();

	t.Erase(1);
	t.InOrder();

	for (auto e : a)
	{
		t.Erase(e);
		t.InOrder();
	}
	t.InOrder();

}
