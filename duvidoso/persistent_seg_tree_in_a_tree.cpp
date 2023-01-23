/*Esse problema tambem tem uma questao de probabilidade envolvida
porque neste caso, a gente pode ter o problema se tipo a gente tiver um 1,2 e 3
na seg,porque ao subir a seguir esses valores vao se cancelando no XOR
ate da 0, pra isso nao ocorrer o cara faz x virar um valor randomico entre
[0 e 2^64-1] o que faz a query tem probabilidade de sucesso de 
1 - 2^(-64) (nao se iporque, o editorial nao se importou em explicar).
*/


/*
Aplicasse a estruta persistente atualizando o no pai ao analisado
com o valor correspondente ao filho,


Cada no tem um valor x atribuido a ele.

Serve para fazer query sobre o path (u,v), que tem algo relacionado ao
uso de uma segtree.

Neste problema a query eh da forma (u,v,l,r), onde se quer saber se existe
um elemento que aparece numero par de vezes no array, utilizando assim
uma PST de XOR (com algo probabilistico, mas nao entendi ao certo) 
para responder tal quere, olhando quatro seg diferentes:

1 - A Seg que representa os valores do Root ao U.
2 - A Seg que representa os valores do Root ao V.
3 - A Seg que representa os valores do Root ao LCA(U,V).
4 - A Seg que representa os valores do Root ao par(LCA(U,V)).
        onde par(i) eh o pai de i, considera a seg pai do root a seg vazia(todos
        os elementos 0).

Para isto utiliza a query --> seg(1,l,r)^seg(2,l,r)^seg(3,l,r)^seg(4,l,r), 
pois desta forma cada elemento do path (u,v) sera considerado um numero impar de vezes,
enquanto os outros elementos nao.

-----

Se a pergunta fosse em uma seg de Soma:
query -->  seg(1,l,r) + seg(1,l,r) - seg(3,l,r) - seg(4,l,r)

Se a pergunta fosse uma seg de min/max:
--- nao sei se eh possivel

Se a pergunta for o max/min no path entre u,v:

Praticamente funciona como a da soma:
query -->  seg(1,l,r) + seg(1,l,r) - seg(3,l,r) - seg(4,l,r)
mais indo sempre pra direita quando possivel, assim achar o maior,
e para a direita, assim acha o menor.

    Problema neste estilo, so que achando o k-esimo menor:
        https://www.spoj.com/problems/COT/

*/
//problem:: https://codeforces.com/contest/1479/problem/D
#include <bits/stdc++.h>
 
using namespace std;
 
const int MAXN = 300010;
const int MAXK = 20;
 
mt19937_64 rd(chrono::steady_clock::now().time_since_epoch().count());
 
int n, q;
int a[MAXN];
uint64_t h[MAXN];
vector<int> v[MAXN];
int pre[MAXN][MAXK];
int dis[MAXN];
 
struct node
{
	node* Lc, * Rc;
	uint64_t val;
	node()
	{
		Lc = Rc = nullptr;
		val = 0;
	}
	void update()
	{
		this->val = this->Lc->val ^ this->Rc->val;
	}
};
 
int tot;
node nodes[MAXN * 22];
node* root[MAXN];
 
node* new_node()
{
	node* it = &nodes[++tot];
	return it;
}
 
node* build(int L, int R)
{
	node* it = new_node();
	if (L < R)
	{
		int m = (L + R) / 2;
		it->Lc = build(L, m);
		it->Rc = build(m + 1, R);
		it->update();
	}
	return it;
}
 
node* modify(node* p, int L, int R, int x)
{
	node* it = new_node();
	*it = *p;
	if (L == R)
	{
		it->val ^= h[x];
		return it;
	}
	int m = (L + R) / 2;
	if (x <= m)
		it->Lc = modify(p->Lc, L, m, x);
	else if (x > m)
		it->Rc = modify(p->Rc, m + 1, R, x);
	it->update();
	return it;
}
 
void dfs(int x)
{
	dis[x] = dis[pre[x][0]] + 1;
	root[x] = modify(root[pre[x][0]], 1, n, a[x]);
	for (auto y : v[x])
	{
		if (y == pre[x][0]) continue;
		pre[y][0] = x;
		dfs(y);
	}
}
 
int getlca(int x, int y)
{
	if (dis[x] < dis[y]) swap(x, y);
	for (int k = MAXK - 1; k >= 0; --k)
		if (dis[x] - dis[y] >= 1 << k)
			x = pre[x][k];
	if (x == y) return x;
	for (int k = MAXK - 1; k >= 0; --k)
		if (pre[x][k] != pre[y][k])
		{
			x = pre[x][k];
			y = pre[y][k];
		}
	return pre[x][0];
}
 
int calc(node* a, node* b, node* c, node* d, int L, int R)
{
	if (L == R) return L;
	int m = (L + R) / 2;
	if (a->Lc->val ^ b->Lc->val ^ c->Lc->val ^ d->Lc->val)
		return calc(a->Lc, b->Lc, c->Lc, d->Lc, L, m);
	else
		return calc(a->Rc, b->Rc, c->Rc, d->Rc, m + 1, R);
}
 
int query(node* a, node* b, node* c, node* d, int L, int R, int x, int y)
{
	if (L == x && R == y)
	{
		if (a->val ^ b->val ^ c->val ^ d->val)
			return calc(a, b, c, d, L, R);
		else
			return -1;
	}
	int m = (L + R) / 2;
	if (y <= m)
		return query(a->Lc, b->Lc, c->Lc, d->Lc, L, m, x, y);
	if (x > m)
		return query(a->Rc, b->Rc, c->Rc, d->Rc, m + 1, R, x, y);
	int tmp = query(a->Lc, b->Lc, c->Lc, d->Lc, L, m, x, m);
	if (tmp != -1) return tmp;
	return query(a->Rc, b->Rc, c->Rc, d->Rc, m + 1, R, m + 1, y);
}
 
int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (int i = 1; i <= n; ++i) h[i] = rd();
	for (int i = 1; i < n; ++i)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	root[0] = build(1, n);
 
	dfs(1);
	for (int k = 1; k < MAXK; ++k)
		for (int i = 1; i <= n; ++i)
			pre[i][k] = pre[pre[i][k - 1]][k - 1];
 
	while (q--)
	{
		int x, y, l, r;
		scanf("%d%d%d%d", &x, &y, &l, &r);
		int z = getlca(x, y);
		int res = query(root[x], root[y], root[z], root[pre[z][0]], 1, n, l, r);
		printf("%d\n", res);
	}
 
	return 0;
}