#pragma GCC target("popcnt")
class Solution {
private:
    static uint cnt(const vector<int> &nums, const uint8_t i, const uint a, const uint u) noexcept __attribute__((hot)) {
        const uint b = a | nums[i];
        return a == u
            ? 1 << (i + 1)
            : i
                ? cnt(nums, i - 1u, a, u) + cnt(nums, i - 1u, b, u)
                : (b == u);
    }

public:
    static int countMaxOrSubsets1(const vector<int> &nums) noexcept __attribute__((always_inline, hot)) {
        return cnt(nums, nums.size() - 1u, 0, reduce(nums.cbegin(), nums.cend(), 0, bit_or<>()));
    }


  int countMaxOrSubsets2(vector<int>& nums) {
        int maxOR = 0, dp[1 << 17] = {1};

        for(int x : nums){
            for(int i = maxOR; i>=0 ; --i){
                dp[i | x] += dp[i];
            }
            maxOR |= x;
        }
        return dp[maxOR];
    }

    int countMaxOrSubsets(vector<int>& nums) { //O(n*maxValue) time, O(1) storage
        int maxOr=0; 
        for(int n:nums) maxOr|=n;
        int numberOfBadSubsets = 0; //bad subset means subset whose OR is less than maxOR
        for(int mask=maxOr;mask; mask=(mask-1)&maxOr){ //iterates over subsets of the set bits of the maxOr
            int cnt = 0; 
            for(int n:nums) if(!(n&mask)) cnt++; //counts elements of nums that have all 0s in the positions that are 1s in the current mask
            numberOfBadSubsets += (__builtin_popcount(mask)%2 ? 1 : -1)*((1<<cnt)-1); //inclusion exclusion
        }
        return (1<<nums.size())-1- numberOfBadSubsets;//total number of subsets minus number of bad subsets
    }
};

const auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
