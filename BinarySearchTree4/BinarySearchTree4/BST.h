#pragma once

////key模型
//namespace K
//{
//	template<class K>
//	struct BSTreeNode
//	{
//		BSTreeNode<K>* _left;
//		BSTreeNode<K>* _right;
//		K _key;
//
//		BSTreeNode(const K& key)
//			:_left(nullptr)
//			, _right(nullptr)
//			, _key(key)
//		{
//
//		}
//	};
//
//	template<class K>
//	class BSTree
//	{
//		typedef BSTreeNode<K> Node;
//	public:
//		BSTree()
//			:_root(nullptr)
//		{
//
//		}
//		//Insert实现
//		bool Insert(const K& key)
//		{
//			if (_root == nullptr)
//			{
//				_root = new Node(key);
//				return true;
//			}
//			Node* parent = nullptr;
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key > key)
//				{
//					parent = cur;
//					cur = cur->_left;
//				}
//				else if (cur->_key < key)
//				{
//					parent = cur;
//					cur = cur->_right;
//				}
//				else
//				{
//					return false;
//				}
//			}
//			cur = new Node(key);
//			if (parent->_key < key)
//			{
//				parent->_right = cur;
//			}
//			else
//			{
//				parent->_left = cur;
//			}
//			return true;
//		}
//
//		//删除
//		bool Erase(const K& key)
//		{
//			Node* parent = nullptr;
//			Node* cur = _root;
//
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					parent = cur;
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					parent = cur;
//					cur = cur->_left;
//				}
//				else
//				{
//					//找到了删除的key
//					if (cur->_left == nullptr)//左为空
//					{
//						if (parent == nullptr)
//						{
//							_root = cur->_right;
//						}
//						else
//						{
//							if (parent->_left == cur)
//							{
//								parent->_left = cur->_right;
//							}
//							else
//							{
//								parent->_right = cur->_right;
//							}
//							delete cur;
//						}
//					}
//					else if (cur->_right == nullptr)//右为空
//					{
//						if (parent == nullptr)
//						{
//							_root = cur->_left;
//						}
//						else
//						{
//							if (parent->_left == cur)
//							{
//								parent->_left = cur->_left;
//							}
//							else
//							{
//								parent->_right = cur->_left;
//							}
//							delete cur;
//						}
//					}
//					else//两个节点都不为空
//					{
//						Node* minparent = cur;
//						Node* min = cur->_right;
//
//						while (min->_left)
//						{
//							minparent = min;
//							min = min->_left;
//						}
//
//						cur->_key = min->_key;
//
//						if (minparent->_left == min)
//						{
//							minparent->_left = min->_right;
//						}
//						else
//						{
//							minparent->_right = min->_right;
//						}
//						delete min;
//					}
//					return true;
//
//				}
//			}
//			return false;
//		}
//
//		//中序遍历
//		void _InOrder(Node* root)
//		{
//			if (root == nullptr)
//			{
//				return;
//			}
//			_InOrder(root->_left);
//			cout << root->_key << " ";
//			_InOrder(root->_right);
//		}
//		void InOrder()
//		{
//			_InOrder(_root);
//			cout << endl;
//		}
//		//查找
//		bool Find(const K& key)
//		{
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					cur = cur->_right;
//				}
//				else
//				{
//					return true;
//				}
//			}
//			return false;
//		}
//	private:
//		Node* _root;
//	};
//
//	void TestBSTree()
//	{
//		BSTree<int> t;
//		int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
//		for (auto e : a)
//		{
//			t.Insert(e);
//		}
//		t.InOrder();
//		t.Erase(7);
//		t.InOrder();
//
//		t.Erase(5);
//		t.InOrder();
//
//		t.Erase(0);
//		t.InOrder();
//
//		t.Erase(1);
//		t.InOrder();
//
//		for (auto e : a)
//		{
//			t.Erase(e);
//			t.InOrder();
//		}
//		t.InOrder();
//
//	}
//}








//key/value模型
namespace KV
{
	template<class K,class V>
	struct BSTreeNode
	{
		BSTreeNode<K,V>* _left;
		BSTreeNode<K,V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key,const V& value)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{

		}
	};

	template<class K,class V>
	struct BSTree
	{
		typedef BSTreeNode<K,V> Node;
	public:
		BSTree()
			:_root(nullptr)
		{

		}
		//Insert实现
		bool Insert(const K& key,const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key,value);
				return true;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					return false;
				}
			}
			cur = new Node(key,value);
			if (parent->_key < key)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			return true;
		}

		//删除
		bool Erase(const K& key)
		{
			Node* parent = nullptr;
			Node* cur = _root;

			while (cur)
			{
				if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					//找到了删除的key
					if (cur->_left == nullptr)//左为空
					{
						if (parent == nullptr)
						{
							_root = cur->_right;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_right;
							}
							else
							{
								parent->_right = cur->_right;
							}
							delete cur;
						}
					}
					else if (cur->_right == nullptr)//右为空
					{
						if (parent == nullptr)
						{
							_root = cur->_left;
						}
						else
						{
							if (parent->_left == cur)
							{
								parent->_left = cur->_left;
							}
							else
							{
								parent->_right = cur->_left;
							}
							delete cur;
						}
					}
					else//两个节点都不为空
					{
						Node* minparent = cur;
						Node* min = cur->_right;

						while (min->_left)
						{
							minparent = min;
							min = min->_left;
						}

						cur->_key = min->_key;

						if (minparent->_left == min)
						{
							minparent->_left = min->_right;
						}
						else
						{
							minparent->_right = min->_right;
						}
						delete min;
					}
					return true;

				}
			}
			return false;
		}

		//中序遍历
		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}
			_InOrder(root->_left);
			cout << root->_key << ":" << root->_value << endl;
			_InOrder(root->_right);
		}
		void InOrder()
		{
			_InOrder(_root);
			cout << endl;
		}
		//查找
		Node* Find(const K& key)
		{
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key)
				{
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					cur = cur->_left;
				}
				else
				{
					return cur;
				}
			}

			return nullptr;
		}
	private:
		Node* _root;
	};

	void TestBSTree1()
	{
		//字典KV模型
		BSTree<string,string> dict;
		dict.Insert("sort", "排序");
		dict.Insert("left", "向左");
		dict.Insert("right", "向右");
		dict.Insert("map", "地图、映射");

		string str;
		while (cin >> str)
		{
			BSTreeNode<string, string>* ret = dict.Find(str);
			if (ret)
			{
				cout << "对应中文解释：" << ret->_value << endl;
			}
			else
			{
				cout << "无此单词" << endl;
			}
		}
	}
	


	void TestBSTree2()
	{
		// 统计水果出现次数
		string arr[] = { "苹果", "西瓜", "草莓", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
		BSTree<string, int> countTree;
		for (auto& str : arr)
		{
			//BSTreeNode<string, int>* ret = countTree.Find(str);
			auto ret = countTree.Find(str);
			if (ret != nullptr)
			{
				ret->_value++;
			}
			else
			{
				countTree.Insert(str, 1);
			}
		}

		countTree.InOrder();
	}
}