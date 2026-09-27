class Solution {
public:
    set<string> dfs(string s, int& i) {
        set<string> res;
        vector<string> cur = {""};

        while (i < s.size() && s[i] != '}') {
            if (s[i] == '{') {
                i++;
                set<string> inside = dfs(s, i);
                i++;

                vector<string> temp;
                for (string a : cur)
                    for (string b : inside)
                        temp.push_back(a + b);

                cur = temp;
            }
            else if (s[i] == ',') {
                for (string x : cur)
                    res.insert(x);
                cur = {""};
                i++;
            }
            else {
                for (string& x : cur)
                    x += s[i];
                i++;
            }
        }

        for (string x : cur)
            res.insert(x);

        return res;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;
        set<string> ans = dfs(expression, i);
        return vector<string>(ans.begin(), ans.end());
    }
};