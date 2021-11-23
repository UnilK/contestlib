template<typename T> struct Matrix{
    
    vector<vector<T> > mx;

    Matrix(int n, int m) : mx(vector<vector<T>>(n, vector<T>(m, 0))) {}
    Matrix(vector<vector<T> > mx_) : mx(mx_) {}
    Matrix(){}

    static Matrix<T> unit(int n){
        Matrix x(n, n);
        for(int i=0; i<n; i++) x[i][i] = 1;
        return x;
    }
    
    int w() const { return mx.size(); }
    int h() const { if(w()){ return mx[0].size(); } return 0; }

    vector<T>& operator[](int i){ return mx[i]; }
    T operator()(int i, int j) const { return mx[i][j]; }

    Matrix<T> &operator*=(const Matrix<T> &rhs){
        if(h() == rhs.w()){
            int n = w(), m = rhs.h(), l = h();
            vector<vector<T>> nx(n, vector<T>(m, 0));
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    for(int k=0; k<l; k++){
                        nx[i][j] += mx[i][k]*rhs(k, j);
                    }
                }
            }
            mx.swap(nx);
        } else {
            mx.resize(0);
        }
        return *this;
    }

    friend Matrix<T> operator*(Matrix<T> lhs, const Matrix<T> &rhs){
        lhs *= rhs;
        return lhs;
    }

    T tolerance = 0;
    Matrix<T> inv(){

        if(h() != w()) return unit(0);

        int n = w();
        Matrix<T> aux = *this, ret = unit(n);

        auto reduce = [&](int i, int j, T d){
            for(int k=0; k<n; k++){
                aux[i][k] -= d*aux[j][k];
                ret[i][k] -= d*ret[j][k];
            }
        };

        for(int j=0; j<n; j++){
            for(int i=j; i<n; i++){
                if(abs(aux[j][j]) < abs(aux[i][j])){
                    aux[i].swap(aux[j]);
                    ret[i].swap(ret[j]);
                }
            }
            if(abs(aux[j][j]) <= tolerance) continue;
            for(int i=0; i<n; i++) if(i != j) reduce(i, j, aux[i][j]/aux[j][j]);
            reduce(j, j, (aux[j][j]-1)/aux[j][j]);
        }
        
        return ret;
    }
};

