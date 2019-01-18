

#include "pch.h"
#include "time.h"
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
	static const size_t m_numOfObj = 1000;
	static const size_t m_infDataSize = sizeof(DataInf);
	static const size_t m_objSize = sizeof(T);
	static const size_t m_objDataShift = m_numOfObj * m_infDataSize;
	static const size_t m_objDataSize = m_numOfObj * m_objSize;
	//char m_buffer[m_objDataShift + m_objDataSize];
	char* m_buffer = new char[m_objDataShift + m_objDataSize];

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
	
	stack<string*> test1;
	stack<string*> test2;
	stack<string*> test3;
	/*string* p1 = t1.Add("fytu");
	string* p2 = t1.Add("q");
	string* p3 = t1.Add("qwerjklqwerjklqwerjklqwerjklqwerjklqwerjklqwerjkl");*/
	string temp = "";
	/*for (int i = 0; i < 1000000; ++i)
	{
		test3.push_back(new string("qwertyqwerty"));
	}*/
	MemoryAlloc<string> t1;
	MemoryAlloc<string> t2;
	MemoryAlloc<string> t3;
	MemoryAlloc<string> t4;
	MemoryAlloc<string> t5;
	MemoryAlloc<string> t6;
	MemoryAlloc<string> t7;
	MemoryAlloc<string> t8;
	MemoryAlloc<string> t9;
	MemoryAlloc<string> t10;
	clock_t t = clock();
	
	for (int i = 0; i < 1000; ++i)
	{
		test1.push(t1.Add("qwertyqwerty"));
		test1.push(t2.Add("qwertyqwerty"));
		test1.push(t3.Add("qwertyqwerty"));
		test1.push(t4.Add("qwertyqwerty"));
		test1.push(t5.Add("qwertyqwerty"));
		test1.push(t6.Add("qwertyqwerty"));
		test1.push(t7.Add("qwertyqwerty"));
		test1.push(t8.Add("qwertyqwerty"));
		test1.push(t9.Add("qwertyqwerty"));
		test1.push(t10.Add("qwertyqwerty"));
	}
	t = clock() - t;
	//t = float(t) / CLOCKS_PER_SEC * 1000;

	cout << t << "    ";

	clock_t t0 = clock();
	for (int i = 0; i < 10000; ++i)
	{
		test2.push(new string("qwertyqwerty"));
	}
	t0 = clock() - t0;
	//t2 = float(t2) / CLOCKS_PER_SEC * 1000;
	cout << t0;

	
	/*MemoryAlloc<int> t1;
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
	}*/
	
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