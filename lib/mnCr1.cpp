template<typename T> struct nCr{
    vector<vector<T> > C; 
    nCr(int n) : C(n+1, vector<T>(n+1, 0)) {
        for(int i=0; i<=n; i++){
            for(int j=0; j<=i; j++){
                if(j==0) C[i][j] = 1;
                else C[i][j] = C[i-1][j-1]+C[i-1][j];
            }
        }
    }
    T operator()(int n, int r){ return C[n][r]; }
};

