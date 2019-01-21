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
	T& Add(T obj);
	T* Delete(T* obj);
private:
	struct DataInf
	{
		DataInf(bool isMemoryFree, size_t dStart, DataInf* prevfreePos)
		{
			m_isMemoryFree = isMemoryFree;
			m_dStart = dStart;
			m_prevfreePos = prevfreePos;
		}

		size_t m_dStart;
		DataInf* m_prevfreePos;
		bool m_isMemoryFree;
	};
	const size_t m_numOfObj = 100000;
	const size_t m_infDataSize = sizeof(DataInf);
	const size_t m_objSize = sizeof(T);
	const size_t m_objDataShift = m_numOfObj * m_infDataSize;
	const size_t m_objDataSize = m_numOfObj * m_objSize;
	char* m_buffer = new char[m_objDataShift + m_objDataSize];

	//std::stack<DataInf*> freeMemoryStack;
	DataInf* m_startInfBufer;
	DataInf* m_lastFreePos;
};

template<typename T>
MemoryAlloc<T>::MemoryAlloc()
{
	m_startInfBufer = new(m_buffer) DataInf(true, m_objDataShift, nullptr);
	m_lastFreePos = m_startInfBufer;
	DataInf* tempPtr = nullptr;
	for (size_t i = 1; i < m_numOfObj; i++)
	{
		tempPtr = new(m_buffer + m_infDataSize * i) DataInf(true, m_objDataShift + m_objSize * i, m_lastFreePos);
		m_lastFreePos = tempPtr;
		//freeMemoryStack.push(tempPtr);
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
T& MemoryAlloc<T>::Add(T obj)
{
	T* tempObjPtr = nullptr;
	if (m_lastFreePos != nullptr)
	{
		tempObjPtr = new(m_buffer + m_lastFreePos->m_dStart) T(obj);
		m_lastFreePos->m_isMemoryFree = false;
		m_lastFreePos = m_lastFreePos->m_prevfreePos;
	}
	return *tempObjPtr;
}

template<typename T>
T* MemoryAlloc<T>::Delete(T* obj)
{
	size_t tempAdr = reinterpret_cast<size_t>(obj);
	DataInf* tempInfPtr = m_lastFreePos;
	m_lastFreePos = reinterpret_cast<DataInf*> (tempAdr - m_objDataShift);
	obj->~T();
	m_lastFreePos->m_isMemoryFree = true;
	m_lastFreePos->m_prevfreePos = tempInfPtr;
	return nullptr;
}
using namespace std;




int main()
{

	vector<int> test1;
	vector<int*> test2;

	/*MemoryAlloc<int> t1;
	for (int i = 0; i < 10000; ++i)
	{
		test1.push_back(t1.Add(i));
	}
	cout << test1[999] << "\t"<< test1[999] << endl;
	t1.Delete(&test1[999]);
	cout << t1.Add(500) << endl;
	cout << test1[999] << "\t" << test1[999] << endl;*/

	clock_t t0 = clock();
	for (int i = 0; i < 100000; ++i)
	{
		new int(i * 100);
	}
	t0 = clock() - t0;
	cout << t0 << " ";
	clock_t t = clock();
	MemoryAlloc<int> t1;/*
	MemoryAlloc<int> t2;
	MemoryAlloc<int> t3;
	MemoryAlloc<int> t4;
	MemoryAlloc<int> t5;
	MemoryAlloc<int> t6;
	MemoryAlloc<int> t7;
	MemoryAlloc<int> t8;
	MemoryAlloc<int> t9;
	MemoryAlloc<int> t10;*/


	/*for (int i = 0; i < 10000; ++i)
	{
		t1.Add(i * 100);
		t2.Add(i * 100);
		t3.Add(i * 100);
		t4.Add(i * 100);
		t5.Add(i * 100);
		t6.Add(i * 100);
		t7.Add(i * 100);
		t8.Add(i * 100);
		t9.Add(i * 100);
		t10.Add(i * 100);
	}*/
	for (int i = 0; i < 100000; ++i)
	{
		t1.Add(i);
	}
	t = clock() - t;

	cout << t << "    ";



	return 0;
}