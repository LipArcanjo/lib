#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define eb emplace_back
#define mk make_pair
#define fi first
#define se second
#define mset(a,b) memset(a, b, sizeof(a))
#define dbg(x) cout << "[" << #x << "]: " << x << endl;
#define forn(i,n) for(int i=0; i < n;i++)
#define each(val, v) for(auto val : v)
#define abs(u) (u >= 0 ? u : -u)

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vl = vector<ll>;

const int MAXN = 2e5 + 5;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;

void solve(){
    int t;
    cin >> t;
    int cnt = 0;
    while(t--){
        if(cnt > 0) cout << endl;
        cnt++;
        string s;
        string pat;
        cin >> s >> pat;
        int size = s.size();
        int pat_len = pat.size();
        vector<int> b(pat_len+1);

        int i = 0;
        int j = -1;
        b[0] = -1;

        while(i < pat_len){
            while(j >= 0 && pat[i] != pat[j]){
                j = b[j];
            }
            i++; j++;
            b[i] = j;
        }

        i = 0, j = 0;
        vector<int> ans;
        while(i < size){
            while(j >= 0 && s[i] != pat[j]){
                j = b[j];
            }
            i++; j++;
            if(j == pat_len){
                ans.pb(i-j);
                j = b[j];
            }
        }
        size = ans.size();
        if(size > 0){
            cout << ans.size() << endl;
            
            for(int i = 0; i < size; i++){
                cout << ans[i]+1 << " ";
            }
            cout << endl;
        }else{
            cout << "Not Found"<<endl;
        }
        
        
        
    }
}

int main(){

    ios::sync_with_stdio(false); cin.tie(NULL);
    solve();

    return 0;
}