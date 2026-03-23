/*
 * @lc app=leetcode.cn id=611 lang=cpp
 *
 * [611] 有效三角形的个数
 */

// @lc code=start
#include<vector>
#include<algorithm>
class Solution {
public:
    int triangleNumber(std::vector<int>& nums) {
        std::sort(nums.begin(),nums.end());
        int n = nums.size();
        int ans=0;
        for(int i=n-1;i>1;i--){
            int left=0;
            int right = i-1;
            while (left<right)
            {
                /* code */
                int sum = nums[left]+nums[right];
                if(sum>nums[i]){
                    ans += (right - left);
                    right--;
                }else
                {
                    /* code */
                    left++;
                }
                
            }
            
        }
        return ans;
    }

};
// @lc code=end

