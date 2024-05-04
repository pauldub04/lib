#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

// https://codeforces.com/blog/entry/60737
// со своим хешем
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
__gnu_pbds::gp_hash_table<ll, ll, chash> cnt;
__gnu_pbds::cc_hash_table<ll, ll, chash> cnt;


// без хеша
__gnu_pbds::gp_hash_table<ll, ll> cnt;
__gnu_pbds::cc_hash_table<ll, ll> cnt;


// https://codeforces.com/blog/entry/72675?locale=ru
// или
#include <tr1/unordered_map>
tr1::unordered_map<ll, ll> cnt;

