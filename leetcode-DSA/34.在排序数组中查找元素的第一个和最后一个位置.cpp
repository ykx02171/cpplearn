/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
#include<vector>
class Solution {
public:
    std::vector<int> searchRange(std::vector<int>& nums, int target) {
         
        int left = 0;
        int right = nums.size()-1;

        std::vector<int> ans;
        while (left<=right)
        {
            int mid = left+(right-left)/2;
            if(nums[mid]<target){
                left=mid+1;
            }
            else{
                right=mid-1;
            }
        }
        int tmp=left;
        left=0;
        right=nums.size()-1;
        while(left<=right){
            int mid = left+(right-left)/2;
            if(nums[mid]<target+1){
                 left=mid+1;
            }
            else{
                right=mid-1;
            }
        
            
        }
        if(tmp==nums.size()||nums[tmp]!=target){
            return{-1,-1};
        }
        ans.push_back(tmp);
        ans.push_back(left-1);
        return ans;

    }
};
// @lc code=end

