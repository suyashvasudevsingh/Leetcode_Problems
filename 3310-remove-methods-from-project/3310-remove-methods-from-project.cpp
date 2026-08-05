class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& suspicious) {
        suspicious[node] = true;
        for (int nxt : graph[node]) {
            if (!suspicious[nxt])
                dfs(nxt, graph, suspicious);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> graph(n);

        for (auto &e : invocations)
            graph[e[0]].push_back(e[1]);

        vector<bool> suspicious(n, false);
        dfs(k, graph, suspicious);

        // If any outside method calls a suspicious method,
        // removal is impossible.
        for (auto &e : invocations) {
            if (!suspicious[e[0]] && suspicious[e[1]]) {
                vector<int> ans;
                for (int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};