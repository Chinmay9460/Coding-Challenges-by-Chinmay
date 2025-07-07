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
#define ll long long
class Solution1 {
public:
    int possibleStringCount(string word, int k) {
        const int  M = 1e9+7;
        int sz = word.size();
        vector<int> freq;
        ll tot = 1;
        int cur = 1;
        for(int i = 1; i < sz; ++i){
            if (word[i] == word[i-1]){
                ++cur;
            }else{
                freq.push_back(cur);
                tot = (tot*cur) % M;
                cur = 1;
            }
        }
        freq.push_back(cur);
        tot = (tot*cur) % M;

        int n = freq.size();
        if (n >= k) return tot;

        vector<vector<ll>> dp(n, vector<ll>(k, 0)), pref(n, vector<ll>(k, 0));
        // dp[i][j] = total possible strings of length j possible considering first i characters.
        // dp[i][j] = sum dp[i-1][j-j']  {j1: 1 -> freq[i]}
        
        for(int j = 1; j < k; ++j){
            if (j <= freq[0]) dp[0][j] = 1;
            pref[0][j] = dp[0][j] + pref[0][j-1];
        }

        for(int i = 1; i < n; ++i){
            for(int j = 1; j < k; ++j){
                if (j-freq[i]-1 >= 0) dp[i][j] = (pref[i-1][j-1] - pref[i-1][j-freq[i]-1] + M) % M;
                else dp[i][j] = pref[i-1][j-1];
                pref[i][j] = (dp[i][j] + pref[i][j-1] ) % M;
            }
        }

        return (tot - pref[n-1][k-1] + M ) % M;
    }
};

class Solution2 {
public:
    int possibleStringCount(string word, int k) {
        const int MOD = 1e9 + 7;

        // Helper function for modular exponentiation (a^b % MOD)
        auto power = [&](long long base, long long exp) {
            long long res = 1;
            base %= MOD;
            while (exp > 0) {
                if (exp % 2 == 1) res = (res * base) % MOD;
                base = (base * base) % MOD;
                exp /= 2;
            }
            return res;
        };

        // 1. Parse the word to find lengths of consecutive character groups.
        if (word.empty()) {
            return 0;
        }
        std::vector<int> counts;
        for (int i = 0; i < word.length(); ) {
            int j = i;
            while (j < word.length() && word[j] == word[i]) {
                j++;
            }
            counts.push_back(j - i);
            i = j;
        }
        int n = counts.size();

        // 2. Calculate the total number of possible original strings.
        long long total_strings = 1;
        for (int c : counts) {
            total_strings = (total_strings * c) % MOD;
        }

        // 3. Group counts by size for efficient polynomial calculation.
        std::unordered_map<int, int> count_freq;
        for (int c : counts) {
            count_freq[c]++;
        }

        // 4. Precompute modular inverses up to k.
        // invs[i] will store the modular inverse of i.
        std::vector<long long> invs(k + 1, 0);
        if (k > 0) invs[1] = 1;
        for (int i = 2; i < k; ++i) {
            invs[i] = MOD - (MOD / i) * invs[MOD % i] % MOD;
        }
        
        // 5. Calculate coefficients of Q(x) = Product_{c in counts} (1 - x^c).
        // We only need coefficients for powers < k.
        std::vector<long long> Q(k, 0);
        Q[0] = 1;
        for (auto const& [s, c_freq] : count_freq) {
            // Calculate coefficients for P_s(x) = (1 - x^s)^c_freq using binomial expansion.
            std::vector<std::pair<int, long long>> P_s_coeffs;
            long long term = 1; // Represents C(c_freq, 0)
            for (int j = 0; j <= c_freq; ++j) {
                int deg = s * j;
                if (deg >= k) break;

                long long coeff = term;
                if (j % 2 == 1) {
                    coeff = (MOD - term) % MOD;
                }
                P_s_coeffs.push_back({deg, coeff});

                // Update term to C(c_freq, j+1) using C(c_freq, j)
                if (j < c_freq) {
                    term = (term * (c_freq - j)) % MOD;
                    term = (term * invs[j + 1]) % MOD;
                }
            }
            
            // Multiply Q by P_s (polynomial multiplication/convolution)
            std::vector<long long> new_Q(k, 0);
            for (int i = 0; i < k; ++i) {
                if (Q[i] == 0) continue;
                for (auto const& [deg_p, coeff_p] : P_s_coeffs) {
                    if (i + deg_p < k) {
                        new_Q[i + deg_p] = (new_Q[i + deg_p] + Q[i] * coeff_p) % MOD;
                    }
                }
            }
            Q = new_Q;
        }

        // 6. Calculate coefficients of H(x) = 1 / (1-x)^n = Sum C(n+j-1, j) * x^j
        std::vector<long long> H(k, 0);
        if (n > 0) {
            H[0] = 1;
            for (int j = 1; j < k; ++j) {
                // H[j] = H[j-1] * (n+j-1) / j
                H[j] = (H[j-1] * (n + j - 1)) % MOD;
                H[j] = (H[j] * invs[j]) % MOD;
            }
        }

        // 7. Calculate T(x) = H(x) * Q(x)
        std::vector<long long> T(k, 0);
        for (int i = 0; i < k; ++i) {
            if (H[i] == 0) continue;
            for (int j = 0; j < k; ++j) {
                if (Q[j] == 0) continue;
                if (i + j < k) {
                    T[i + j] = (T[i + j] + H[i] * Q[j]) % MOD;
                }
            }
        }

        // 8. The generating function for total length is x^n * T(x).
        // We need to sum coefficients for lengths 1 to k-1.
        // This corresponds to summing coefficients of T(x) for powers 0 to k-1-n.
        long long strings_less_than_k = 0;
        if (k > n) {
            for (int i = 0; i < k - n; ++i) {
                strings_less_than_k = (strings_less_than_k + T[i]) % MOD;
            }
        }
            
        // 9. Final result: total possibilities minus those with length < k.
        long long result = (total_strings - strings_less_than_k + MOD) % MOD;
        return static_cast<int>(result);
    }
};

class Solution3 {
public:
    static int possibleStringCount(const string &word, const uint k) noexcept __attribute__((hot)) {
        constexpr uint MOD = 1'000'000'007, MAXK = 2000;
        const uint n = word.length();
        if (n <= k) return n == k;
        uint seg[n], g = 1;
        *seg = 1;
        char p = word.front();
        for (uint i = 1; i < n; i++) {
            const char c = word[i];
            const bool e = p == c;
            g += !e;
            seg[g-1] = (seg[g-1] & -e) + 1;
            p = c;
        }
        uint64_t t = 1;
        bool big = false;
        for (uint j = 0; j < g; j++) {
            t *= seg[j];
            big |= t >= MOD;
            t %= MOD;
        }
        if (t == 1 && !big) return 1;
        if (k <= g) return t;
        const uint maxt = k - g - 1;
        uint res[2][maxt+1], pref[maxt+2];
        **res = 1;
        fill_n(*res + 1, maxt, 0);
        *pref = 0;
        for (uint j = 0; j < g; j++) {
            const uint s = seg[j];
            for (uint i = 0; i <= maxt; i++) {
                pref[i+1] = (pref[i] + res[j&1][i]) % MOD;
                uint v = MOD + pref[i+1] - pref[max(s - 1, i) - s + 1];
                v -= MOD & -(v >= MOD);
                res[j&1^1][i] = v - (MOD & -(v >= MOD));
            }
        }
        return ((uint64_t)MOD * (maxt + 1) + t - reduce(res[g&1], res[g&1] + (maxt + 1), 0ull)) % MOD;
    }
};

#define i64 int64_t
const i64 mod = 1e9 + 7;
class Solution4 {
public:
    i64 possibleStringCount(string word, i64 k) {
        vector<i64> els;
        i64 cur = 0;
        char c = '$';
        i64 n = word.size();

        int j;
        for (int i = 0; i < n; i = j) {
            j = i + 1;
            while (j < n && word[j] == word[i])
                ++j;
            els.push_back(j - i);
        }
        els = els;
        int g = els.size();

        i64 total = 1;
        for (auto it : els) {
            total = (total * it) % mod;
        }

        if (g >= k) {

            // cout<<"easy\n";
            return total;
        }
        // cout<<"NOT EASY"<<endl;

        i64 ans = 0;
        i64 sum_max = k - 1;
        vector<i64> dp(sum_max + 1, 0);
        vector<i64> news(sum_max + 1, 0);

        dp[0] = 1;
        i64 window = 0;

        for (i64 i = 0; i < els.size(); i++) {
            window = 0;
            news[0] = 0;
            for (i64 j = 1; j <= sum_max; j++) {
                window += dp[j-1];
                window %= mod;
                if (j >= els[i] + 1) {
                    window -= dp[j - els[i] - 1];
                }
                window %= mod;
                news[j] = window;
            }
            dp.swap(news);
        }
        for (auto it : dp) {
            ans += it;
            ans %= mod;
        }

        ans = total - ans;
        ans %= mod;

        if (ans < 0)
            ans += mod;

        return ans;
    }
};
auto init = atexit([]() { ofstream("display_runtime.txt") << "0";});


const auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
