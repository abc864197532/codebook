void PolarAngleSort(vector <Pt> &pt) {
    sort(pt.begin(), pt.end(), [&](Pt a, Pt b) {
        return (a.pos() == b.pos() ? (a ^ b) > 0 : a.pos() < b.pos());
    });
}