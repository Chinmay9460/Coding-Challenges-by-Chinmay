#include <bits/stdc++.h>
using namespace std;


#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
        cin >> s;
        int bal = 0;
        bool has_cut = false;

        for (int i = 0, n = s.size(); i < n - 1; i++) {
            if (s[i] == '(')  bal++;
            else               bal--;
            if (bal == 0) {
                has_cut = true;
                break;
            }
        }

        cout << (has_cut ? "YES\n" : "NO\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
