#include "pch.h"

int main()
{
	std::vector<int*> test1;
	size_t memorySize = 10000000;

	/*MAlloc<int> t1(memorySize);
	for (int i = 0; i < memorySize; ++i)
	{
		test1.push_back(t1.Add(i));
	}
	std::cout << test1[9] << "\t"<< *test1[9] << std::endl;
	t1.Delete(test1[9]);
	std::cout << t1.Add(500) << std::endl;
	std::cout << test1[9] << "\t" << *test1[9] << std::endl;*/
	
	clock_t t0 = clock();
	for (size_t i = 0; i < memorySize; ++i)
	{
		new int(i);
	}
	t0 = clock() - t0;
	std::cout << "Default memory allocator: \t" << t0 << std::endl;
	clock_t t = clock();
	
	MAlloc<int> t1(memorySize);/*
	MAlloc<int> t2;
	MAlloc<int> t3;
	MAlloc<int> t4;
	MAlloc<int> t5;
	MAlloc<int> t6;
	MAlloc<int> t7;
	MAlloc<int> t8;
	MAlloc<int> t9;
	MAlloc<int> t10;*/


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
	for (size_t i = 0; i < memorySize; ++i)
	{
		t1.Add(i);
	}
	t = clock() - t;

	std::cout << "Custom memory allocator: \t" << t << std::endl;



	return 0;
}