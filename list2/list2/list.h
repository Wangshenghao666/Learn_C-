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
	template<class T>
	struct __list_iterator
	{
		typedef ListNode<T> Node;
		Node* _node;
		__list_iterator(Node* x)
			:_node(x)
		{

		}
		//++it
		__list_iterator<T>& operator++()
		{
			_node = _node->_next;
			return *this;
		}
		//it++
		__list_iterator<T> operator++(int)
		{
			__list_iterator<T> tmp(*this);
			_node = _node->_next;
			return tmp;
		}
		//--it
		__list_iterator<T>& operator--()
		{
			_node = _node->_prev;
			return *this;
		}
		//it--
		__list_iterator<T> operator--(int)
		{
			__list_iterator<T> tmp(*this);
			_node = _node->_prev;
			return tmp;
		}
		//*
		T& operator*()
		{
			return _node->_data;
		}
		//!=
		bool operator!=(const __list_iterator<T>& it) const
		{
			return _node != it._node;
		}
		//==
		bool operator==(const __list_iterator<T>& it) const
		{
			return _node == it._node;
		}
	};
	template<class T>
	class list
	{
		typedef ListNode<T> Node;
	public:
		typedef __list_iterator<T> iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}
		iterator end()
		{
			return iterator(_head);
		}
		list()
		{
			_head = new Node();
			_head->_next = _head;
			_head->_prev = _head;
		}
		void push_back(const T& x)
		{
			Node* tail = _head->_prev;
			Node* newnode =new Node(x);
			tail->_next = newnode;
			newnode->_prev = tail;
			newnode->_next = _head;
			_head->_prev = newnode;
		}
	private:
		Node* _head;
	};
	void test_list1()
	{
		list<int> It;
		It.push_back(1);
		It.push_back(2);
		It.push_back(3);
		It.push_back(4);

		list<int>::iterator it = It.begin();
		while (it != It.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}