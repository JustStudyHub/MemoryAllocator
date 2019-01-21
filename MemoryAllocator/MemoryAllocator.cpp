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
int main()
{
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

	std::cout << "Memory Size: \t" << memorySize << " of string" << std::endl;
	{
		// Default Alloc
		clock_t t0 = clock();
		for (size_t i = 0; i < memorySize; ++i)
		{
			new std::string("qwerty");
		}
		t0 = clock() - t0;
		std::cout << "Default memory allocator: \t" << t0 << std::endl;

		// Custom Alloc
		clock_t t = clock();
		MAlloc<std::string> t2(memorySize);
		for (size_t i = 0; i < memorySize; ++i)
		{
			t2.Add("qwerty");
		}
		t = clock() - t;
		std::cout << "Custom memory allocator: \t" << t << std::endl;
	}

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
		t2.Add(i);
	}
	t = clock() - t;
	std::cout << "Custom memory allocator: \t" << t << std::endl;
	return 0;
}