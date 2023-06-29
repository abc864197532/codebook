int sign(ll x) {return abs(x) == 0 ? 0 : (x > 0 ? 1 : -1);}
struct Pt {
  ll x, y;
  Pt (ll _x, ll _y) : x(_x), y(_y) {}
  Pt operator + (Pt o) {return Pt(x + o.x, y + o.y);}
  Pt operator - (Pt o) {return Pt(x - o.x, y - o.y);}
  Pt operator * (ll k) {return Pt(x * k, y * k);}
  Pt operator / (ll k) {return Pt (x / k, y / k);}
  ll operator * (Pt o) {return x * o.x + y * o.y;}
  ll operator ^ (Pt o) {return x * o.y - y * o.x;}
};
struct Line {
  Pt a, b;
};
struct Cir {
  Pt o; ll r;
};
ll abs2(Pt o) {return o.x * o.x + o.y * o.y;}
double abs(Pt o) {return sqrt(abs2(o));}
int ori(Pt o, Pt a, Pt b) {return sign((o - a) ^ (o - b));}
bool btw(Pt a, Pt b, Pt c) { // c on segment ab?
  return ori(a, b, c) == 0 && sign((c - a) * (c - b)) <= 0;
}
double area(Pt a, Pt b, Pt c) {return abs((a - b) ^ (a - c)) / 2;}
Pt unit(Pt o) {return o / abs(o);}
Pt rot(Pt a, double o) { // CCW
  double c = cos(o), s = sin(o);
  return Pt(c * a.x - s * a.y, s * a.x + c * a.y);
}
Pt proj_vector(Pt a, Pt b, Pt c) { // vector ac proj to ab
  return (b - a) * ((c - a) * (b - a)) / ((b - a) * (b - a));
}
Pt proj_pt(Pt a, Pt b, Pt c) { // point c proj to ab
  return proj_vector(a, b, c) + a;
}