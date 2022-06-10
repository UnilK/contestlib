mt19937 rng32(chrono::steady_clock::now().time_since_epoch().count());
int rnd(){ return rng32()>>1; }

// mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());
// ll rnd(){ return rng64()>>1; }

