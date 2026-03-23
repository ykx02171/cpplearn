// @before-stub-for-debug-begin
#include <vector>
#include <string>
// #include "commoncppproblem42.h"

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=42 lang=cpp
 *
 * [42] 接雨水
 */

// @lc code=start
#include<vector>
#include<iostream>
#include<algorithm>

class Solution {
public:
    int trap(std::vector<int>& height) {
        int left = 0;
        int right = height.size()-1;
        int ans=0;
        int pre_max=0;
        int suf_max =0;
        while (left<right)
        {
            pre_max = std::max(pre_max,height[left]);
            suf_max = std::max(suf_max,height[right]);
            if(pre_max<suf_max){
                ans+=pre_max-height[left];
                left++;
            }
            else{
                ans+=suf_max-height[right];
                right--;
            }

        }
        return ans;
        
    }
};
// @lc code=end

