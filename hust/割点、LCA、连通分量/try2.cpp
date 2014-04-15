#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>

using namespace std;

#define lc x << 1
#define rc (lc) + 1

const int MAXN = 33333, MAXB = 11111111;

bool v[MAXN];
char buf[MAXB], *it = buf;
int n, tot, cnt, q[MAXN], x[MAXN], y[MAXN], d[MAXN << 2], s[MAXN << 2], hd[MAXN], pre[MAXN], suc[MAXN], sz[MAXN], idx[MAXN], dep[MAXN], h[MAXN], p[MAXN << 1], nxt[MAXN << 1];

inline void addedge(int a, int b) {
    p[++tot] = b;
    nxt[tot] = h[a];
    h[a] = tot;
}

inline void update(int x) {
    d[x] = max(d[lc], d[rc]);
    s[x] = s[lc] + s[rc];
}

void build(int x, int f, int t) {
    if (f == t) {
        d[x] = s[x] = y[f];
        return;
    }
    int mid = f + t >> 1;
    build(lc, f, mid);
    build(rc, mid + 1, t);
    update(x);
}

void modify(int x, int f, int t, int u, int v) {
    if (f == t) {
        d[x] = s[x] = v;
        return;
    }
    int mid = f + t >> 1;
    if (u <= mid)
        modify(lc, f, mid, u, v);
    else
        modify(rc, mid + 1, t, u, v);
    update(x);
}

int qmax(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt)
        return d[x];
    int mid = f + t >> 1, a = INT_MIN, b = INT_MIN;
    if (qf <= mid)
        a = qmax(lc, f, mid, qf, qt);
    if (qt > mid)
        b = qmax(rc, mid + 1, t, qf, qt);
    return max(a, b);
}

int qsum(int x, int f, int t, int qf, int qt) {
    if (qf <= f && t <= qt)
        return s[x];
    int mid = f + t >> 1, a = 0, b = 0;
    if (qf <= mid)
        a = qsum(lc, f, mid, qf, qt);
    if (qt > mid)
        b = qsum(rc, mid + 1, t, qf, qt);
    return a + b;
}

inline int getmax(int a, int b) {
    int ret = INT_MIN;
    while (hd[a] != hd[b]) {
        if (dep[hd[a]] < dep[hd[b]])
            swap(a, b);
        ret = max(ret, qmax(1, 1, n, idx[hd[a]], idx[a]));
        a = pre[hd[a]];
    }
    if (idx[a] < idx[b])
        swap(a, b);
    ret = max(ret, qmax(1, 1, n, idx[b], idx[a]));
    return ret;
}

inline int getsum(int a, int b) {
    int ret = 0;
    while (hd[a] != hd[b]) {
        if (dep[hd[a]] < dep[hd[b]])
            swap(a, b);
        ret += qsum(1, 1, n, idx[hd[a]], idx[a]);
        a = pre[hd[a]];
    }
    if (idx[a] < idx[b])
        swap(a, b);
    ret += qsum(1, 1, n, idx[b], idx[a]);
    return ret;
}

inline void getint(int &x) {
    for (; !isdigit(*it) && *it != '-'; ++it);
    int p = *it == '-' ? -1 : 1;
    for ((x = *it == '-' ? 0 : *it - 48), ++it; isdigit(*it); (x *= 10) += *it++ - 48);
    x *= p;
}

int main() {
    fread(buf, 1, MAXB - 10, stdin);
    getint(n);
    for (int i = 1; i < n; ++i) {
        int a, b;
        getint(a);
        getint(b);
        addedge(a, b);
        addedge(b, a);
    }
    for (int i = 1; i <= n; ++i)
        getint(x[i]);
    int r = 0;
    v[dep[1] = q[0] = 1] = true;
    for (int l = 0; l <= r; ++l)
        for (int k = h[q[l]]; k; k = nxt[k])
            if (!v[p[k]]) {
                v[p[k]] = true;
                dep[q[++r] = p[k]] = dep[q[l]] + 1;
                pre[q[r]] = q[l];
            }
    for (int i = r; i >= 0; --i) {
        sz[pre[q[i]]] += ++sz[q[i]];
        if (sz[q[i]] > sz[suc[pre[q[i]]]])
            suc[pre[q[i]]] = q[i];
    }
    for (int i = 0; i <= r; ++i)
        if (!hd[q[i]])
            for (int k = q[i]; k; k = suc[k]) {
                hd[k] = q[i];
                y[idx[k] = ++cnt] = x[k];
            }
    build(1, 1, n);
    int m;
    getint(m);
    while (m--) {
        while (!isalpha(*it++));
        char op = *it++;
        int a, b;
        getint(a);
        getint(b);
        if (op == 'H')
            modify(1, 1, n, idx[a], b);
        else
            printf("%d\n", op == 'M' ? getmax(a, b) : getsum(a, b));
    }
    return 0;
}
