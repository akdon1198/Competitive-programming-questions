#include<bits/stdc++.h>
using namespace std;
#define ll 				     long long int
#define ld				     long double
#define mod                  1000000007
#define inf                  1e18
#define endl			    "\n"
#define pb 				     push_back
#define vi                   vector<ll>
#define vs				     vector<string>
#define pii                  pair<ll,ll>
#define ump				     unordered_map
#define mp 				     make_pair
#define pq_max               priority_queue<ll>
#define pq_min               priority_queue<ll,vi,greater<ll> >
#define all(n) 			     n.begin(),n.end()
#define ff 				     first
#define ss 				     second
#define mid(l,r)             (l+(r-l)/2)
#define bitc(n) 		     __builtin_popcount(n)
#define zrobits(x)           __builtin_ctzll(x)
#define looprev(i,a,b) 	     for(int i=(a);i>=(b);i--)
#define logarr(arr,a,b)	     for(int z=(a);z<=(b);z++) cout<<(arr[z])<<" ";cout<<endl;	
#define loop(i,a,b) 	     for(int i=(a);i<=(b);i++)
template <typename T> T      gcd(T a, T b){if(a%b) return gcd(b,a%b);return b;}
template <typename T> T      lcm(T a, T b){return (a*(b/gcd(a,b)));}
const int maxn = 50005;
void solve();

struct node
{
	ll maxsum; ll sum; ll bps; ll bss;
};

ll arr[50005];
node seg[4 * maxn];

void build(ll si, ll ss, ll se){
	if(ss == se){
		seg[si].bss = arr[ss];
		seg[si].bps = arr[ss];
		seg[si].sum = arr[ss];
		seg[si].maxsum = arr[ss];
		return;
	}
	ll m = mid(ss, se);
	build(2 * si, ss, m);
	build(2 * si + 1, m + 1, se);
	seg[si].bss = max(seg[2 * si + 1].bss, seg[2 * si + 1].sum + seg[2 * si].bss);
	seg[si].bps = max(seg[2 * si].bps, seg[2 * si].sum + seg[2 * si + 1].bps);
	seg[si].sum = seg[2 * si + 1].sum + seg[2 * si].sum;
	seg[si].maxsum = max({seg[2 * si + 1].maxsum, seg[2 * si].maxsum, seg[2 * si].sum + seg[2 * si + 1].bps, seg[2 * si + 1].sum + seg[2 * si].bss, seg[2 * si].bss + seg[2 * si + 1].bps});
}

node query(ll si, ll ss, ll se, ll qs, ll qe){
	node t;
	t.sum = t.maxsum = t.bps = t.bss = INT_MIN;
	if(se < qs or ss > qe) return t;
	if(ss >= qs and se <= qe){
		return seg[si];
	}
	ll m = mid(ss, se);
	node one = query(2 * si, ss, m, qs, qe);
	node two = query(2 * si + 1, m + 1, se, qs, qe);
	t.bss = max(two.bss, two.sum + one.bss);
	t.bps = max(one.bps, one.sum + two.bps);
	t.sum = two.sum + one.sum;
	t.maxsum = max({two.maxsum, one.maxsum, one.sum + two.bps, two.sum + one.bss, one.bss + two.bps});
	return t;
}

void update(ll si, ll ss, ll se, ll qi, ll val){
	if(ss == se){
		seg[si].sum = val;
		seg[si].maxsum = val;
		seg[si].bps = val;
		seg[si].bss = val;
		arr[qi] = val;
		return;
	}
	ll m = mid(ss, se);
	if(qi <= m) update(2 * si, ss, m, qi, val);
	else update(2 * si + 1, m + 1, se, qi, val);
	seg[si].bss = max(seg[2 * si + 1].bss, seg[2 * si + 1].sum + seg[2 * si].bss);
	seg[si].bps = max(seg[2 * si].bps, seg[2 * si].sum + seg[2 * si + 1].bps);
	seg[si].sum = seg[2 * si + 1].sum + seg[2 * si].sum;
	seg[si].maxsum = max({seg[2 * si + 1].maxsum, seg[2 * si].maxsum, seg[2 * si].sum + seg[2 * si + 1].bps, seg[2 * si + 1].sum + seg[2 * si].bss, seg[2 * si].bss + seg[2 * si + 1].bps});	
}

void file_i_o()
{
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
	#ifndef ONLINE_JUDGE
	    freopen("input.txt", "r", stdin);
	    freopen("output.txt", "w", stdout);
	#endif
}

int main() {
	file_i_o();	
	int t = 1;
	// cin >> t;
	while(t--){
		solve();
	}
	return 0;
}
// here 0 is for modify
void solve(){
	ll n; cin >> n;
	loop(i, 1, n) cin >> arr[i];
	build(1, 1, n);
	ll q; cin >> q;
	ll l, r, type;
	while(q--){
		cin >> type >> l >> r;
		if(type == 0){
			update(1, 1, n, l, r);
		}else{
			node t = query(1, 1, n, l, r);
			cout << t.maxsum << endl;
		}
	}
}
