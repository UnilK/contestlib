struct HLD{
    
    // adamant's awesome HLD implementation <3
    // https://codeforces.com/blog/entry/53170
    // nodes are 1-indexed

    int n;
    vector<int> l, r, nxt, hop;

    HLD(vector<vector<int> > &g) :
        n(g.size()-1), l(g.size()), r(g.size()), nxt(g.size()), hop(g.size()){

        vector<int> sz(n+1, 0);

        auto dfs0 = [&](auto &&rec, int i) -> int {
            int tot = 0;
            sz[i] = 1;
            for(int &j : g[i]){
                if(!sz[j]){
                    tot += rec(rec, j);
                    if(sz[j] >= sz[g[i][0]]) swap(g[i][0], j);
                }
            }
            sz[i] += tot;
            return sz[i];
        };

        dfs0(dfs0, 1);

        int t = 0;
        auto dfs1 = [&](auto &&rec, int i) -> void {
            l[i] = t++;
            for(int j : g[i]){
                if(sz[j] < sz[i]){
                    if(j == g[i][0]){
                        nxt[j] = nxt[i];
                        hop[j] = hop[i];
                    } else {
                        nxt[j] = j;
                        hop[j] = i;
                    }
                    rec(rec, j);
                }
            }
            r[i] = t;
        };

        nxt[1] = hop[1] = 1;
        dfs1(dfs1, 1);
    }

    int &operator[](int i){ return l[i]; }
    array<int, 2> sub(int i){ return {l[i], r[i]}; }

    int lca(int a, int b){
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        return b;
    }

    vector<array<int, 2> > path(int a, int b, int e=0){
        vector<array<int, 2> > p;
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            p.pb({l[nxt[a]], l[a]});
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        if(max(l[b]+e, l[nxt[a]]) <= l[a]) p.pb({max(l[b]+e, l[nxt[a]]), l[a]});
        return p;
    }

    template<typename Q, typename T>
    void add(int a, int b, Q &seg, const T &val){
        auto s = path(a, b);
        for(auto [aa, bb] : s) seg.add(aa, bb, val);
    }

    template<typename Q, typename T>
    T sum(int a, int b, Q &seg, T x){
        auto s = path(a, b);
        for(auto [aa, bb] : s) x += seg.sum(aa, bb);
        return x;
    }
};
