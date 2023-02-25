
struct LCA {
    
    int n, N = 1;
    vector<int> pos, lvl;
    vector<array<int, 2> > seg;

    LCA(vector<vector<int> > &g, int r=1) :
        n((int)g.size()-1), pos(g.size()), lvl(g.size()) {
        
        while(N<2*n-1) N *= 2;
        seg.resize(2*N);

        int t = 0;
        auto dfs = [&](auto &&dfs, int i) -> void {
            pos[i] = N+t;
            for(int j : g[i]){
                if(!lvl[j]){
                    seg[N+t++] = {lvl[i], i};
                    lvl[j] = lvl[i]+1;
                    dfs(dfs, j);
                }
            }
            seg[N+t++] = {lvl[i], i};
        };

        lvl[r] = 1;
        dfs(dfs, r);

        for(int i=N-1; i; i--) seg[i] = min(seg[2*i], seg[2*i+1]);
    }

    int get(int l, int r){
        
        l = pos[l]; r = pos[r];
        if(l>r) swap(l, r);
        
        array<int, 2> low = {2*N+1, 0};
        while(l<=r){
            if(l&1) low = min(low, seg[l++]);
            if(~r&1) low = min(low, seg[r--]);
            l/=2; r/=2;
        }

        return low[1];
    }

};
