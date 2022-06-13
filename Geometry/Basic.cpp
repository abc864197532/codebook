struct Pt {
    long long x, y;
    Pt (long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
    long long operator * (const Pt &o) {
        return x * o.x + y * o.y;
    }
    long long operator ^ (const Pt &o) {
        return x * o.y - y * o.x;
    }
    Pt operator + (const Pt &o) {
        return Pt(x + o.x, y + o.y);
    }
    Pt operator - (const Pt &o) {
        return Pt(x - o.x, y - o.y);
    }
    bool pos() {
        return (y == 0 ? x < 0 : y < 0);
    }
    long long dis() {
        return x * x + y * y;
    }
};

bool btw(Pt a, Pt b, Pt c) {
    // c in segment ab?
    return ((a - b) ^ (a - c)) == 0 && ((c - a) * (c - b)) <= 0;
}

long long area(Pt a, Pt b, Pt c) {
    return abs((a - b) ^ (a - c));
}

double dis(Pt a, Pt b, Pt c) {
    return double(area(a, b, c)) / sqrt((b - c).dis());
}