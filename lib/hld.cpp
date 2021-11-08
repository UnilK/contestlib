template<
typename T, typename L,
template<typename, typename> typename O,
template<typename, typename, template<typename, typename> typename> typename S>
struct HLD{
    
    // adamant's awesome HLD implementation <3
    // https://codeforces.com/blog/entry/53170
    // nodes are 1-indexed

    using X = O<T, L>;
    int n, isedge;
    vector<int> l, nxt, hop;
    S<T, L, O> seg;

    HLD(vector<vector<int> > &g, vector<T> v={}, int isedge_=0):
        n(g.size()-1), isedge(isedge_), l(g.size()), nxt(g.size()), hop(g.size()){

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
        };

        nxt[1] = hop[1] = 1;
        dfs1(dfs1, 1);

        vector<T> ord(n+1);
        for(int i=1; i<=n; i++) ord[l[i]] = v[i];
        seg.init(n, ord);
    }

    int lca(int a, int b){
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        return b;
    }

    void add(int a, int b, L val){
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            seg.add(l[nxt[a]], l[a], val);
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        seg.add(max(l[b]+isedge, l[nxt[a]]), l[a], val);
    }

    T sum(int a, int b){
        T ret = X::qnil;
        while(nxt[a] != nxt[b]){
            if(l[nxt[a]] < l[nxt[b]]) swap(a, b);
            ret = X::join(ret, seg.sum(l[nxt[a]], l[a]));
            a = hop[a];
        }
        if(l[a] < l[b]) swap(a, b);
        return X::join(ret, seg.sum(max(l[b]+isedge, l[nxt[a]]), l[a]));
    }
};

