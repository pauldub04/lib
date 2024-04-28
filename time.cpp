// #pragma GCC optimize("Ofast")
// #pragma GCC target ("sse2") sse, sse2, sse3, sse4, sse4.1, sse4.2

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

// or

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

// or

#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
int main() {
    IOS;

    ll t = 1;
//    cin >> t;
    forn(i, t) {
        clock_t z = clock();
        solve(t);
        debug("Total Time: %.3f\n", (double)(clock() - z) / CLOCKS_PER_SEC);
    }

    return 0;
}
