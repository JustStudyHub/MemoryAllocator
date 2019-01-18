
#include "pch.h"
#include <iostream>
#include <stack>
#include <vector>
#include <string>

template<typename T>
class MemoryAlloc
{
public:
	MemoryAlloc();
	~MemoryAlloc();
	T* Add(T obj);
	T* Delete(T* obj);
private:
	struct DataInf
	{
		DataInf(bool isMemoryFree, size_t dStart , size_t dSize )
		{
			m_isMemoryFree = isMemoryFree;
			m_dStart = dStart;
			m_dSize = dSize;
		}
		bool m_isMemoryFree;
		size_t m_dSize;		
		size_t m_dStart;
	};
	static const size_t m_numOfObj = 10000;
	static const size_t m_infDataSize = sizeof(DataInf);
	static const size_t m_objSize = sizeof(T);
	static const size_t m_objDataShift = m_numOfObj * m_infDataSize;
	static const size_t m_objDataSize = m_numOfObj * m_objSize;
	char m_buffer[m_objDataShift + m_objDataSize];

	std::stack<DataInf*> freeMemoryStack;
	DataInf* m_startInfBufer;
	DataInf* m_endInfBufer;
};

template<typename T>
MemoryAlloc<T>::MemoryAlloc()
{
	m_startInfBufer = new(m_buffer) DataInf(true, m_objDataShift, m_objDataSize);
	DataInf* tempPtr = nullptr;
	for (size_t i = 1; i < m_numOfObj; i++)
	{
		tempPtr = new(m_buffer + m_infDataSize * i) DataInf(true, m_objDataShift + m_objSize * i, m_objSize);
		freeMemoryStack.push(tempPtr);
	}
}

template<typename T>
MemoryAlloc<T>::~MemoryAlloc()
{
	DataInf* tempPtr = m_startInfBufer;
	for (size_t i = 1; i < m_numOfObj; i++)
	{
		tempPtr += i;
		tempPtr->~DataInf();
	}
}

template<typename T>
T* MemoryAlloc<T>::Add(T obj)
{
	T* tempObjPtr = nullptr;
	DataInf* tempInfPtr = nullptr;

	if (freeMemoryStack.size())
	{
		tempInfPtr = freeMemoryStack.top();
		tempObjPtr = reinterpret_cast<T*>(new(m_buffer + tempInfPtr->m_dStart) T(obj));
		tempInfPtr->m_isMemoryFree = false;
		tempInfPtr->m_dSize = sizeof(obj);
		freeMemoryStack.pop();
	}
	/*for (size_t i = 0; i < m_numOfObj; i++)
	{
		tempInfPtr = m_startInfBufer + i;
		if (tempInfPtr->m_isMemoryFree)
		{
			tempObjPtr = reinterpret_cast<T*>(new(m_buffer + tempInfPtr->m_dStart) T(obj));
			tempInfPtr->m_isMemoryFree = false;
			tempInfPtr->m_dSize = sizeof(obj);
			break;
		}			
	}*/
	return tempObjPtr;
}

template<typename T>
T* MemoryAlloc<T>::Delete(T* obj)
{
	size_t tempAdr = reinterpret_cast<size_t>(obj);
	DataInf* tempInfPtr = reinterpret_cast<DataInf*> (tempAdr - m_objDataShift);
	obj->~T();
	tempInfPtr->m_isMemoryFree = true;
	freeMemoryStack.push(tempInfPtr);
	return nullptr;
}
using namespace std;
int main()
{
	//MemoryAlloc<string> t1;
	/*string* p1 = t1.Add("fytu");
	string* p2 = t1.Add("q");
	string* p3 = t1.Add("qwerjklqwerjklqwerjklqwerjklqwerjklqwerjklqwerjkl");*/
	//cout << *t1.Add("fytu") << endl;
	//cout << *t1.Add("q") << endl;
	//cout << *t1.Add("qwerjklqwerjklqwerjklqwerjklqwerjklqwerjklqwerjkl") << endl;
	MemoryAlloc<int> t1;
	vector<int*> test;
	for (int i = 0; i < 10000; ++i)
	{
		test.push_back(t1.Add(i));
	}
	cout << *test[552] << endl;
	t1.Delete(test[552]);
	int* test2 = t1.Add(50000);
	cout << *test2 << endl;
	int* test3 = t1.Add(55555);
	if (test3 != nullptr)
	{
		cout << *test3 << endl;
	}
	else
	{
		cout << "nullptr" << endl;
	}
	
	//int* p1 = t1.Add(100);
	//int* p2 = t1.Add(200);
	//int* p3 = t1.Add(300);
	/*cout << *p1 << endl;
	cout << *p2 << endl;
	cout << *p3 << endl;
	t1.Delete(p1);
	p1 = t1.Add("svglsbv");
	cout << *p1 << endl;*/
	return 0;
}