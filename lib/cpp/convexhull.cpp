// convex hull of points. Points that are on
// edges but are not vertices are included too.

#define CO complex<ll>
#define X real()
#define Y imag()

vector<CO> chull(vector<CO> v){

    auto cmp = [](CO a, CO b){ return a.X==b.X ? a.Y<b.Y : a.X<b.X; };
    
    sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());

    int n = v.size();
    if(n < 3) return v;

    vector<CO> hull(1, v[0]);

    auto cr = [](CO a, CO b) { return a.X*b.Y - a.Y*b.X; };
    
    auto half = [&](){
        for(int i=1, j=hull.size()-1, m=hull.size(); i<n; i++, j++){
            while(j>=m && cr(hull[j]-hull[j-1], v[i]-hull[j-1]) > 0){
                hull.pop_back(); j--;
            } hull.push_back(v[i]);
        }
    };

    half();
    reverse(v.begin(), v.end());
    half();

    sort(hull.begin(), hull.end(), cmp);
    hull.erase(unique(hull.begin(), hull.end()), hull.end());

    return hull;
}

