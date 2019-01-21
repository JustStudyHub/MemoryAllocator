#pragma once
template<typename T>
class MAlloc
{
public:
	MAlloc(size_t numOfObj);
	~MAlloc();
	T* Add(T obj);
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
	size_t m_numOfObj;
	const size_t m_infDataSize = sizeof(DataInf);
	const size_t m_objSize = sizeof(T);
	size_t m_objDataShift;
	size_t m_objDataSize;
	char* m_buffer;
	DataInf* m_startInfBufer;
	DataInf* m_lastFreePos;
};

template<typename T>
MAlloc<T>::MAlloc(size_t numOfObj)
{
	m_numOfObj = numOfObj;
	m_objDataShift = m_numOfObj * m_infDataSize;
	m_objDataSize = m_numOfObj * m_objSize;
	m_buffer = new char[m_objDataShift + m_objDataSize];

	m_startInfBufer = new(m_buffer) DataInf(true, m_objDataShift, nullptr);
	m_lastFreePos = m_startInfBufer;
	DataInf* tempPtr = nullptr;
	for (size_t i = 1; i < m_numOfObj; i++)
	{
		tempPtr = new(m_buffer + m_infDataSize * i) DataInf(true, m_objDataShift + m_objSize * i, m_lastFreePos);
		m_lastFreePos = tempPtr;
	}
}

template<typename T>
MAlloc<T>::~MAlloc()
{
	DataInf* tempPtr = m_startInfBufer;
	for (size_t i = 1; i < m_numOfObj; i++)
	{
		tempPtr += i;
		tempPtr->~DataInf();
	}
}

template<typename T>
T* MAlloc<T>::Add(T obj)
{
	T* tempObjPtr = nullptr;
	if (m_lastFreePos != nullptr)
	{
		tempObjPtr = new(m_buffer + m_lastFreePos->m_dStart) T(obj);
		m_lastFreePos->m_isMemoryFree = false;
		m_lastFreePos = m_lastFreePos->m_prevfreePos;
	}
	return tempObjPtr;
}
template<typename T>
T* MAlloc<T>::Delete(T* obj)
{
	size_t tempAdr = reinterpret_cast<size_t>(obj);
	size_t tempBufAdr = reinterpret_cast<size_t>(m_buffer);
	DataInf* tempInfPtr = m_lastFreePos;
	m_lastFreePos = reinterpret_cast<DataInf*> ((tempAdr - m_objDataShift - tempBufAdr)/m_objSize * m_infDataSize + tempBufAdr);
	obj->~T();
	m_lastFreePos->m_isMemoryFree = true;
	m_lastFreePos->m_prevfreePos = tempInfPtr;
	return nullptr;
}

