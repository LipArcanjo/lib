



#include<bits/stdc++.h>
#define L long long
#define vi vector<int>
#define pb push_back
using namespace std;
const int q=1000000007;
int n,m,p,r,t[100010],c[100010],d[100010],w[100010],u[100010],v[100010],f[100010][400],g[400][400];
bool o[100010];
vi a[100010],b[100010],x[400],y[100010];
map<vi,int> h;

/*
pre - calcula todas as representacoes possiveis de subespacos
    do z^5_2( 5 dimencoes que podem assumir valor 0 ou 1 ) com a
    operacao XOR ^ (0+0 = 0, 0+1 = 1, 1+0 = 1, 1+1 = 1)

O que percebi nesta representacao de subespacoes equivalentes:

Suponha que tenhamos o valor X, com o k sendo o bit 1 mais significativo

por exemplo, sendo X = 01AAA (k = 3).(o primeiro da direita pra esquerda
tem indice 0).

Podemos achar uma representacao onde o unico elemento que tenha o bit b[k]=1 
seja X(mesmo que transformando os outros bits de X).

Prova:
    Se temos um outro elemento Y com o bit significativo seja k 
        tambem(01BBB):

        Se Y < X, vamos trocar Y por X^Y, se tornando (00DDD).

        Se Y > X, vamos manter Y e trocar X por Y^X. X se tornando
            (00DDD), 
        
        Fazemos isto pra sempre manter uma mesma representacao, se temos
        a escolha de trocar X ou Y, mantemos o maior para manter um padrao.
    
    Se temos um outro elemento Y com o bit b[k] = 1, porem nao sendo
        o mais significativo(11BBB):

        Podemos trocar Y por Y^X --> 10CCC -> k=3 vira 0, 
            podemos voltar a ter Y com Y^X^X


---

Com esta ideia, podemos fazer uma equivalencia entre os subespacos.

para se reduzir um conjuntos de vetores a uma forma padrao:

seja N o numero de vetores que temos,

For i .. 0.. N:

  ordenamos o conjunto de vetores(representacao numerica, o maior numero)
  
  (sempre se ordena a cada iteracao, pois os elementos do xor podem acabar ficando menores, e sempre queremos escolher
  o maior elemento possivel para o bit significativo k, por uma questao de padrao, para se ter apenas uma representacao).

  Para o i elemento do conjunto iremos:

    Comparar ele com os demais elementos:
      Se existe um elemento j igual a ele, isto eh, a[i] = a[j], siginifica
      que temos um conjunto LD, ou seja, podemos retornar 0.

      Caso contrario:

        Se a[i]^a[j] < a[j]:
          a[j] ^= a[i]

        ... Vamos tentar entender o significado disto:

          Se a[i] tem o bit mais significativo maior que a[j], logo, a[i]^a[j] > a[j] por consequencia imediata.

          Se a[i] tem o mesmo bit mais significativo que a[j].
            Isto implica que teremos que fazer o procedimento para apenas
            deixar a[i] contendo apenas este elemento mais significativo.
          
          Se a[i] tem um bit mais siginifativo menor que bit mais significativo que a[i]:

          Vamos olhar o bit mais significativo de a[i], suponhamos que seja k.

          Denotemos a[c][d] como o valor do d-esimo bit do vetor c.

          Sabemos que a[i][k]= 1, vamos olhar para as possiveis combinacoes que temos para a[j][k].

          Para a[j][k] = 1, temos que (a[j]^a[i])[k] = 1^1 = 0, portanto a[i]^a[j] < a[j], ja que este eh
          o primeiro bit a poder ser mudado, e como temos que antes tinha-se 1, se tornou 0, ou seja, devemos fazer
          a operacao para que a[j] nao tenha o k-esimo bit valendo 1.

          Para a[j][k] = 0, temos que (a[j]^a[i])[k] = 0^1 = 1, portanto a[i]^a[j] > a[j], ja que este eh
          o primeiro bit a poder ser mudado, e como temos que antes tinha-se 0, se tornou 1, ou seja, nao ha necessidade
          de se fazer a operacao, pois o k-esimo bit ja vale 0 em a[j].

Como enumerar cada subespaco:

  Como sabemos que queremos apenas um elemento com cada bit mais significativo, podemos podar nossa arvore de combinacoes  bastante.

  originalmente teos 32*31*30*29*28 opcoes.

  Sabemos que para ser uma base, e ser da forma que representamos( de equivalencia), podemos pegar, cada elemento sera responsavel por seu bit
  mais significativo, entao para o passo de escolha do k elemento, podemos escolher apenas os elementos que tenham o k-esimo bit = 1(da esquerda pra 
  direita, para podermos fazer o processo de ir pelo maior para  o menor).

*/

//acho que a complexidade eh (2^n+1)*(2^(n-1)+1)*...*(4+1)*(2+1)(1+1), para n = 4, temos O(pre) = 2*3*5*9*17 < 5000 (rapidao)
inline void pre(int n,vi x)
{
    if(n==-1)
      {
       if(!h[x])
         {
          h[x]=++p;
          ::x[p]=x;
         }
       return;
      }
    vi y=x;
    pre(n-1,x);
    int i,j;
    for(i=(1<<n);i<(1<<n+1);i++)
      {
       x=y;
       x.pb(i);
       for(j=0;j<x.size()-1;j++)
         if(x[j]&(1<<n))
           x[j]^=i;
       pre(n-1,x);
      }
}

//custa n * n * log n (como n <= 5, da aprox 50~60 operacoes)
inline int get(vi x)
{
    if(x.size()>5)
      return 0;
    int i,j;
    for(i=0;i<x.size();i++)
      {
       sort(x.begin(),x.end(),cmp);
       for(j=0;j<x.size();j++)
          // i > j para remover o bit mais significato de i de x[j].
          // i < j para bits  com o mesmo bit significato
         if(i!=j)
           if(x[i]==x[j])
             return 0;
           else if( (x[i]^x[j])<x[j])
             x[j]^=x[i];
      }
    return h[x];
}

inline void dfs(int i,int j)
{
    int k;
    t[i]=r;
    for(k=0;k<a[i].size();k++)
      if(a[i][k]!=1 && a[i][k]!=j)
        if(!t[a[i][k]])
          {
           w[a[i][k]]=w[i]^b[i][k];
           dfs(a[i][k],i);
          }
        else if(i<a[i][k])
          y[r].pb(w[i]^w[a[i][k]]^b[i][k]);
}
inline int get(int i,int j)
{
    int k;
    for(k=0;k<a[i].size();k++)
      if(a[i][k]==j)
        return b[i][k];
    
    return -1;
}
inline bool cmp(int i,int j)
{
    return i>j;
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int i,j,k,l;
	pre(4,vi());
	//cerr<<p<<"\n";
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
	  {
       scanf("%d%d%d",&j,&k,&l);
       a[j].pb(k);
       b[j].pb(l);
       a[k].pb(j);
       b[k].pb(l);
      }
    for(i=0;i<a[1].size();i++)
      if(!t[a[1][i]])
        {
         r++;
         c[r]=a[1][i];
         d[r]=b[1][i];
         dfs(a[1][i],1);
         u[r]=get(y[r]);
         //cout<<r<<" "<<u[r]<<"\n";
        }
      else
        {
         k=t[a[1][i]];
         y[k].pb(d[k]^b[1][i]^get(a[1][i],c[k]));
         v[k]=get(y[k]);
         o[k]=1;
         //cout<<r<<" "<<v[r]<<"\n";
        }
    for(i=1;i<=p;i++)
      for(j=1;j<=p;j++)
        {
         vi a=x[i];
         for(auto k:x[j])
           a.pb(k);
         g[i][j]=get(a);
        }
    f[1][1]=1;
    for(i=1;i<=r;i++)
      for(j=1;j<=p;j++)
        if(f[i][j])
        {
         f[i+1][j]=(f[i+1][j]+f[i][j])%q;
         k=g[j][u[i]];
         if(!o[i])
           f[i+1][k]=(f[i+1][k]+f[i][j])%q;
         else
           {
            f[i+1][k]=(f[i+1][k]+2ll*f[i][j])%q;
            k=g[j][v[i]];
            f[i+1][k]=(f[i+1][k]+f[i][j])%q;
           }
        }
    for(i=1,k=0;i<=p;i++)
      k=(k+f[r+1][i])%q;
    printf("%d\n",k);
	return 0;
}