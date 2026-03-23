/*
 * @lc app=leetcode.cn id=167 lang=cpp
 *
 * [167] 两数之和 II - 输入有序数组
 */

// @lc code=start
#include<vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size()-1;
        while(left<right){
            if(numbers[left]+numbers[right]==target){
                break;
            }
            else if (numbers[left]+numbers[right]>target)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
        std::vector<int> ans = {left+1,right+1};
        return ans;
    }
};
// @lc code=end

