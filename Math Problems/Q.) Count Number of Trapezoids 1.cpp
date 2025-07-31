#define INL __attribute__((always_inline))
#define HOT __attribute__((hot))
#define INL_ATTR noexcept INL HOT
#define OUTL_ATTR noexcept HOT
#define LAM_ATTR INL HOT noexcept

#pragma GCC diagnostic ignored "-Wshift-op-parentheses"
#pragma GCC diagnostic ignored "-Wvla-cxx-extension"
#pragma GCC diagnostic ignored "-Wunqualified-std-cast-call"

template <class K, class T, size_t max_size, uint8_t bucket_bits, class KeyHash = std::hash<K>>
class static_flat_hash_map {
public:
    typedef pair<K, T> value_type;
    typedef value_type *iterator;

    static constexpr K ZERO_VAL = K(1) << (sizeof(K) * 8 - 1);
    // static constexpr K ZERO_VAL { 0, 0, 0, 0, 1ull << 63 };
    static constexpr K RM_VAL = __builtin_constant_p((K)0xdeadbeefdeadbeefull) ? (K)0xdeadbeefdeadbeefull : (K)0xdeadbeefdeadbeefull;
    // static constexpr K RM_VAL { 0xdeadbeefdeadbeefull, 0xdeadbeefdeadbeefull, 0xdeadbeefdeadbeefull, 0xdeadbeefdeadbeefull, 0xdeadbeefdeadbeefull };

    static bool equal(const K &km, const K &ku) INL_ATTR {
        return km && (km == ZERO_VAL ? K(0) : km) == ku;
    }

    static bool equal_or_free(const K &km, const K &ku) INL_ATTR {
        return !km || (km == ZERO_VAL ? K(0) : km) == ku;
    }

    static bool valid(const K &km) INL {
        return km && km != RM_VAL;
    }

    static K unmask(const K &km) INL {
        return km == ZERO_VAL ? 0 : km;
    }

    static constexpr size_t min_cap = 16u;

    static constexpr size_t getcap(size_t size) INL_ATTR {
        return size <= min_cap ? min_cap : 1ull << (64u - __builtin_clzll(size - 1u));
    }

    static constexpr size_t cap = getcap(max_size);

private:
    value_type storage[cap];
    size_t limit;
    size_t count;

    static size_t hash(const K &k) INL_ATTR {
        return KeyHash()(k);
    }

    value_type *locate(const K &k) OUTL_ATTR {
        const size_t h = (hash(k) << bucket_bits) & (limit - 1);
        size_t i = h;
        while (i < limit && !equal_or_free(storage[i].first, k)) i++;
        if (i >= limit) {
            i = 0;
            while (i < h && !equal_or_free(storage[i].first, k)) i++;
        }
        return storage + i;
    }

public:

    value_type *locate_ins(const K &k) OUTL_ATTR {
        const size_t h = (hash(k) << bucket_bits) & (limit - 1);
        size_t i = h;
        size_t f = h;
        while (i < limit && !equal_or_free(storage[i].first, k)) {
            if (f == h && storage[i].first == RM_VAL) f = i;
            i++;
        }
        if (i >= limit) i = 0;
        while (i < h && !equal_or_free(storage[i].first, k)) {
            if (f == h && storage[i].first == RM_VAL) f = i;
            i++;
        }
        return storage + (f == h ? i : f);
    }

    static_flat_hash_map() INL_ATTR: limit(cap), count(0) {}

    bool contains(const K &k) INL_ATTR {
        value_type *p = locate(k);
        return equal(p->first, k);
    }

    iterator find(const K &k) INL_ATTR {
        value_type *p = locate(k);
        return p;
    }

    iterator insert(iterator p, const value_type &v) INL_ATTR {
        p->first = v.first ? v.first : ZERO_VAL;
        p->second = v.second;
        count++;
        return p;
    }

    iterator insert(const value_type &v) INL_ATTR {
        auto p = locate_ins(v.first);
        return insert(p, v);
    }

    T &operator[](const K &k) INL_ATTR {
        auto p = locate_ins(k);
        if (!equal(p->first, k))
            insert(p, pair(k, T()));
        return p->second;
    }

    bool erase(iterator p) INL_ATTR {
        auto n = p + 1 < storage + limit ? p + 1 : storage;
        p->first = n->first ? RM_VAL : 0;
        count--;
        return true;
    }

    bool erase(const K &k) INL_ATTR {
        auto p = locate(k);
        const bool er = equal(p->first, k) ? erase(p) : false;
        // count -= er;
        return er;
    }

    void clear() INL_ATTR {
        fill(storage, storage + limit, value_type());
        count = 0;
    }

    void setlimit(const size_t l) INL_ATTR {
        limit = getcap(l);
    }

    size_t getlimit() const INL_ATTR {
        return limit;
    }

    size_t size() const INL_ATTR {
        return count;
    }

    const value_type *data() INL_ATTR {
        return storage;
    }
};

class Solution {
private:
    static constexpr uint MAXN = 100'000, MOD = 1'000'000'007;
    static constexpr int MINV = -100'000'000, MAXV = 100'000'000;

    struct shift_hash {
        static uint operator()(int p) INL_ATTR {
            p -= MINV;
            return p ^ (p >> 7) ^ (p >> 18);
        }
    };

    typedef static_flat_hash_map<int, uint, MAXN, 1, shift_hash> map_t;

    static map_t ords;

public:
    static int countTrapezoids(const vector<vector<int>> &points) OUTL_ATTR {
        const uint n = points.size();
        ords.setlimit(n);
        uint64_t s = 0, q = 0;
        for (const auto &pt : points) {
            const int y = pt[1];
            uint &f = ords[y];
            s += f;
            q += (uint64_t)f * f * f;
            f++;
        }
        ords.clear();
        return (s * s - q) / 2 % MOD;
    }
};

Solution::map_t Solution::ords;

const auto init = []() noexcept {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();
