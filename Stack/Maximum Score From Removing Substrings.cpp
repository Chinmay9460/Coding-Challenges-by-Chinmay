class Solution {
public:
    static int maximumGain(const string &s, uint16_t x, uint16_t y) noexcept __attribute__((hot)) {
        const uint n = s.length();
        const uint16_t z = min(x, y);
        uint ca = 0, cb = 0, r = 0;
        const uint rev = x < y, step = rev * 2 - 1;
        if (rev) swap(x, y);
        for (uint i = n - 1 & -rev; (rev ? i + 1 : i < n); i -= step) {
            switch (s[i]) {
                case 'a':
                    if (x < y && cb > 0)
                        cb--, r += y;
                    else
                        ca++;
                    break;
                case 'b':
                    if (x > y && ca > 0)
                        ca--, r += x;
                    else
                        cb++;
                    break;
                default:
                    r += min(ca, cb) * z;
                    ca = cb = 0;
            }
        }
        return r + min(ca, cb) * z;
    }
};

const auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
