/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
#include<iostream>
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        if(s.length()==0)
            return 0;
        int start = 0;
        int end = 1;
        int count = 0;
        int i;
        while (end < s.length())
        {
            
            for (i = start; i < end; i++)
            {
                if (s[i] == s[end])
                {
                    int len = end - start;
                    count = std::max(len, count);
                    start = i + 1;
                    break;
                }
            }
            if (i == end)
            {
                end++;
            }
        }
        count = std::max(end-start, count);
        return count;
    }
};
// @lc code=end

