template<int MOD> struct rhash{
    
    int n;
    vector<int> h, p;
    
    rhash(string &s, int c=0) : n(s.size()), h(n+1, 0), p(n+1, 1) {
        if(!c) c = rnd();
        for(int i=1; i<=n; i++){
            h[i] = ((long long)h[i-1]*c+s[i-1])%MOD;
            p[i] = (long long)p[i-1]*c%MOD;
        }
    }
 
    int operator()(int l, int r) const {
        int hsh = (h[r+1]-(long long)h[l]*p[r-l+1])%MOD;
        return hsh < 0 ? hsh+MOD : hsh;
    }
};

using rh = rhash<998244353>;

