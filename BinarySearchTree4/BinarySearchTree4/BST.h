#pragma once

////keyģ��
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
//		//Insertʵ��
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
//		//ɾ��
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
//					//�ҵ���ɾ����key
//					if (cur->_left == nullptr)//��Ϊ��
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
//					else if (cur->_right == nullptr)//��Ϊ��
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
//					else//�����ڵ㶼��Ϊ��
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
//		//�������
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
//		//����
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








//key/valueģ��
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
		//Insertʵ��
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

		//ɾ��
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
					//�ҵ���ɾ����key
					if (cur->_left == nullptr)//��Ϊ��
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
					else if (cur->_right == nullptr)//��Ϊ��
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
					else//�����ڵ㶼��Ϊ��
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

		//�������
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
		//����
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
		//�ֵ�KVģ��
		BSTree<string,string> dict;
		dict.Insert("sort", "����");
		dict.Insert("left", "����");
		dict.Insert("right", "����");
		dict.Insert("map", "��ͼ��ӳ��");

		string str;
		while (cin >> str)
		{
			BSTreeNode<string, string>* ret = dict.Find(str);
			if (ret)
			{
				cout << "��Ӧ���Ľ��ͣ�" << ret->_value << endl;
			}
			else
			{
				cout << "�޴˵���" << endl;
			}
		}
	}
	


	void TestBSTree2()
	{
		// ͳ��ˮ�����ִ���
		string arr[] = { "ƻ��", "����", "��ݮ", "ƻ��", "����", "ƻ��", "ƻ��", "����", "ƻ��", "�㽶", "ƻ��", "�㽶" };
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