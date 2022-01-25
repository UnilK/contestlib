template<typename T> struct Matrix{
    
    vector<vector<T> > mx;

    Matrix(int n, int m) : mx(vector<vector<T>>(n, vector<T>(m, 0))) {}
    Matrix(const vector<vector<T> > &mx_) : mx(mx_) {}
    Matrix(){}

    static Matrix<T> unit(int n){
        Matrix x(n, n);
        for(int i=0; i<n; i++) x[i][i] = 1;
        return x;
    }
    
    int r() const { return mx.size(); }
    int c() const { return r() ? mx[0].size() : 0; }

    vector<T>& operator[](int i){ return mx[i]; }
    T operator()(int i, int j) const { return mx[i][j]; }

    Matrix<T> &operator*=(const Matrix<T> &lhs){
        
        assert(r() == lhs.c());
        
        int n = lhs.r(), m = c(), l = r();
        vector<vector<T>> nx(n, vector<T>(m, 0));
        
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                for(int k=0; k<l; k++){
                    nx[i][j] += lhs(i, k)*mx[k][j];
                }
            }
        }
        
        mx.swap(nx);
        
        return *this;
    }

    friend Matrix<T> operator*(const Matrix<T> &lhs, Matrix<T> rhs){
        rhs *= lhs;
        return rhs;
    }

    T tolerance = 1e-10;
    Matrix<T> inv(){

        assert(c() == r());

        int n = r();
        Matrix<T> aux = *this, ret = unit(n);
        
        auto reduce = [&](int i, int j, T d){
            for(int k=0; k<n; k++){
                aux[j][k] -= d*aux[i][k];
                ret[j][k] -= d*ret[i][k];
            }
        };

        for(int i=0; i<n; i++){
            
            for(int j=i; j<n; j++){
                if(abs(aux[i][i]) < abs(aux[j][i])){
                    aux[i].swap(aux[j]);
                    ret[i].swap(ret[j]);
                }
            }

            if(abs(aux[i][i]) <= tolerance) continue;
            for(int j=0; j<n; j++) if(i != j) reduce(i, j, aux[j][i]/aux[i][i]);
            reduce(i, i, (aux[i][i]-1)/aux[i][i]);
        }
        
        return ret;
    }
};
