
vector<AR(2) > blocut(int &n, const vector<array<int, 2> > &e){
    
    vector<AR(2) > d;
    vector<vector<int> > g(n+1);

    for(auto [a, b] : e){ g[a].pb(b); g[b].pb(a); }

    VI lvl(n+1, 0), up(n+1, 0);

    auto dfs0 = [&](auto &&dfs0, int i) -> int {
        for(int j : g[i]){
            if(!lvl[j]){ up[j] = lvl[j] = lvl[i]+1; up[i] = min(up[i], dfs0(dfs0, j)); }
            else up[i] = min(up[i], lvl[j]);
        }
        return up[i];
    };

    auto dfs1 = [&](auto &&dfs1, int i, int c) -> void {
        for(int j : g[i]){
            if(lvl[i]+1 != lvl[j]) continue;
            if(up[j] == lvl[i]){
                d.pb({++n, j});
                d.pb({n, i});
                dfs1(dfs1, j, n);
            } else {
                d.pb({c, j});
                dfs1(dfs1, j, c);
            }
        }
    };

    up[1] = lvl[1] = 1;
    dfs0(dfs0, 1);
    dfs1(dfs1, 1, 0);

    return d;
}

tuple<int, vector<int>, vector<vector<int> > > cute(const vector<vector<int> > &g){
   
    int n = g.size()-1;
    VI lvl(n+1, 0), up(n+1, 0), col(n+1, 0);

    auto dfs0 = [&](auto &&dfs0, int i, int p) -> int {
        for(int j : g[i]){
            if(j == p) continue;
            if(!lvl[j]){ up[j] = lvl[j] = lvl[i]+1; up[i] = min(up[i], dfs0(dfs0, j, i)); }
            else up[i] = min(up[i], lvl[j]);
        }
        return up[i];
    };

    int c = 1;
    vector<vector<int> > gg(2);

    auto dfs1 = [&](auto &&dfs1, int i) -> void {
        
        for(int j : g[i]){
            if(lvl[i]+1 != lvl[j]) continue;
            if(up[j] == lvl[j]){
                
                col[j] = ++c;
                
                gg.pb({});
                gg[col[i]].pb(col[j]);
                gg[col[j]].pb(col[i]);
                
                dfs1(dfs1, j);
            } else {
                col[j] = col[i];
                dfs1(dfs1, j);
            }
        }
    };

    col[1] = up[1] = lvl[1] = 1;
    dfs0(dfs0, 1, 1);
    dfs1(dfs1, 1);

    return {c, col, gg};
}

