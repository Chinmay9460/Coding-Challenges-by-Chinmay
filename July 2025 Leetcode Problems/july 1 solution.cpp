#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vll vector<ll>
#define pb push_back
#define f first
#define s second

const int MAX = 1000007;
const int MOD = 1000000007;

#define INL __attribute__((always_inline))
#define HOT __attribute__((hot))
#define INL_ATTR noexcept INL HOT
#define OUTL_ATTR noexcept HOT

#pragma GCC diagnostic ignored "-Wvla-cxx-extension"
#pragma GCC diagnostic ignored "-Wshift-op-parentheses"
#pragma GCC diagnostic ignored "-Wunqualified-std-cast-call"


class Solution1 {
    // This solution is based on the counting principle.
    // It counts the number of distinct characters in the string
    // and calculates the possible string count based on that.
    // The time complexity is O(n) where n is the length of the string.
    // The space complexity is O(1) since we are using a constant amount of space.
public:
    int possibleStringCount(string word) noexcept __attribute__ ((hot)) {
        char p = '\0';
        uint n = word.size() + 1;
        for(auto c : word){
            n -= (c != p);
            p = c;
        }
        return n;
    }
};


/*Counting principle has both of addition & multiplication.
Look at what LC said -->
    Although Alice tried to focus on her typing, she is aware that she
    may still have done this at most once.

Event occurse in either case. So, the adding rule is using for counting:
    cnt=1+∑fi​=∣seg[i]∣​(fi​−1)=n+1−∣segments∣

2nd approach is to use subtraction; Python 1-liner is made.


*/

// This solution is based addition
class Solution2 {
public:
    static int possibleStringCount(string& word) {
        int f=1, cnt=1;
        char prev='X';
        for(char c: word){
            if (c!=prev) {
                cnt+=(f>1)?(f-1):0;// add f-1 to cnt if f>1
                f=1;// reset f = 1
            }
            else f++; // increase f by 1
            prev=c; //update prev=c in both cases
        }
        cnt+=(f>1)?(f-1):0; // don't forget the last adding
        return cnt;
    }
};



// This solution is based substraction
class Solution3 {
public:
    static int possibleStringCount(string& word) {
        int n=word.size(), cnt=n;
        for(int i=1; i<n; i++)
            cnt-=(word[i]!=word[i-1]);
        return cnt;
    }
};


const auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
