#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

struct spnt {
    ull x, y, b;
};

struct reg {
    ull mx, my, Mx, My;
};

typedef vector<spnt> vs;
typedef queue<reg> qr;

bool checkInside(spnt& sp, ull x, ull y) {
    ull dx = x > sp.x ? x - sp.x : sp.x - x;
    ull dy = y > sp.y ? y - sp.y : sp.y - y;
    return dx*dx*dx + dy*dy*dy <= sp.b;
}

ull outDiff3(ull b, ull e, ull v) {
    --e;
    ull r = 0;
    if(v < b) r = b - v;
    if(v > e) r = v - e;
    return r*r*r;
}

bool inside(ull b, ull e, ull v) {
    return b <= v && v < e;
}

int maxState(int pS, spnt& sp, reg& r) {
    if(pS >= 2) return pS;
    bool c1 = checkInside(sp, r.mx, r.my);
    bool c2 = checkInside(sp, r.mx, r.My - 1);
    bool c3 = checkInside(sp, r.Mx - 1, r.my);
    bool c4 = checkInside(sp, r.Mx - 1, r.My - 1);
    if(c1 && c2 && c3 && c4) return 2;
    if(pS) return pS;
    if(c1 || c2 || c3 || c4) return 1;
    if(inside(r.mx, r.Mx, sp.x) && outDiff3(r.my, r.My, sp.y) <= sp.b) return 1;
    if(inside(r.my, r.My, sp.y) && outDiff3(r.mx, r.Mx, sp.x) <= sp.b) return 1;
    return 0;
}

int main() {
    ull n, k;
    cin >> n >> k;
    vs ps(k);
    while(k --> 0) cin >> ps[k].x >> ps[k].y >> ps[k].b;
    k = ps.size();
    qr qt;
    reg r;
    r.mx = r.my = 0;
    r.Mx = r.My = n + 1;
    qt.push(r);
    ull cnt = 0;
    while(!qt.empty()) {
        r = qt.front();
        qt.pop();
        int s = 0;
        if(r.Mx - r.mx < 2 && r.My - r.my < 2) {
            bool isIn = r.Mx > r.mx && r.My > r.my;
            for(int i = 0; isIn && i < k; ++i)
                isIn = !checkInside(ps[i], r.mx, r.my);
            cnt += isIn;
        } else {
            for(spnt& sp : ps) s = maxState(s, sp, r);
            if(s == 0) cnt += (r.Mx - r.mx)*(r.My - r.my);
            if(s == 1) {
                ull xA, yA;
                reg q1, q2, q3, q4;
                xA = (r.mx + r.Mx)/2;
                yA = (r.my + r.My)/2;
                q1.mx = q3.mx = r.mx;
                q2.Mx = q4.Mx = r.Mx;
                q1.Mx = q2.mx = q3.Mx = q4.mx = xA;
                q1.my = q2.my = r.my;
                q3.My = q4.My = r.My;
                q1.My = q2.My = q3.my = q4.my = yA;
                qt.push(q1);
                qt.push(q2);
                qt.push(q3);
                qt.push(q4);
            }
        }
    }
    cout << cnt << endl;
}
