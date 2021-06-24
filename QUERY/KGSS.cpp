#include<bits/stdc++.h>
using namespace std;
#define ll             long long int
#define ld             long double
#define mod                  1000000007
#define inf                  1e18
#define endl          "\n"
#define pb             push_back
#define vi                   vector<ll>
#define vs             vector<string>
#define pii                  pair<ll,ll>
#define ump            unordered_map
#define mp             make_pair
#define pq_max               priority_queue<ll>
#define pq_min               priority_queue<ll,vi,greater<ll> >
#define all(n)           n.begin(),n.end()
#define ff             first
#define ss             second
#define mid(l,r)             (l+(r-l)/2)
#define bitc(n)          __builtin_popcount(n)
#define zrobits(x)           __builtin_ctzll(x)
#define looprev(i,a,b)       for(int i=(a);i>=(b);i--)
#define logarr(arr,a,b)      for(int z=(a);z<=(b);z++) cout<<(arr[z])<<" ";cout<<endl;  
#define loop(i,a,b)        for(int i=(a);i<=(b);i++)
template <typename T> T      gcd(T a, T b){if(a%b) return gcd(b,a%b);return b;}
template <typename T> T      lcm(T a, T b){return (a*(b/gcd(a,b)));}
const int maxn = 100004;
void solve();

ll arr[100004];
pair<ll, ll> st[4 * 100004];

void build(ll si, ll ss, ll se){
  if(ss == se){
    st[si].first = arr[ss]; st[si].second = 0;
    return;
  }
  ll m = mid(ss, se);
  build(2 * si, ss, m);
  build(2 * si + 1, m + 1, se);
  if(st[2 * si + 1].first >= st[2 * si].first){
  	st[si].first = st[2 * si + 1].first;
  	st[si].second = max(st[2 * si + 1].second, st[2 * si].first);
  }
  else if(st[2 * si].first >= st[2 * si + 1].first){
  	st[si].first = st[2 * si].first;
  	st[si].second = max(st[2 * si + 1].first, st[2 * si].second);
  }
}

void update(ll si, ll ss, ll se, ll qi, ll val){
	if(ss == se){
		st[si].first = val;
		arr[qi] = val;
		return;
	}
	ll m = mid(ss, se);
	if(qi <= m) update(2 * si, ss, m, qi, val);
	else update(2 * si + 1, m + 1, se, qi, val);
	if(st[2 * si + 1].first >= st[2 * si].first){
	  	st[si].first = st[2 * si + 1].first;
	  	st[si].second = max(st[2 * si + 1].second, st[2 * si].first);
	  }
	  else if(st[2 * si].first >= st[2 * si + 1].first){
	  	st[si].first = st[2 * si].first;
	  	st[si].second = max(st[2 * si + 1].first, st[2 * si].second);
	  }
}

pair<ll,ll> query(ll si, ll ss, ll se, ll qs, ll qe){
  if(ss > qe or se < qs) return {0, 0};
  if(ss >= qs and se <= qe) return {st[si].first, st[si].second};
  ll m = mid(ss, se);
  pair<ll, ll> p1 = query(2 * si, ss, m, qs, qe);
  pair<ll, ll> p2 = query(2 * si + 1, m + 1, se, qs, qe);
  pair<ll,ll> result;
  if(p1.first >= p2.first){
	result.first = p1.first;
	result.second = max(p2.first, p1.second);
  }
  else if(p2.first >= p1.first){
  	result.first = p2.first;
  	result.second = max(p1.first, p2.second);
  }
  return result;
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
  ll n, q; cin >> n;
  loop(i, 1, n) cin >> arr[i];
  cin >> q;
  build(1, 1, n);
  ll l, r;
  char type;
  while(q--){
    cin >> type;
    cin >> l >> r;
    if(type == 'Q'){
	    pair<ll,ll> p = query(1, 1, n, l, r);
	    cout << p.first + p.second << endl;
    }else{
    	update(1, 1, n, l, r);
    }
  }
}
