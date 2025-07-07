#include <bits/stdc++.h>
using namespace std;


#define INL __attribute__((always_inline))

#define ll long long
#define vll vector<ll>
#define pb push_back
#define f first
#define s second

const int MAX = 1000007;
const int MOD = 1000000007;

class Solution {
public:
    vector<int> lexicalOrder(int n) {
        vector<int> result;
        int count = 1;
        for(int i = 0;i<n;++i) {
            result.push_back(1);

            if(count * 10 <= n) count *= 10;
            count++;
            while(count > n)count /= 10;
        }
        return result;
    }

    static vector<int> lexicalOrder(const uint n) noexcept INL {
        vector<int> r;
        r.reserve(n);
        for (uint c = 1, i = 0; i < n; i++) {
            r.push_back(c);
            if (const uint c10 = c * 10u; c10 <= n)
                c = c10;
            else {
                if (c >= n) c /= 10u;
                c++;
                while (c % 10u == 0)
                    c /= 10u;
            }
        }
        return r;
    }
};

auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();

int main(){

}
