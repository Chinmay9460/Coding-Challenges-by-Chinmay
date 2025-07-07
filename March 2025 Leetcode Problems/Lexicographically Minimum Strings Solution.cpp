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


template <class K, class T, uint CAP, K NONE = K(-1)>
struct static_allocator {
    struct item_t {
        T data;
        K next;
    };
    item_t items[CAP];
    K used, freehead;

    static_allocator() INL_ATTR: used(0), freehead(NONE) {}
        
    K alloc() INL_ATTR {
         K i;
        if (freehead != NONE) {
            i = freehead;
            freehead = items[freehead].next;
        } else {
            i = used++;
            // assert(used <= CAP);
        }
        items[i].next = NONE;
        return i;
    }

    void free(const K i) INL_ATTR {
        items[i].next = freehead;
        freehead = i;
    }

    void clear() INL_ATTR {
        used = 0;
        freehead = NONE;
    }
};


template <class K, class T, K RANGE, uint CAP, K NONE = K(-1)>
class part_queue {
    private:
        typedef static_allocator<K, T, CAP, NONE> allocator_t;
        static allocator_t allocator;

        static void _push(K &i, const T v) INL_ATTR {
        const K j = allocator.alloc();
        allocator.items[j].data = v;
        allocator.items[j].next = i;
        i = j;
    }

    static T _pop(K &i) INL_ATTR {
        const K j = i;
        const T v = allocator.items[j].data;
        i = allocator.items[j].next;
        allocator.free(j);
        return v;
    }

    K queues[RANGE];
    uint count;

    public:
    class iterator {
    private:
        K i;
    public:
        iterator(const K i) INL_ATTR: i(i) {}

        iterator &operator++() INL_ATTR {
            i = allocator.items[i].next;
            return *this;
        }

        iterator &operator++(const int) INL_ATTR {
            i = allocator.items[i].next;
            return *this;
        }

        bool operator==(const iterator &other) INL_ATTR {
            return i == other.i;
        }

        bool operator!=(const iterator &other) INL_ATTR {
            return i != other.i;
        }

        T operator*() const INL_ATTR {
            return allocator.items[i].data;
        }

        const T *operator->() const INL_ATTR {
            return &allocator.items[i].data;
        }
    };

    private:
    static iterator endit;

public:
    part_queue() INL_ATTR: count(0) {
        fill(queues, queues + RANGE, NONE);
    }

    void push(const K k, const T v) INL_ATTR {
        // assert(k < RANGE);
        _push(queues[k], v);
        count++;
    }

    T pop(const K k) INL_ATTR {
        count--;
        const T v = _pop(queues[k]);
        return v;
    }

    iterator peek(const K k) const INL_ATTR {
        return iterator(queues[k]);
    }

    iterator end() const INL_ATTR {
        return endit;
    }

    uint size() const INL_ATTR {
        return count;
    }

    bool empty() const INL_ATTR {
        return !count;
    }

    bool empty(const K k) const INL_ATTR {
        return queues[k] == NONE;
    }

    void clear(const K startk, const K endk) INL_ATTR {
        fill(queues + startk, queues + endk, NONE);
        allocator.clear();
        count = 0;
    }
};


template <class K, class T, K RANGE, uint CAP, K NONE>
static_allocator<K, T, CAP, NONE> part_queue<K, T, RANGE, CAP, NONE>::allocator;


template <class K, class T, K RANGE, uint CAP, K NONE>
part_queue<K, T, RANGE, CAP, NONE>::iterator part_queue<K, T, RANGE, CAP, NONE>::endit(NONE);


class Solution {
    private:
    static constexpr uint MAXN = 100'000;

    typedef part_queue<uint, uint, 26, MAXN> pq_t;

    static pq_t pos;

public:

    static string clearStars(string &s) OUTL_ATTR {
        const uint n = s.length();
        uint k = -1u;
        for (uint i = 0, u = 0; i < n; i++) {
            if (const char c = s[i]; c == '*') {
                const uint8_t e = __builtin_ctz(u);
                const uint p = pos.pop(e);
                s[p] = '$';
                u ^= pos.empty(e) << e;
                k = min(p, k);
            } else {
                const uint8_t d = c - 'a';
                pos.push(d, i);
                u |= 1u << d;
            }
        }
        if (k + 1) {
            for (uint i = k + 1; i < n; i++) {
                const char c = s[i];
                s[k] = c;
                k += c >= 'a';
            }
            s.resize(k);
        }
        pos.clear(0, 26);
        return move(s);
    }


    string clearStars(string s) {
        int n = s.size();
        priority_queue<char, vector<char>, greater<char>> pq;
        unordered_map<char, vector<int>> freq;
        vector<bool>vis(n, true);

        for(int i = 0;i<n;i++){
            if(s[i] == '*') {
                char c = pq.top();
                pq.pop();

                int last = freq[c].back();
                freq[c].pop_back();
                vis[last] = false;
            }
            else {
                pq.push(s[i]);
                freq[s[i]].push_back(i);
            }
        }

        string ans = "";
        for(int i = 0;i<vis.size();i++){
            if(vis[i]) {
                ans += s[i];
            }
        }
        return ans;
    }
};

Solution::pq_t Solution::pos;

auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();

int main() {
}
