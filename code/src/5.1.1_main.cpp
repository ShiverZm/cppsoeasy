#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cassert>

class Solution {
public:

	//正解1
	static int removeDuplicates(std::vector<int> nums) {
		int slow = 0;
		int fast = 0;

		while (fast < nums.size()) {
			if (nums[fast] != nums[slow]) {
				nums[slow + 1] = nums[fast];
				slow++;
			}

			fast++;
		}

		return slow + 1;
	}

	//错解
	static int removeDuplicates1(std::vector<int>& nums) {
		int realSize = nums.size();
		for (int i = 0; i< nums.size(); i++) {
			for (int j = i + 1; j < nums.size(); j++) {
				if (nums[i] == nums[j]) {
						nums[j-1] = nums[j];
						realSize--;
				}
			}
		}
		return realSize;
	}

	//错解
	static int removeDuplicates2(std::vector<int> nums) {
		int numsSize = nums.size();
		for (int i = 1; i < numsSize; i++) {
			if (nums[i - 1] == nums[i]) {
				for (int j = i + 1; j < numsSize; j++) 
				{ 
					nums[j - 1] = nums[j]; 
				}

				i--; 
				numsSize--;
			}
		} 
		return numsSize;
	}
};

int test(std::vector<int> &nums, std::vector<int> &expectedNums) {
	
	int size = Solution::removeDuplicates(nums);

	//assert(expectedNums.size() == size);

	printf("realSize:%d\n", size);

	printf("[");
	for (size_t i = 0; i < size; i++)
	{
		//assert(expectedNums[i] == nums[i]);
		printf("%d,", nums[i]);
	}
	printf("]\n");

	system("pause");
	return 0;
}

void main5_1_1() {
	test(std::vector<int>{ 1,2,2 }, std::vector<int>{ 1,2 });
	test(std::vector<int>{ 1,1,1,2,2,2 },std::vector<int>{ 1,2 });
}