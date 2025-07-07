#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define pb push_back
#define f first
#define s second

const int MAX = 1000007;
const int MOD = 1000000007;


//Sergei99 's code best in c++....

#define INL __attribute__((always_inline))
#define HOT __attribute__((hot))
#define INL_ATTR noexcept INL HOT
#define OUTL_ATTR noexcept HOT
#define LAM_ATTR INL HOT noexcept

#pragma GCC diagnostic ignored "-Wvla-cxx-extension"
#pragma GCC diagnostic ignored "-Wshift-op-parentheses"
#pragma GCC diagnostic ignored "-Wunqualified-std-cast-call"


template <class It, class Fun, uint8_t RBITS>
HOT typename remove_reference<decltype(*declval<It>())>::type radix_stable_sort(const It beg, const It end, const uint8_t pos, const It out, const Fun getval) noexcept {
    constexpr uint RADIX = 1u << RBITS, RMASK = RADIX - 1u;
    uint freqs[RADIX + 1u] = {};
    for (auto curr = beg; curr < end; curr++)
        freqs[((getval(*curr) >> pos) & RMASK) + 1u]++;
    partial_sum(freqs + 1u, freqs + RADIX + 1u, freqs + 1u);
    auto maxi = *beg;
    auto maxv = getval(maxi);
    for (auto curr = beg; curr < end; curr++) {
        const auto i = *curr;
        const auto v = getval(i);
        out[freqs[((v >> pos) & RMASK)]++] = i;
        if (v > maxv) {
            maxi = i;
            maxv = v;
        }
    }
    return maxi;
}

template <class It, class Fun, uint8_t SBITS, uint8_t RBITS = SBITS>
HOT void adaptive_sort(const It beg, const It end, const Fun getval, const It temp) noexcept {
    using T = remove_reference<decltype(*declval<It>())>::type;
    using V = result_of<decltype(getval)(const T)>::type;
    constexpr uint8_t BITSIZE = sizeof(V) * 8u;
    const uint n = end - beg;
    if (n > 1u << (SBITS - 2u)) {
        const bool large = n > 1u << (RBITS - 2u);
        It bin = beg, ein = end, bout = temp, eout = temp + n;
        T maxi = *beg;
        V maxv = 1;
        const auto sortfn = large ? radix_stable_sort<It,Fun,RBITS> : radix_stable_sort<It,Fun,SBITS>;
        const uint8_t bits = large ? RBITS : SBITS;
        for (uint8_t pos = 0; pos < BITSIZE && maxv >> pos; pos += bits) {
            maxi = sortfn(bin, ein, pos, bout, getval);
            maxv = getval(maxi);
            swap(bin, bout);
            swap(ein, eout);
        }
        if (bout == beg)
            copy(bin, ein, beg);
    } else if (n > 2) {
        sort(beg, end, [getval](const T i, const T j) LAM_ATTR { return getval(i) < getval(j); });
    } else if (n == 2 && getval(beg[0]) > getval(beg[1])) {
        swap(beg[0], beg[1]);
    }
}

template <class It, class Fun, uint8_t SBITS, uint8_t RBITS = SBITS>
HOT INL void adaptive_sort(const It beg, const It end, const Fun getval) noexcept {
    using T = remove_reference<decltype(*declval<It>())>::type;
    const uint n = end - beg;
    T temp[n];
    adaptive_sort<It,Fun,SBITS,RBITS>(beg, end, getval, temp);
}

class Solution {
public:

    int findLHS1(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        unordered_map<int,int>freq;
        for(int i = 0;i<nums.size();i++) freq[nums[i]]++;int ans = 0;
        for(auto it : freq) if(freq.find(it.first + 1) != freq.end())ans = max(ans, it.second + freq[it.first + 1]);
        return ans;
    }


    static int findLHS2(vector<int> &nums) noexcept __attribute__((hot)) {
        const auto getkey = [](const int v) LAM_ATTR { return v + 1'000'000'000; };
        const uint n = nums.size();
        int *const data = nums.data();
        adaptive_sort<int*,decltype(getkey),8>(data, data + n, getkey);
        uint a = 0, b = 0, l = 0;
        int p = nums.front();
        for (uint i = 1; i < n; i++) {
            const int v = nums[i];
            if (v > p) {
                const uint g = -(i - a > l & a != b);
                l = (i - a & g) + (l & ~g);
                const uint e = -(v == p + 1);
                a = (b & e) + (i & ~e);
                b = i;
                p = v;
            }
        }
        const uint g = -(n - a > l & a != b);
        return (n - a & g) + (l & ~g);
    }
};

const auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
int main() {
    
    return 0;
}
