#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cassert>

class Solution {
public:

	//±©Á¦·¨ O(raw*col*(raw+col))
	static int findLonelyPixel(std::vector<std::vector<char>>& picture) {
		int raws = picture.size();
		int cols = picture[0].size();
		int counts = 0;
		for (size_t i = 0; i < raws; i++)//raw
		{
			for (size_t j = 0; j < cols; j++) {//col

				if (picture[i][j] == 'B') {
					int isBlackRaw = 0;
					int isBlackCol = 0;
					for (size_t k = 0; k < raws; k++)
					{
						if (picture[i][k] == 'B') {
							isBlackRaw++;
						}
					}

					for (size_t k = 0; k < cols; k++)
					{
						if (picture[k][j] == 'B') {
							isBlackCol++;
						}
					}

					if (isBlackCol == 1 && isBlackRaw == 1) {
						counts++;
					}
				}
			}
		}

		return counts;
	}

	static int findLonelyPixel2(std::vector<std::vector<char>>& picture) {
		int counts = 0;
		int raws = picture.size();
		int cols = picture[0].size();
		int max = raws > cols?raws:cols;
		std::vector<char> rawValue(max, 0);
		std::vector<char> colValue(max, 0);

		for (size_t i = 0; i < raws; i++)//raw
		{
			for (size_t j = 0; j < cols; j++) {//col
				if (picture[i][j] == 'B') {
					rawValue[i]++;
					colValue[j]++;
				}
			}
		}

		for (size_t i = 0; i < raws; i++)//raw
		{
			for (size_t j = 0; j < cols; j++) {//col

				if(picture[i][j] == 'B'){
					if (rawValue[i] == 1 && colValue[j] == 1) {
						counts++;
					}
				}
			}
		}
		
		return counts;
	}
};

int test(std::vector<std::vector<char>> expectedNums) {
	int ans = Solution::findLonelyPixel2(expectedNums);
	printf("%d\n", ans);
	system("pause");
	return 0;
}

void main() {
	test(std::vector<std::vector<char>>{ { 'W', 'W', 'B' }, { 'W', 'B', 'W' }, { 'B', 'W', 'W' } });
}