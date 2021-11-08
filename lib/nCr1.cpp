template<int MOD> struct nCr{
    vector<vector<int> > C; 
    nCr(int n) : C(n+1, vector<int>(n+1, 0)) {
        for(int i=0; i<=n; i++){
            for(int j=0; j<=i; j++){
                if(j==0) C[i][j] = 1;
                else C[i][j] = (C[i-1][j-1]+C[i-1][j])%MOD;
            }
        }
    }
    int operator()(int n, int r){ return C[n][r]; }
};

