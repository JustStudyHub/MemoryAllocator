#include "pch.h"
class TestClass
{
public:
	TestClass(int t)
	{
		a = t;
		a1 = 2 * t;
		b = t + a;
		b1 = 3 * t;
		c = b + t;
		c1 = 4 * t;
		d = 't';
	}
	~TestClass()
	{

	}

private:
	int a;
	int b;
	int c;
	int a1;
	int b1;
	int c1;
	char d;
};


class TestClass2
{
public:
	TestClass2()
	{
		a = 5;
		a1 = 2 * 5;
		b = 5 + a;
		b1 = 3 * 5;
		c = b + 5;
		c1 = 4 * 5;
		d = '5';
		m_conteiner = new MAlloc<TestClass2>(10000);
	}
	TestClass2(int t)
	{
		a = t;
		a1 = 2 * t;
		b = t + a;
		b1 = 3 * t;
		c = b + t;
		c1 = 4 * t;
		d = 't';
		m_conteiner = new MAlloc<TestClass2>(10000);
	}
	~TestClass2()
	{

	}
	void* operator new(size_t size)
	{
		return m_conteiner->Add();
	}

	void operator delete(void* p)
	{
		m_conteiner->Delete(reinterpret_cast<TestClass2*>(p));
	}

private:
	static MAlloc<TestClass2>* m_conteiner;
	int a;
	int b;
	int c;
	int a1;
	int b1;
	int c1;
	char d;
};

int main()
{
	//TestClass2 *a  = new TestClass2(6);
	size_t memorySize = 1000000;
	std::cout << "Memory Size: \t" << memorySize << " of int" << std::endl;
	{
		// Default Alloc
		clock_t t0 = clock();
		for (size_t i = 0; i < memorySize; ++i)
		{
			new int(i);
		}
		t0 = clock() - t0;
		std::cout << "Default memory allocator: \t" << t0 << std::endl;
		
		// Custom Alloc
		clock_t t = clock();
		MAlloc<int> t1(memorySize);
		for (size_t i = 0; i < memorySize; ++i)
		{
			t1.Add(i);
		}
		t = clock() - t;
		std::cout << "Custom memory allocator: \t" << t << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Memory Size: \t" << memorySize << " of string" << std::endl;
	{
		std::string temp = "qwerty";
		// Default Alloc
		clock_t t0 = clock();
		for (size_t i = 0; i < memorySize; ++i)
		{
			new std::string(temp);
		}
		t0 = clock() - t0;
		std::cout << "Default memory allocator: \t" << t0 << std::endl;

		// Custom Alloc
		clock_t t = clock();
		MAlloc<std::string> t2(memorySize);
		for (size_t i = 0; i < memorySize; ++i)
		{
			t2.Add(temp);
		}
		t = clock() - t;
		std::cout << "Custom memory allocator: \t" << t << std::endl;
	}
	std::cout << std::endl;
	std::cout << "Memory Size: \t" << memorySize << " of TestClass" << std::endl;

	// Default Alloc
	clock_t t0 = clock();
	for (size_t i = 0; i < memorySize; ++i)
	{
		new TestClass(i);
	}
	t0 = clock() - t0;
	std::cout << "Default memory allocator: \t" << t0 << std::endl;

	// Custom Alloc
	clock_t t = clock();
	MAlloc<TestClass> t2(memorySize);
	for (size_t i = 0; i < memorySize; ++i)
	{
		t2.Add(TestClass(i));
	}
	t = clock() - t;
	std::cout << "Custom memory allocator: \t" << t << std::endl;
	return 0;
}