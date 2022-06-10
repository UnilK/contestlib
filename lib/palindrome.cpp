
string splits(string s){
    int n = 2*s.size()+1;
    string ss(n, '#');
    for(int i=1; i<=n; i+=2) ss[i] = s[i/2];
    return ss;
}

vector<int> palindrome(string s){
    
    int n = s.size();
    vector<int> p(n, 0);

    for(int i=0, l=0, r=0; i<n; i++){   
        p[i] = min(p[l+l-i], max(0, r-i));
        if(i+p[i] >= r){
            while(i-p[i]-1 >= 0 && i+p[i]+1 < n && s[i-p[i]-1] == s[i+p[i]+1]) p[i]++;
            r = i + p[i];
            l = i;
        }
    }

    return p;
}
