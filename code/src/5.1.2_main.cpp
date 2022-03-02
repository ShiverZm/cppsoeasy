#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cassert>

class Solution {
public:
	//����1  ʱ�临�Ӷ�O(n)
	static std::vector<int> getModifiedArray(
		int length,
		std::vector<std::vector<int>> updates)
	{
		std::vector<int> arr(length, 0);
		for (size_t i = 0; i < updates.size(); i++)
		{
			int start = updates[i][0];
			int end = updates[i][1];
			int inc = updates[i][2];

			arr[start] += inc;
			if (end + 1 < length) {
				arr[end + 1] -= inc;
			}

		}

		//2.�����������
		for (size_t i = 1; i < length; i++) {
			arr[i] += arr[i-1];
		}

		return arr;
	}

	//����2  ʱ�临�Ӷ�O(n^2)
	static std::vector<int> getModifiedArray2(
		int length, 
		std::vector<std::vector<int>> updates) 
	{
		std::vector<int> arr(length, 0);
		for (size_t i = 0; i < updates.size(); i++)
		{
			int start = updates[i][0];
			int end = updates[i][1];
			int inc = updates[i][2];

			for (size_t i = start; i <= end; i++)
			{
				arr[i] += inc;
			}
		}

		return arr;
	}

	static void getModifiedArray1to1(
		std::vector<int> &arr,
		int length,
		std::vector<std::vector<int>> updates) 
	{
		for (size_t i = 0; i < updates.size(); i++)
		{
			int start = updates[i][0];
			int end = updates[i][1];
			int inc = updates[i][2];

			arr[start] += inc;
			if (end + 1 < length) {
				arr[end + 1] -= inc;
			}

		}

		//2.�����������
		for (size_t i = 1; i < length; i++) {
			arr[i] += arr[i - 1];
		}
	}

};

int test(int length, std::vector<std::vector<int>> expectedNums) {
	std::vector<int> ans(length, 0);
	
	printf("��ʼ״̬��\n[");
	for (size_t i = 0; i < length; i++)
	{
		printf("%d,", ans[i]);
	}
	printf("]\n");
	
	for (size_t i = 0; i < expectedNums.size(); i++)
	{
		std::vector<std::vector<int>> expectedOne;
		expectedOne.push_back(expectedNums[i]);
		Solution::getModifiedArray1to1(ans,length, expectedOne);

		printf("�����˲���[");
		for (size_t j = 0; j < expectedNums[i].size(); j++)
		{
			printf("%d,", expectedNums[i][j]);
		}
		printf("] ���״̬:\n");
		printf("[");
		for (size_t j = 0; j < length; j++)
		{
			printf("%d,", ans[j]);
		}
		printf("]\n");
	}
	
	
	std::vector<int> ret = Solution::getModifiedArray(length, expectedNums);
	printf("�����:\n[");
	for (size_t j = 0; j < length; j++)
	{
		printf("%d,", ret[j]);
	}
	printf("]\n");

	system("pause");
	return 0;
}

void main5_1_2() {
	test(5, std::vector<std::vector<int>>{ {1,3,2 }, { 2,4,3 }, { 0, 2, -2 }});
}