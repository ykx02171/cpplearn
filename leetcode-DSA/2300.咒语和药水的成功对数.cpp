/*
 * @lc app=leetcode.cn id=2300 lang=cpp
 *
 * [2300] 咒语和药水的成功对数
 */

// @lc code=start
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
// 实际上只需要求mid的值就好，不用把所有的vector数组都求出来。

int CountNum(int spell, vector<int>&potions, long long success){
    
    int left=0;
    int right = potions.size()-1;
    while(left<=right){
        int mid = left+(right-left)/2;
        if((long long)spell * potions[mid] < success){
            left=mid+1;
        }
        else{
            right = mid-1;
        }
    }
    return potions.size()-left;
}
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        vector<int> res(spells.size());
        for(int i=0;i<spells.size();i++){
            res[i]=CountNum(spells[i],potions,success);
        }
        return res;
    }
};
// @lc code=end

