/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
#include<vector>
#include<algorithm>
class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums) {

        int n = nums.size();
        int slow = 0;
        int fast = 0;
        int ans = INT_MAX;
        int sum = 0;
        while (fast<n)
        {
            /* code */
            sum+=nums[fast];
            while (sum>=target)
            {
                /* code */
                ans = std::min(ans,fast-slow+1);
                sum-=nums[slow++];
            }
            fast++;

        }
        return ans==INT_MAX?0:ans;       
    }
};
// @lc code=end

