struct mincost {
    
    int src, sink, n, m = 0;
    ll inf = 1e18;
    vector<vector<array<int, 2> > > G;
    vector<ll> CAP, COST;

    mincost(int nn, const vector<tuple<int, int, ll, ll> > &e, int in, int out) :
        src(in), sink(out), n(nn+1), G(nn+1)
    {
        for(auto [i, j, w, c] : e){
            CAP.push_back(w);
            CAP.push_back(0);
            COST.push_back(c);
            COST.push_back(-c);
            G[i].push_back({j, m++});
            G[j].push_back({i, m++});
        }
    }

    vector<array<ll, 2> > flowcost(ll target){

        vector<vector<array<int, 2> > > g = G;
        queue<int> q;
        vector<ll> cap = CAP, cost = COST, d(n+1), f(n+1);
        vector<int> p(n+1);
        vector<bool> vis(n+1);

        vector<array<ll, 2> > ans;

        ll fsum = 0, csum = 0;

        while(fsum < target){
            
            fill(d.begin(), d.end(), inf);
            fill(vis.begin(), vis.end(), 0);

            q.push(src);
            d[src] = 0;

            while(!q.empty()){
                
                int i = q.front();
                q.pop();

                vis[i] = 0;
                
                for(auto [j, e] : g[i]){
                    if(cap[e] > 0 && d[i] + cost[e] < d[j]){
                        d[j] = d[i] + cost[e];
                        p[j] = i;
                        f[j] = e;
                        if(!vis[j]){
                            vis[j] = 1;
                            q.push(j);
                        }
                    }
                }
            }

            while(!q.empty()) q.pop();

            if(d[sink] == inf) break;

            ll minf = target - fsum;
            
            int i = sink;
            while(i != src){
                minf = min(minf, cap[f[i]]);
                i = p[i];
            }

            fsum += minf;
            csum += minf * d[sink];

            i = sink;
            while(i != src){
                cap[f[i]] -= minf;
                cap[f[i]^1] += minf;
                i = p[i];
            }

            ans.pb({fsum, csum});
        }

        return ans;
    }
};
