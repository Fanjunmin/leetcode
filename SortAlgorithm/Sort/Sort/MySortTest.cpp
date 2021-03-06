// Sort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "MySort.h"
using namespace std;
vector<int> g_vec(10);
vector<int> g_right(10); 
class SortTest : public testing::Test {
public:
	virtual void SetUp() { 
		g_vec = {2,3,8,1,9,0,4,6,7,5};
    g_right = {0,1,2,3,4,5,6,7,8,9};
	}
	virtual void TearDown() {}
};

TEST_F(SortTest, BubbleSortTest1) {
	BubbleSort(g_vec.begin(), g_vec.end());
  EXPECT_TRUE(g_vec == g_right);
  EXPECT_ANY_THROW(BubbleSort(g_vec.end(), g_vec.begin()));

} 

TEST_F(SortTest, BubbleSortTest2) {
  BubbleSort(g_vec.begin(), g_vec.end(), less<int>());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, BubbleSortTest3) {
  BubbleSortWithFlag(g_vec.begin(), g_vec.end());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, BubbleSortTest4) {
  BubbleSortWithFlag(g_vec.begin(), g_vec.end(), less<int>());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, SelectionSortTest1) {
  SelectionSort(g_vec.begin(), g_vec.end());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, SelectionSortTest2) {
  SelectionSort(g_vec.begin(), g_vec.end(), less<int>());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, InsertionSortTest1) {
  InsertionSort(g_vec.begin(), g_vec.end());
  for (auto x : g_vec) {
		cout << x << ' ';
  }
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, InsertionSortTest2) {
  InsertionSort(g_vec.begin(), g_vec.end(), less<int>());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, CountSortTest) {
  CountSort(g_vec.begin(), g_vec.end());
  EXPECT_TRUE(g_vec == g_right);
}
TEST_F(SortTest, RadixSortTest) {
  RadixSort(g_vec.begin(), g_vec.end());
  EXPECT_TRUE(g_vec == g_right);
}
int main(int argc, char** argv) { 
	testing::GTEST_FLAG(output) = "xml:Ouput.xml";
  testing::InitGoogleTest(&argc, argv);
  RUN_ALL_TESTS();
  return 0;
}

