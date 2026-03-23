/*
 * @lc app=leetcode.cn id=16 lang=cpp
 *
 * [16] 最接近的三数之和
 */

// @lc code=start
#include<vector>
#include<algorithm>
#include <cmath>
class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        std::sort(nums.begin(),nums.end());
        int ans;
        int dif_min = INT_MAX;
        int n = nums.size()-1;
        if(nums[0]+nums[1]+nums[2]>target)
        {
            ans = nums[0]+nums[1]+nums[2];
            return ans;
        }
        if(nums[n]+nums[n-1]+nums[n-2]<target)
        {
            ans = nums[n]+nums[n-1]+nums[n-2];
            return ans;
        }
        for(int i = 0; i<nums.size()-2;i++){
            int left = i+1;
            int right = nums.size()-1;

  
            while (left<right)
            {
                /* code */
                int sum = nums[i]+nums[left]+nums[right];
                int dif = std::abs(sum-target);
                if(dif<dif_min){
                    dif_min = dif;
                    ans = sum;
                }
                if(sum>target){
                    right--;
                }else if(sum<target){
                    left++;
                }else{
                    return target;
                }
                

            }

            
        }
        return ans;
    }
};
// @lc code=end

