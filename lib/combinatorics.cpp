
template<typename T> struct fpow{
    T MOD;
    fpow(T MOD_) : MOD(MOD_) {}
    fpow(){}
    T operator()(T a, T b){
        T ret = 1;
        for(;b;b>>=1){
            if(b&1) ret = (long long)ret*a%MOD;
            a = (long long)a*a%MOD;
        }
        return ret;
    }
}; 
template<typename T> struct fact{ 
    vector<T> f;
    fact(int n, const T MOD){
        f = vector<T>(n+1);
        f[0] = 1;
        for(int i=1; i<=n; i++) f[i] = (long long)i*f[i-1]%MOD;
    }
    fact(){}
    T operator()(int n){ return f[n]; }
};
template<typename T> struct fnCr{
    vector<vector<T> > C; 
    fnCr(int n, T MOD){
        C = vector<vector<T> >(n+1, vector<T>(n+1, 0));   
        for(int i=0; i<=n; i++){
            for(int j=0; j<=i; j++){
                if(j==0) C[i][j] = 1;
                else C[i][j] = (C[i-1][j-1]+C[i-1][j])%MOD;
            }
        }
    }
    fnCr(){}
    T operator()(int n, int r){ return C[n][r]; }
};
template<typename T> struct bnCr{
    T MOD;
    vector<T> f, inv; 
    bnCr(int n, T MOD_){
        MOD = MOD_;
        f = inv = vector<T>(n+1);
        f[0] = inv[0] = 1;
        fpow<T> pwr(MOD);
        for(int i=1; i<=n; i++){
            f[i] = (long long)i*f[i-1]%MOD;
            inv[i] = pwr(f[i], MOD-2); // assumes MOD is prime
        }
    }
    bnCr(){}
    T operator()(int n, int r){ return (long long)f[n]*inv[r]%MOD*inv[n-r]%MOD; }
};

