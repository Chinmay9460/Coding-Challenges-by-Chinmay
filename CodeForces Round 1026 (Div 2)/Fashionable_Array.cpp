#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    // Collect min/max of each parity
    int e_min = INT_MAX, e_max = INT_MIN;
    int o_min = INT_MAX, o_max = INT_MIN;
    for (int x : a) {
        if (x % 2 == 0) {
            e_min = min(e_min, x);
            e_max = max(e_max, x);
        } else {
            o_min = min(o_min, x);
            o_max = max(o_max, x);
        }
    }

    // If already only one parity ⇒ sum is even ⇒ 0 ops
    if (e_max == INT_MIN || o_max == INT_MIN) {
        cout << 0 << "\n";
        return;
    }

    // Count how many we can keep if targeting evens as ends
    int keep_if_even_ends = 0;
    for (int x : a)
        if (e_min <= x && x <= e_max)
            keep_if_even_ends++;

    // Count how many we can keep if targeting odds as ends
    int keep_if_odd_ends = 0;
    for (int x : a)
        if (o_min <= x && x <= o_max)
            keep_if_odd_ends++;

    // Deletions = n - (kept)
    int del_even = n - keep_if_even_ends;
    int del_odd  = n - keep_if_odd_ends;
    cout << min(del_even, del_odd) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
