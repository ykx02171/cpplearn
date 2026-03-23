/*
 * @lc app=leetcode.cn id=15 lang=cpp
 *
 * [15] 三数之和
 */

// @lc code=start
#include<vector>
#include<algorithm>
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::sort(nums.begin(),nums.end());
        std::vector<std::vector<int>> ans;
        for (int i =0;i<nums.size()-2;i++){
            int left = i+1;
            int right = nums.size()-1;
            if(i>0&&nums[i]==nums[i-1])
            {
                continue;
            }
            if(nums[i]+nums[i+1]+nums[i+2]>0){
                break;
            }
            if(nums[i]+nums[right]+nums[right-1]<0){
                continue;
            }
            while(left<right){
                if(nums[left]+nums[right]<-nums[i]){
                    left++;
                }
                else if (nums[left]+nums[right]>-nums[i])
                {
                    right--;
                }
                else{
                    ans.push_back({nums[i],nums[left],nums[right]});
                    left++;
                    while (left<right&& nums[left]==nums[left-1])
                    {
                        left++;
                    }
                    right--;
                    while (left<right&& nums[right]==nums[right+1])
                    {
                        right--;
                    }
                    
                }
            }
        }
        return ans;
    }
};
// @lc code=end

