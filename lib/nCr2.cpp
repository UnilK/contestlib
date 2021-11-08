template<int MOD> struct nCr{
    vector<int> f, inv;

    int exeu(int i){
        int v0 = MOD, v1 = i, r0 = 0, r1 = 1;
        while(v1){
            int d = v0/v1;
            r0 -= d*r1; v0 -= d*v1;
            swap(v0, v1); swap(r0, r1);
        }
        return r0 < 0 ? r0+MOD : r0; 
    }

    nCr(int n) : f(n+1, 1), inv(n+1){
        f[0] = inv[0] = 1;
        for(int i=1; i<=n; i++){
            f[i] = (long long)i*f[i-1]%MOD;
            inv[i] = exeu(f[i]);
        }
    }
    int operator()(int n, int r){ return (long long)f[n]*inv[r]%MOD*inv[n-r]%MOD; }
};

