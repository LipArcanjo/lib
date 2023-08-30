//from codeforces.com/blog/entry/61306
#define SZ 233333
namespace linear_seq {
	ll qp(ll a,ll b)
	{
		ll x=1; a%=MOD;
		while(b)
		{
			if(b&1) x=x*a%MOD;
			a=a*a%MOD; b>>=1;
		}
		return x;
	}

	inline vector<int> BM(vector<int> x)
	{
		//ls: (shortest) relation sequence (after filling zeroes) so far
		//cur: current relation sequence
		vector<int> ls,cur;
		int lf,ld;
		for(int i=0;i<int(x.size());++i)
		{
			ll t=0;
			for(int j=0;j<int(cur.size());++j)
				t=(t+x[i-j-1]*(ll)cur[j])%MOD;
			if((t-x[i])%MOD==0) continue; //good so far
			if(!cur.size())
			{
				cur.resize(i+1);
				lf=i; ld=(t-x[i])%MOD;
				continue;
			}
			ll k=-(x[i]-t)*qp(ld,MOD-2)%MOD/*1/ld*/;
			vector<int> c(i-lf-1); //add zeroes in front
			c.pb(k);
			for(int j=0;j<int(ls.size());++j)
				c.pb(-ls[j]*k%MOD);
			if(c.size()<cur.size()) c.resize(cur.size());
			for(int j=0;j<int(cur.size());++j)
				c[j]=(c[j]+cur[j])%MOD;
			if(i-lf+(int)ls.size()>=(int)cur.size())
				ls=cur,lf=i,ld=(t-x[i])%MOD;
			cur=c;
		}
		for(int i=0;i<int(cur.size());++i)
			cur[i]=(cur[i]%MOD+MOD)%MOD;
		return cur;
	}
	int m;
	ll a[SZ],h[SZ],t_[SZ],s[SZ],t[SZ];
	inline void mull(ll*p,ll*q)
	{
		for(int i=0;i<m+m;++i) t_[i]=0;
		for(int i=0;i<m;++i) if(p[i])
			for(int j=0;j<m;++j)
				t_[i+j]=(t_[i+j]+p[i]*q[j])%MOD;
		for(int i=m+m-1;i>=m;--i) if(t_[i])
			for(int j=m-1;~j;--j)
				t_[i-j-1]=(t_[i-j-1]+t_[i]*h[j])%MOD;
		for(int i=0;i<m;++i) p[i]=t_[i];
	}
	inline ll calc(ll K)
	{
		for(int i=m;~i;--i)
			s[i]=t[i]=0;
		//init
		s[0]=1; if(m!=1) t[1]=1; else t[0]=h[0];
		//binary-exponentiation
		while(K)
		{
			if(K&1) mull(s,t);
			mull(t,t); K>>=1;
		}
		ll su=0;
		for(int i=0;i<m;++i) su=(su+s[i]*a[i])%MOD;
		return (su%MOD+MOD)%MOD;
	}
	inline int work(vector<int> x,ll n)
	{
		if(n<int(x.size())) return x[n];
		vector<int> v=BM(x); m=v.size(); if(!m) return 0;
		for(int i=0;i<m;++i) h[i]=v[i],a[i]=x[i];
		return calc(n);
	}
}
