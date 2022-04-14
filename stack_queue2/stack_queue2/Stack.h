#pragma once


namespace wsh
{
	template<class T, class Container = deque<T>>

	class stack
	{
	public:
		bool empty() const
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& top() const
		{
			return _con.back();
		}
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_back();
		}
	private:
		Container _con;
	};
	void test_stack()
	{
		stack<int> s;
		s.push(1);
		s.push(2);
		s.push(3);
		s.push(4);

		while (!s.empty())
		{
			cout << s.top() << " ";
			s.pop();

		}
		cout << endl;
	}
}


namespace wsh
{
	template<class T, class Container = deque<T>>

	class queue
	{
	public:
		bool empty() const
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		const T& front() const
		{
			return _con.front();
		}
		void push(const T& x)
		{
			_con.push_back(x);
		}
		void pop()
		{
			_con.pop_front();
		}
	private:
		Container _con;
	};
	void test_queue()
	{
		queue<int> q;
		q.push(1);
		q.push(2);
		q.push(3);
		q.push(4);

		while (!q.empty())
		{
			cout << q.front() << " ";
			q.pop();

		}
		cout << endl;
	}
}