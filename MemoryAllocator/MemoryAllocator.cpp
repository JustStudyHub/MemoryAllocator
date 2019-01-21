#include "pch.h"

int main()
{
	std::vector<int> test1;
	std::vector<int*> test2;

	/*MAlloc<int> t1;
	for (int i = 0; i < 10000; ++i)
	{
		test1.push_back(t1.Add(i));
	}
	std::cout << test1[999] << "\t"<< test1[999] << std::endl;
	t1.Delete(&test1[999]);
	std::cout << t1.Add(500) << endl;
	std::cout << test1[999] << "\t" << test1[999] << std::endl;*/

	clock_t t0 = clock();
	for (int i = 0; i < 100000; ++i)
	{
		new int(i * 100);
	}
	t0 = clock() - t0;
	std::cout << "Defaul memory allocator: \t" << t0 << std::endl;
	clock_t t = clock();
	MAlloc<int> t1;/*
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
	for (int i = 0; i < 100000; ++i)
	{
		t1.Add(i);
	}
	t = clock() - t;

	std::cout << "Custom memory allocator: \t" << t << std::endl;



	return 0;
}