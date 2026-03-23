/*
 * @lc app=leetcode.cn id=2529 lang=cpp
 *
 * [2529] 正整数和负整数的最大计数
 */

// @lc code=start
#include<vector>
#include<iostream>
using namespace std;

//几个问题，第一左闭右必区间，left<=right
//然后nums[mid]<target
//还有left = mid+1     right = mid-1
//判断条件必须要记清

int CountNum(vector<int>&nums, int target){
    int left =0;
    int right = nums.size()-1;
    while(left<=right){     
        int mid = left+(right-left)/2;
        if (nums[mid]<target)
        {
            left = mid+1;
        }
        else{
            right=mid-1;
        }
    }
    if (target==0){
        return left;
    }
    else if(target==1){
        return nums.size()-left;
    }
    return 0;
}
class Solution {
public:
    int maximumCount(vector<int>& nums) {
        int res0 = CountNum(nums, 0);
        int res1 = CountNum(nums, 1);

        return max(res0,res1);

    }
};
// @lc code=end

