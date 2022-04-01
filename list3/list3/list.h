#pragma once

namespace wsh
{
	template<class T>
	struct ListNode
	{
		ListNode<T>* _next;
		ListNode<T>* _prev;
		T _data;

		ListNode(const T& data = T())
			:_next(nullptr)
			, _prev(nullptr)
			, _data(data)
		{

		}
	};






	//迭代器
	template<class T,class Ref,class Ptr>    //增加一个参数，返回值是一个模板参数
	struct __list_iterator
	{
		typedef ListNode<T> Node;
		typedef __list_iterator<T, Ref,Ptr> self;
		Node* _node;
		__list_iterator(Node* x)
			:_node(x)
		{

		}
		//++it
		self& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//it++
		self operator++(int)
		{
			self tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		//--it
		self& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		//it--
		self operator--(int)
		{
			self tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		//*
		Ref& operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}
		//!=
		bool operator!=(const self& it) const
		{
			return _node != it._node;
		}
		//==
		bool operator==(const self& it) const
		{
			return _node == it._node;
		}
	};

	//template<class T>
	//struct __const_list_iterator
	//{
	//	typedef ListNode<T> Node;
	//	Node* _node;
	//	__const_list_iterator(Node* x)
	//		:_node(x)
	//	{

	//	}
	//	//++it
	//	__const_list_iterator<T>& operator++()
	//	{
	//		_node = _node->_next;
	//		return *this;
	//	}
	//	//it++
	//	__const_list_iterator<T> operator++(int)
	//	{
	//		__const_list_iterator<T> tmp(*this);
	//		_node = _node->_next;
	//		return tmp;
	//	}
	//	//--it
	//	__const_list_iterator<T>& operator--()
	//	{
	//		_node = _node->_prev;
	//		return *this;
	//	}
	//	//it--
	//	__const_list_iterator<T> operator--(int)
	//	{
	//		__const_list_iterator<T> tmp(*this);
	//		_node = _node->_prev;
	//		return tmp;
	//	}
	//	//*
	//	const T& operator*() const
	//	{
	//		return _node->_data;
	//	}
	//	//!=
	//	bool operator!=(const __const_list_iterator<T>& it) const
	//	{
	//		return _node != it._node;
	//	}
	//	//==
	//	bool operator==(const __const_list_iterator<T>& it) const
	//	{
	//		return _node == it._node;
	//	}
	//};




	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef __list_iterator<T,T&,T*> iterator;
		typedef __list_iterator<T,const T&,const T*> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}
		list()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		////传统写法
		//list(const list<T>& It)
		//{
		//	_head = new Node();
		//	_head->_next = _head;
		//	_head->_prev = _head;
		//	for (auto& e : It)
		//	{
		//		push_back(e);
		//	}

		//}
		////It1 = It3
		//list<T>& operator=(const list<T>& It)
		//{
		//	if (this != &It)
		//	{
		//		clear();
		//		for (auto& e : It)
		//		{
		//			push_back(e);
		//		}
		//	}
		//	return *this;
		//}



		//现代写法

		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}


		//It2(It1)
		list(const list<T>& It)
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;


			list<T> tmp(It.begin(), It.end());
			swap(_head, tmp._head);
		}
		//It1 = It3
		list<T>& operator=(list<T> It)
		{
			swap(_head, It._head);
			return *this;
		}




		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				iterator del = it++;
				delete del._node;
			}
			_head->_next = _head;
			_head->_prev = _head;
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		void push_back(const T& x)
		{
		/*	Node* tail = _head->_prev;
			Node* newnode = new Node(x);
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;*/

			Insert(end(), x);
		}
		iterator Insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node*prev = cur->_prev;
			Node* newnode = new Node(x);

			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;
			return iterator(newnode);
		}
		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			delete pos._node;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}
		void pop_back()
		{
			erase(--end());
		}
		void pop_front()
		{
			erase(begin());
		}
	private:
		Node* _head;
	};
	//第一种方法实现const版本，这样太冗余
	void print_list(const list<int>& It)
	{
		list<int>::const_iterator it = It.begin();   //现在遍历不了了
		while (it != It.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}



	void test_list1()
	{
		list<int> It;
		It.push_back(1);
		It.push_back(2);
		It.push_back(3);
		It.push_back(4);
		It.push_back(5);
		It.push_back(6);

		list<int>::iterator it = It.begin();
		while (it != It.end())
		{
			*it *= 2;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}


	//迭代器像指针一样
	//使用场景
	struct Date
	{
		int _year;
		int _month;
		int _day;

		Date(int year =1, int month =1, int day =1)
			:_year(year)
			, _month(month)
			, _day(day)
		{}
	};
	void test_list2()
	{
		list<Date> It;
		It.push_back(Date(2022, 3, 12));
		It.push_back(Date(2022, 3, 13));
		It.push_back(Date(2022, 3, 14));

		list<Date>::iterator it = It.begin();
		while (it != It.end())
		{
			//cout << (*it)._year << "/" << (*it)._month << "/" << (*it)._day;
			cout << it->_year << "/" << it->_month << "/" << it->_day;//实现operator运算符重载
			++it;
			printf("\n");
		}
		cout << endl;
		//现在编译不通过
	}
	//拷贝、赋值
	void test_list3()
	{
		list<int> It1;
		It1.push_back(1);
		It1.push_back(2);
		It1.push_back(3);
		It1.push_back(4);

		list<int> It2(It1);
		for (auto& e : It2)
		{
			cout << e << " ";
		}
		cout << endl;

		list<int> It3;
		It3.push_back(10);
		It3.push_back(10);
		It3.push_back(10);
		It3.push_back(10);

		It1 = It3;
		for (auto& e : It1)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}