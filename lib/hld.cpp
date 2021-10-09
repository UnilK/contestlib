template<typename T> struct HLD{
    
    // adamant's awesome HLD implementation <3
    // https://codeforces.com/blog/entry/53170
    // nodes are 1-indexed

    int n;
    vector<T> &v;
    vector<int> l, r, nxt, hop;
    segtree<T> seg;

    HLD(vector<vector<int> > &g, vector<T> &v_):
        n(g.size()-1), v(v_), l(vector<int>(g.size())), r(vector<int>(g.size())),
        nxt(vector<int>(g.size())), hop(vector<int>(g.size())){

        vector<int> sz(n+1, 0);

        auto dfs0 = [&](auto &&dfs0, int i) -> int{
            int tot = 0;
            sz[i] = 1;
            for(int &j : g[i]){
                if(!sz[j]){
                    tot += dfs0(dfs0, j);
                    if(sz[j] >= sz[g[i][0]]) swap(g[i][0], j);
                }
            }
            sz[i] += tot;
            return sz[i];
        };

        dfs0(dfs0, 1);

        int t = 0;
        auto dfs1 = [&](auto &&dfs1, int i) -> void{
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
                    dfs1(dfs1, j);
                }
            }
            r[i] = t;
        };

        nxt[1] = hop[1] = 1;
        dfs1(dfs1, 1);

        // query initialization

        vector<T> ord_val(n);
        for(int i=1; i<=n; i++) ord_val[l[i]] = v[i];
        seg = segtree<T>(ord_val);
    }

    T nil = 0;

    int lca(int a, int b){
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        return b;
    }

    void oper(int i, T o){
        v[i] = o;
        seg.oper(l[i], o);
    }

    T qer(int a, int b){
        T ret = nil;
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            ret = join(ret, seg.qer(l[nxt[a]], l[a]));
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        ret = join(ret, seg.qer(max(l[b], l[nxt[a]]), l[a]));
        return ret;
    }

    T join(T a, T b){
        return a+b;
    }
};

