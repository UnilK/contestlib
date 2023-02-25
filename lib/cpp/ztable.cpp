vector<int> ztab(string &s){
    
    int n = s.size();
    vector<int> z(n, 0);
 
    for(int i=1, l=0, r=0; i<n; i++){
        r = max(r-1, 0);
        z[i] = min(r, z[++l]);
        while(i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
        if(z[i] > r) r = z[i], l = 0;
    }
 
    return z;
}

