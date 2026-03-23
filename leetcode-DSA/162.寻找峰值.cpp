/*
 * @lc app=leetcode.cn id=162 lang=cpp
 *
 * [162] 寻找峰值
 */

// @lc code=start
#include<vector>
class Solution {
public:
    int findPeakElement(std::vector<int>& nums) {
        int left = 0;
        int right = nums.size()-2;
        while(left<=right){
            int mid = left+(right-left)/2;
            if(nums[mid]>nums[mid+1]){
                right=mid-1;
            }
            else{
                left = mid+1;
            }
        }
        return left;
    }
};
// @lc code=end

