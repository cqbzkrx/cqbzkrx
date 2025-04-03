namespace chtholly_tree {
    template <typename T = ll>
    struct Node {    // 表示区间l ~ r的元素权值都是val
        int l, r;
        mutable T val;
        Node (int _l = 0, int _r = -1, T _val = 0) : l (_l), r (_r), val (_val) {}
        bool operator < (const Node &b) const {return l < b.l;}
    };

    template <typename T = ll, class info = Node <T>>
    class ODT {
    public:
        set <info> s;     // 核心
        vector <pair <T, int>> vec;

        set <info> :: iterator split (int pos) {  // iterator -> 迭代器  将含有pos的区间分成[l, pos - 1] and [pos + 1, r]
            auto it = s.lower_bound (info (pos));
            if (it != s.end () && it -> l == pos) return it;  // 如果本来l就是某区间的左端点
            --it;

            if (pos > it -> r) return s.end ();  // l不包含在最大区间内
            auto L = it -> l, R = it -> r, v = it -> val;
            s.erase (it);
            s.insert (info (L, pos - 1, v));
            auto [it2, f] = s.insert (info (pos, R, v));  // insert返回 -> pair <iterator, bool>   重新建立两个区间
            return it2;    // 返回l区间的迭代器
        }

        void add (int l, int r, T v = 1) {  // 对[l, r]内元素加上val
            split (l);
            auto itr = split (r + 1), itl = split (l);
            for (; itl != itr; itl++) itl -> val += v;
        }

        void assign (int l, int r, T val = 0) {  // 将[l, r]内元素推平成val
            split (l);
            auto itr = split (r + 1), itl = split (l);
            s.erase (itl, itr);
            s.insert (info (l, r, val));
        }

        T qry_sum (int l, int r, T x, T k) {  // 区间元素k次方求和
            T ans = 0;
            split (l);
            auto itr = split (r + 1), itl = split (l);
            vec.clear ();
            for (; itl != itr; itl++) ans = (ans + (math :: qpow (itl -> val, x, k) * (T) (itl -> r - itl -> l + 1)) % k) % k;
            return ans;
        }

        T qry_kth (int l, int r, int k, bool reversed = false) {  // 寻找[l, r]内第k大元素 (可重复)
            if (reversed) k = r - l + 2 - k;
            split (l);
            auto itr = split (r + 1), itl = split (l);
            vec.clear ();
            for (; itl != itr; itl++) vec.push_back ({itl -> val, itl -> r - itl -> l + 1});

            sort (all(vec));
            for (auto [val, len] : vec) {
                k -= len;
                if (k <= 0) return val;
            }
            return -1;
        }

        ODT () {}
        ODT (const vector <T> &a) {init (a);}

        void init (const vector <T> &a) {
            int n = a.size ();
            for (int i = 0; i < n; i++) {
                int l = i, r = i;
                while (r < n && a[l] == a[r]) r++;
                s.insert (info (l, r - 1, a[l]));
                i = r - 1;
            }
        }
    };
}
