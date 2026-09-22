class Solution {
    struct Node {
        int prod = 1;
        int cnt[5] = {};
    };

    int k;
    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node res;
        res.prod = (a.prod * b.prod) % k;

        for (int i = 0; i < k; i++)
            res.cnt[i] = a.cnt[i];

        for (int i = 0; i < k; i++)
            res.cnt[(a.prod * i) % k] += b.cnt[i];

        return res;
    }

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            int v = nums[l] % k;
            tree[p].prod = v;
            tree[p].cnt[v] = 1;
            return;
        }

        int m = (l + r) / 2;

        build(p * 2, l, m, nums);
        build(p * 2 + 1, m + 1, r, nums);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            val %= k;

            tree[p] = Node();
            tree[p].prod = val;
            tree[p].cnt[val] = 1;
            return;
        }

        int m = (l + r) / 2;

        if (idx <= m)
            update(p * 2, l, m, idx, val);
        else
            update(p * 2 + 1, m + 1, r, idx, val);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int m = (l + r) / 2;

        if (qr <= m)
            return query(p * 2, l, m, ql, qr);

        if (ql > m)
            return query(p * 2 + 1, m + 1, r, ql, qr);

        Node left = query(p * 2, l, m, ql, qr);
        Node right = query(p * 2 + 1, m + 1, r, ql, qr);

        return merge(left, right);
    }

public:
    vector<int> resultArray(vector<int>& nums, int K, vector<vector<int>>& queries) {
        k = K;
        int n = nums.size();

        tree.resize(4 * n);
        build(1, 0, n - 1, nums);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};