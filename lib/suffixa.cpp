vector<int> suffixa(string &s){
    
    int n = s.size();
    vector<int> v(n, 0);

    iota(v.begin(), v.end(), 0);
    vector<long long> c(2*n, 0);
    for(int i=0; i<n; i++) c[i] = s[i];

    auto cmp = [&](int a, int b){ return c[a] < c[b]; };
    sort(v.begin(), v.end(), cmp);

    for(int b=1; b<n; b*=2){
       
        for(int i=0, x=1; i<n; x++){
            for(ll j=c[v[i]]; i<n && c[v[i]] == j; i++) c[v[i]] = x;
        }

        for(int i=0; i<n; i++) c[i] = c[i]<<32 | c[i+b];
        sort(v.begin(), v.end(), cmp);
    }

    return v;
}

