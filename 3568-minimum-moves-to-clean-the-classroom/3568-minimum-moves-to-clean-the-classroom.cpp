class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size(), n = classroom[0].size();
        vector<pair<int,int>> litter;
        int sr = 0, sc = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                } else if (classroom[i][j] == 'L') {
                    litter.push_back({i, j});
                }
            }
        }

        int k = litter.size();
        if (k == 0) return 0;

        vector<vector<int>> id(m, vector<int>(n, -1));
        for (int i = 0; i < k; i++)
            id[litter[i].first][litter[i].second] = i;

        int total = 1 << k;
        vector<vector<vector<int>>> dist(
            m, vector<vector<int>>(n, vector<int>(total * (energy + 1), -1))
        );

        queue<array<int,4>> q;
        dist[sr][sc][energy] = 0;
        q.push({sr, sc, energy, 0});

        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        while (!q.empty()) {
            auto [r, c, e, mask] = q.front();
            q.pop();

            int curDist = dist[r][c][mask * (energy + 1) + e];

            if (mask == total - 1)
                return curDist;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                if (classroom[nr][nc] == 'X')
                    continue;

                if (e == 0)
                    continue;

                int ne = e - 1;
                int nmask = mask;

                if (classroom[nr][nc] == 'L') {
                    int idx = id[nr][nc];
                    nmask |= (1 << idx);
                }

                if (classroom[nr][nc] == 'R')
                    ne = energy;

                int state = nmask * (energy + 1) + ne;

                if (dist[nr][nc][state] == -1) {
                    dist[nr][nc][state] = curDist + 1;
                    q.push({nr, nc, ne, nmask});
                }
            }
        }

        return -1;
    }
};