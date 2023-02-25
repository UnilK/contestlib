template<typename T> struct nCr{
    vector<T> f, inv;

    nCr(int n) : f(n+1, 1), inv(n+1){
        f[0] = 1;
        for(int i=1; i<=n; i++) f[i] = f[i-1]*i;
        inv[n] = 1 / f[n];
        for(int i=n-1; i>=0; i--) inv[i] = inv[i+1]*(i+1);
    }
    T operator()(int n, int r){ return f[n]*inv[r]*inv[n-r]; }
};

