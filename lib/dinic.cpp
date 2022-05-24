struct dinic {
    
    int src, sink, m = 0;
    ll inf = 1e18, flow = 0;
    vector<vector<array<int, 2> > > g;
    vector<ll> cap;
    vector<int> lvl, ptr;
    queue<int> q;

    dinic(int n, const vector<tuple<int, int, ll> > &e, int src_, int sink_)
        : src(src_), sink(sink_), g(n+1), lvl(n+1), ptr(n+1)
    {
       
        for(auto [i, j, w] : e){
            cap.push_back(w);
            cap.push_back(0);
            g[i].push_back({j, m++});
            g[j].push_back({i, m++});
        }

        while(bfs()){
            fill(ptr.begin(), ptr.end(), 0);
            while(ll f = dfs(src, inf)) flow += f;
        }
    }

    int bfs(){
        fill(lvl.begin(), lvl.end(), 0);
        lvl[src] = 1;
        q.push(src);
        while(!q.empty()){
            int i = q.front();
            q.pop();
            for(auto j : g[i]){
                if(lvl[j[0]] || cap[j[1]] <= 0) continue;
                lvl[j[0]] = lvl[i]+1;
                q.push(j[0]);
            }
        }
        return lvl[sink];
    }

    ll dfs(int i, ll f){
        if(i == sink) return f;
        for(int &j=ptr[i]; j<(int)g[i].size(); j++){
            auto &x = g[i][j];
            if(lvl[x[0]] != lvl[i]+1 || cap[x[1]] <= 0) continue;
            ll ff = dfs(x[0], min(f, cap[x[1]]));
            if(ff > 0){
                cap[x[1]] -= ff;
                cap[x[1]^1] += ff;
                return ff;
            }
        }
        return 0;
    }

    vector<array<int, 2> > &operator[](int i){ return g[i]; }
    ll &operator()(int i){ return cap[i]; }
};
