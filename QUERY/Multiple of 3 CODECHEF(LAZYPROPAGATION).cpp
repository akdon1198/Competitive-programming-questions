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
const int maxn = 100005;
void solve();

struct node{
	int arr[3];
};

ll lazy[4 * maxn];
node segment[4 * maxn];

void build(ll si, ll ss, ll se){
	if(ss == se){
		segment[si].arr[0] = 1;
		segment[si].arr[1] = 0;
		segment[si].arr[2] = 0;
		return;
	}

	ll m = mid(ss, se);
	build(2 * si, ss, m);
	build(2 * si + 1, m + 1, se);
	segment[si].arr[0] = segment[2 * si].arr[0] + segment[2 * si + 1].arr[0];
	segment[si].arr[1] = segment[2 * si].arr[1] + segment[2 * si + 1].arr[1];
	segment[si].arr[2] = segment[2 * si].arr[2] + segment[2 * si + 1].arr[2];
}

void shift(ll i){
	ll temp = segment[i].arr[2];
	segment[i].arr[2] = segment[i].arr[1];
	segment[i].arr[1] = segment[i].arr[0];
	segment[i].arr[0] = temp;
}

long long query(ll si, ll ss, ll se, ll qs, ll qe){
	if(lazy[si]){
		ll add = lazy[si];
		lazy[si] = 0;
		if(ss != se){
			lazy[2 * si] += add;
			lazy[2 * si + 1] += add;
		}
		add %= 3;
		for(ll i = 0; i < add; i++){
			shift(si);
		}
	}	
	if(ss > qe or se < qs) return 0;
	if(ss >= qs and se <= qe){
		return segment[si].arr[0];
	}
	ll m = mid(ss, se);
	return query(2 * si, ss, m, qs, qe) + query(2 * si + 1, m + 1, se, qs, qe);
}

void update(ll si, ll ss, ll se, ll qs, ll qe){
	if(lazy[si]){
		ll add = lazy[si];
		lazy[si] = 0;
		if(ss != se){
			lazy[2 * si] += add;
			lazy[2 * si + 1] += add;
		}
		add %= 3;
		for(ll i = 0; i < add; i++){
			shift(si);
		}
	}
	if(ss > qe or se < qs) return;
	if(ss >= qs and se <= qe){
		shift(si);
		if(ss != se){
			lazy[2 * si]++; lazy[2 * si + 1]++;
		}
		return;
	}
	ll m = mid(ss, se);
	update(2 * si, ss, m, qs, qe);
	update(2 * si + 1, m + 1, se, qs, qe);
	segment[si].arr[0] = segment[2 * si].arr[0] + segment[2 * si + 1].arr[0];
	segment[si].arr[1] = segment[2 * si].arr[1] + segment[2 * si + 1].arr[1];
	segment[si].arr[2] = segment[2 * si].arr[2] + segment[2 * si + 1].arr[2];	
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

void solve(){
	ll n, q, code, l, r; cin >> n >> q;
	build(1, 1, n);
	while(q--){
		cin >> code >> l >> r;
		if(code == 0){
			update(1, 1, n, l + 1, r + 1);
		}else{
			cout << query(1, 1, n, l + 1, r + 1) << endl;
		}
	}
}