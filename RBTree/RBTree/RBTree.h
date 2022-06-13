#pragma once

//枚举，定义红与黑
enum Colour
{
	RED,
	BLACK
};

template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	pair<K, V> _kv;
	
	Colour _col;//颜色

	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}

};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
private:
	Node* _root;
public:
	RBTree()
		:_root(nullptr)
	{}
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		cur->_col = RED;//新增节点
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		

		//控制平衡
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent = grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				//1.uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					//变色+继续处理
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle不存在且为黑
				{

					//        g
					//     p
					//  c

					//        g
					//     p
					//        c

					if (cur = parent->_left)
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						// 双旋
						RotateL(parent);
						RotateR(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else//if (parent = grandfather->_right)
			{
				Node* uncle = grandfather->_left;
				//1.uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					//变色+继续处理
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle不存在且为黑
				{

					//  g    
					//     p
					//        c

					//  g
					//     p
					//  c

					if (cur = parent->_right)
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateR(parent);
						RotateL(grandfather);
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		_root->_col = BLACK;

		return true;
	}



	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		Node* parentParent = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subR;
			else
				parentParent->_right = subR;
			subR->_parent = parentParent;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		Node* parentParent = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (parentParent->_left == parent)
				parentParent->_left = subL;
			else
				parentParent->_right = subL;

			subL->_parent = parentParent;
		}
	}


	//打印函数(中序)
	void InOrder()
	{
		_InOrder(_root);
	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}


	//检查树
	bool IsBalance()
	{
		if (_root && _root->_col == RED)
		{
			cout << "根节点不是黑色" << endl;
			return false;
		}

		// 最左路径黑色节点数量做基准值
		int banchmark = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_col == BLACK)
			{
				++banchmark;
			}
			left = left->_left;
		}

		int blackNum = 0;
		return _IsBalance(_root, banchmark, blackNum);
	}

	bool _IsBalance(Node* root, int banchmark, int blackNum)
	{
		if (root == nullptr)
		{
			if (banchmark != blackNum)
			{
				cout << "存在路径黑色节点的数量不相等" << endl;
				return false;
			}

			return true;
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "出现连续红色节点" << endl;
			return false;
		}

		if (root->_col == BLACK)
		{
			++blackNum;
		}

		return _IsBalance(root->_left, banchmark, blackNum) && _IsBalance(root->_right, banchmark, blackNum);
	}

	int Height()
	{
		return _Height(_root);
	}

	int _Height(Node* root)
	{
		if (root == NULL)
			return 0;
		int leftHeight = _Height(root->_left);
		int rightHeight = _Height(root->_right);
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}
};



//void TestRBTree()
//{
//	RBTree<int, int> t;
//	//int a[] = { 5, 4, 3, 2, 1, 0 };
//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//	for (auto& e : a)
//	{
//		t.Insert(make_pair(e, e));
//	}
//	t.InOrder();
//}

void TestRBTree()
{
	RBTree<int, int> t;
	vector<int> v;
	srand(time(0));
	int N = 100000000;
	for (int i = 0; i < N; ++i)
	{
		//v.push_back(rand());
		v.push_back(i);
	}
	//int a[] = {5,4,3,2,1,0};
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
		/*if (!t.IsBalance())
		{
		cout << "Insert" << e << endl;
		}*/
	}
	//t.InOrder();
	//cout << t.IsBalance() << endl;
	cout << "高度:" << t.Height() << endl;
}


