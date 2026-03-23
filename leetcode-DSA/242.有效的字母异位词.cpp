// @before-stub-for-debug-begin
#include <vector>
#include <string>
#include "commoncppproblem242.h"

using namespace std;
// @before-stub-for-debug-end

/*
 * @lc app=leetcode.cn id=242 lang=cpp
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
#include <iostream>
using namespace std;
class Solution {
public:
    bool isAnagram(string s, string t) {
        int count[26];
        for (int i =0;i<s.size();i++){
            int a = s[i]-'a';
            count[a]++;
        }
        for(int i =0;i<t.size();i++){
            int a = t[i]-'a';
            count[a]--;
        }
        for(int i = 0; i<26;i++){
            if(count[i]!=0){
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

