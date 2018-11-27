#include <iostream>
#include <string.h> // For memcpy()
using namespace std;

template<typename T>
class Stack
{
public:
	Stack();
	~Stack();

	void push(const T &elem) throw(const char *);
	void pop();
	T top() const throw(const char *);
	bool empty() const;
	size_t size() const;
	size_t space() const;

private:
	T*  m_pElem;
	int m_nNext;
	int m_nSpace;	// Space allocated, >= size().

private:
	Stack(const Stack &rhs);
	Stack& operator=(const Stack<T> &rhs);
};

template<typename T>
Stack<T>::Stack()
:m_nNext(0)
,m_nSpace(10)
{
	m_pElem = new T[m_nSpace];
}

template<typename T>
Stack<T>::~Stack()
{
	delete []m_pElem;
}

template<typename T>
void Stack<T>::push(const T &elem) throw(const char *)
{
	// Allocate a large buffer and copy existing data into it.
	if (m_nNext == m_nSpace)
	{
		try
		{
			int nNewSize;
			if (m_nSpace <= 1000)
				nNewSize = m_nSpace * 2;
			else
				nNewSize = m_nSpace + 1000;
			cout << "*** Space is increased from " << m_nSpace << " to " << nNewSize << " ***" << endl;

			T *pNew = new T[nNewSize];
			memcpy(pNew, m_pElem, sizeof(T) * m_nSpace);
			delete[]m_pElem;

			m_pElem  = pNew;
			m_nSpace = nNewSize;
		}
		catch(std::bad_alloc)
		{
			throw "Not enough buffer!";
		}
	}

	m_pElem[m_nNext++] = elem;
}

template<typename T>
void Stack<T>::pop()
{
	if (m_nNext != 0)
		--m_nNext;
}

template<typename T>
T Stack<T>::top() const throw(const char *)
{
	if (m_nNext == 0)
		throw "empty stack!";

	return m_pElem[m_nNext-1];
}

template<typename T>
bool Stack<T>::empty() const
{
	return m_nNext == 0 ? true : false;
}

template<typename T>
size_t Stack<T>::size() const
{
	return m_nNext;
}

template<typename T>
size_t Stack<T>::space() const
{
	return m_nSpace;
}

#define TEMPLATE_STACK_CPP
#ifdef  TEMPLATE_STACK_CPP
int main(int argc, char *argv[])
{
	Stack<int> stk;
	
	for (int i = 0; i < 10; i++)
		stk.push(i);
	while (!stk.empty())
	{
		cout << stk.top() << " ";
		stk.pop();
	}
	cout << endl << "space(): " << stk.space() << ", size(): " << stk.size() << endl;

	for (int i = 0; i < 50; i++)
		stk.push(i);
	while (!stk.empty())
	{
		cout << stk.top() << " ";
		stk.pop();
	}
	cout << endl << "space(): " << stk.space() << ", size(): " << stk.size() << endl;

	try
	{
		cout << "stk.top(): " << stk.top() << endl;
	}
	catch (const char *pstr)
	{
		cout << "Exception: " << pstr << endl;
	}

	return 0;
}
#endif

