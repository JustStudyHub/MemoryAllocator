#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\MemoryAllocator\MAlloc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MAllocTests
{		
	TEST_CLASS(UnitTest1)
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
		TEST_METHOD(TestDelete)
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
	};
}