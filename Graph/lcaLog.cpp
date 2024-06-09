class LCAFinder {
private:
    vector<vector<int>> g;
    vector<vector<int>> par;
    vector<int> lvl;
    int N;
    int L;

    void dfs(int node, int level) {
        lvl[node] = level;
        for (int x : g[node]) {
            if (lvl[x] == -1) { // Using -1 to indicate unvisited
                par[x][0] = node;
                dfs(x, level + 1);
            }
        }
    }

    void preprocessLca(int root) {
        lvl.assign(N, -1); // Initialize levels to -1 for unvisited nodes
        L = 0;
        for (int i = 1; i <= N; i <<= 1) L++; // Calculate the number of levels needed for sparse table
        par.assign(N, vector<int>(L, -1)); // Initialize parent table with -1
        dfs(root, 0); // Start DFS from the specified root
        for (int k = 1; k < L; ++k) {
            for (int i = 0; i < N; ++i) {
                if (par[i][k-1] != -1) {
                    par[i][k] = par[par[i][k-1]][k-1];
                }
            }
        }
    }

public:
    LCAFinder(vector<vector<int>> graph, int root) : g(graph) {
        N = g.size();
        preprocessLca(root);
    }

    int lca(int x, int y) {
        if (lvl[x] < lvl[y]) swap(x, y);
        for (int k = L - 1; k >= 0; --k) {
            if (lvl[x] - (1 << k) >= lvl[y]) {
                x = par[x][k];
            }
        }
        if (x == y) return x;
        for (int k = L - 1; k >= 0; --k) {
            if (par[x][k] != par[y][k]) {
                x = par[x][k];
                y = par[y][k];
            }
        }
        return par[x][0];
    }
};
