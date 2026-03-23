/*
 * @lc app=leetcode.cn id=33 lang=cpp
 *
 * [33] 搜索旋转排序数组
 */

// @lc code=start
#include<vector>
class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        //先找最小值
        int start = 0;
        int end = nums.size()-1;
        while(start<end){
            int mid = start + (end-start)/2;
            if(nums[mid]>nums[end]){
                start=mid+1;
            }
            else{
                end=mid;
            }
        }
        int pivot = start;
        int left=0,right=nums.size()-1;

        if(target>=nums[pivot]&&target<=nums[right]){
            left=pivot;
        }
        else{
            right = pivot-1;
        }

        while(left<=right){
            int mid = left+(right-left)/2;
            if(nums[mid]==target){
                return mid;}
            else if(nums[mid]<target){
                left=mid+1;
            }
            else{
                right = mid-1;
            }
        
        }

        return -1;
    }
};
// @lc code=end

