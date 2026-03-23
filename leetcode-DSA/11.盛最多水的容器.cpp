/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start

#include<vector>
#include<iostream>
#include<algorithm>
class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int left = 0;
        int right = height.size()-1;
        int res=0;
        int area;
        while (left<right)
        {
            /* code */
            area = (right-left)*std::min(height[left],height[right]);
            if(height[left]<height[right]){
                left+=1;
            }
            else{
                right-=1;
            }
            res = std::max(res,area);
        }
        return res;
    }
};
// @lc code=end

