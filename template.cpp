#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define pii pair <int, int>
#define X first
#define Y second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define info() cerr << __PRETTY_FUNCTION__ << ": " << __LINE__ << endl
#define test(args...) info(), kout("[" + string(#args) + "]", args)
void kout() {cerr << endl;}
template <typename T, class ...U>
void kout(vector <T> a, U ...b) {for (T i : a) cerr << i << ' '; kout(b...);}
template <class T, class ...U>
void kout(T a, U ...b) {cerr << a << ' ', kout(b...);}
template <class T>
void printv(T l, T r) {
    while (l != r) cout << *l << " \n"[++l == r];
}
template <typename A, typename B>
istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B>
ostream& operator << (ostream& o, pair<A, B> a) {
    return o << a.X << ' ' << a.Y;
}
const int mod = 1e9 + 7, abc = 864197532, Doludu = 123, N = 400001, K = 111;
