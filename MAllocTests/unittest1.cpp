#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\MemoryAllocator\MAlloc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MAllocTests
{		
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
		}
		void* operator new(size_t size)
		{
			return m_conteiner->Add();
		}

		void operator delete(void* p)
		{
			m_conteiner->Delete(reinterpret_cast<TestClass2*>(p));
		}
		int a;
		int b;
		int c;
		int a1;
		int b1;
		int c1;
		char d;
	private:
		static MAlloc<TestClass2>* m_conteiner;

	};
	MAlloc<TestClass2>* TestClass2::m_conteiner = new MAlloc<TestClass2>(200);
	TEST_CLASS(MAllocTest)
	{
	public:
		
		TEST_METHOD(TestAdd)
		{
			std::vector<int*> test1;
			size_t memorySize = 100;
			try
			{
				MAlloc<int> t1(memorySize);
				for (int i = 0; i < memorySize; ++i)
				{
					test1.push_back(t1.Add(i));
				}
				Assert::AreEqual(*test1[0], 0);
				Assert::AreEqual(*test1[9], 9);
				Assert::AreEqual(*test1[50], 50);
				Assert::AreEqual(*test1[99], 99);
				Assert::IsNull(t1.Add(31));
			}
			catch (...)
			{
				Assert::Fail();
			}						
		}

		TEST_METHOD(TestAddString)
		{
			std::vector<std::string*> test1;
			std::string temp = "qwerty";
			size_t memorySize = 100;
			try
			{
				MAlloc<std::string> t1(memorySize);
				for (int i = 0; i < memorySize; ++i)
				{
					test1.push_back(t1.Add(temp));
				}
				Assert::AreEqual(*test1[0], temp);
				Assert::AreEqual(*test1[9], temp);
				Assert::AreEqual(*test1[50], temp);
				Assert::AreEqual(*test1[99], temp);
				Assert::IsNull(t1.Add(temp));
			}
			catch (...)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(TestDeleteInFullBuffer)
		{
			std::vector<int*> test1;
			size_t memorySize = 100;
			try
			{
				MAlloc<int> t1(memorySize);
				for (int i = 0; i < memorySize; ++i)
				{
					test1.push_back(t1.Add(i));
				}
				t1.Delete(test1[0]);
				t1.Add(100);
				Assert::AreEqual(*test1[0], 100);
				t1.Delete(test1[9]);
				t1.Add(200);
				Assert::AreEqual(*test1[9], 200);
				t1.Delete(test1[50]);
				t1.Delete(test1[99]);
				t1.Add(300);
				t1.Add(400);
				Assert::AreEqual(*test1[50], 400);
				Assert::AreEqual(*test1[99], 300);
				Assert::IsNull(t1.Add(31));
			}
			catch (...)
			{
				Assert::Fail();
			}
		}

		TEST_METHOD(TestDelete)
		{
			std::vector<int*> test1;
			size_t memorySize = 200;
			try
			{
				MAlloc<int> t1(memorySize);
				for (int i = 0; i < memorySize - 100; ++i)
				{
					test1.push_back(t1.Add(i));
				}
				t1.Delete(test1[0]);
				t1.Add(100);
				Assert::AreEqual(*test1[0], 100);
				t1.Delete(test1[9]);
				t1.Add(200);
				Assert::AreEqual(*test1[9], 200);
				t1.Delete(test1[50]);
				t1.Delete(test1[99]);
				t1.Add(300);
				t1.Add(400);
				Assert::AreEqual(*test1[50], 400);
				Assert::AreEqual(*test1[99], 300);
				Assert::AreEqual(*t1.Add(31), 31);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}
	};

	TEST_CLASS(MAllocTestWithNew)
	{
	public:

		TEST_METHOD(TestAdd)
		{
			std::vector<TestClass2*> test1;
			size_t memorySize = 200;
			try
			{
				for (int i = 0; i < memorySize; ++i)
				{
					test1.push_back(new TestClass2(i));
				}
				Assert::AreEqual(test1[0]->a, 0);
				Assert::AreEqual(test1[9]->a, 9);
				Assert::AreEqual(test1[50]->a, 50);
				Assert::AreEqual(test1[99]->a, 99);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}		
		TEST_METHOD(TestDelete)
		{
			std::vector<TestClass2*> test1;
			size_t memorySize = 200;
			try
			{
				for (int i = 0; i < memorySize - 100; ++i)
				{
					test1.push_back(new TestClass2(i));
				}
				delete test1[0];
				test1[0] = new TestClass2(100);
				Assert::AreEqual(test1[0]->a, 100);
				delete test1[20];
				new TestClass2(200);
				Assert::AreEqual(test1[20]->a, 200);
				delete test1[99];
				new TestClass2(300);
				Assert::AreEqual(test1[99]->a, 300);
				delete test1[60];
				delete test1[70];
				new TestClass2(400);
				new TestClass2(500);
				Assert::AreEqual(test1[60]->a, 500);
				Assert::AreEqual(test1[70]->a, 400);
				TestClass2* temp = new TestClass2(600);
				Assert::AreEqual(temp->a, 600);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}
		TEST_METHOD(DeleteInFullBuffer)
		{
			std::vector<TestClass2*> test1;
			size_t memorySize = 200;
			try
			{
				for (int i = 0; i < memorySize; ++i)
				{
					test1.push_back(new TestClass2(i));
				}
				delete test1[0];
				new TestClass2(100);
				Assert::AreEqual(test1[0]->a, 100);
				delete test1[20];
				new TestClass2(200);
				Assert::AreEqual(test1[20]->a, 200);
				delete test1[199];
				new TestClass2(300);
				Assert::AreEqual(test1[199]->a, 300);
				delete test1[60];
				delete test1[70];
				new TestClass2(400);
				new TestClass2(500);
				Assert::AreEqual(test1[60]->a, 500);
				Assert::AreEqual(test1[70]->a, 400);
			}
			catch (...)
			{
				Assert::Fail();
			}
		}
	};
}