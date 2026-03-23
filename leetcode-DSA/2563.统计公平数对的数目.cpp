/*
 * @lc app=leetcode.cn id=2563 lang=cpp
 *
 * [2563] 统计公平数对的数目
 */

// @lc code=start
#include<vector>
#include<algorithm>
using namespace std;
//注意j的大小，或者说是right的大小，必须-1来确保left要小于j

long long CountNum(vector<int>&nums, int target,int j,bool upper_bound){
    long long left =0;
    long long right = j;
    if(upper_bound){
        target+=1;
    }
    while(left<=right){     
        long long mid = left+(right-left)/2;
        if (nums[mid]<target)
        {
            left = mid+1;
        }
        else{
            right=mid-1;
        }
    }
    return left;
}
class Solution {
public:
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        sort(nums.begin(),nums.end());
        long long ans = 0;
        for (int j=0;j<nums.size();j++){
            long long low = CountNum(nums,lower-nums[j],j-1,false);
            long long upp = CountNum(nums,upper-nums[j],j-1,true);
            ans += upp-low;
        }
        return ans;
    }
};
// @lc code=end

