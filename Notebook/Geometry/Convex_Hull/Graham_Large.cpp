vpt hull(vpt& pts) {
	if(pts.size() < 4) return vpt(pts);
	pnt pvt = pts[0];
	for(pnt pt : pts) if(cartCmp(pt, pvt)) pvt = pt;
	for(pnt& pt : pts) pt = pt - pvt;
	sort(pts.begin(), pts.end(), cnvaCmp);
	for(pnt& pt : pts) pt = pt + pvt;
    vpt h;
	for(pnt pt : pts) {
		while(h.size() > 1 && cross(pt - BCK(h, 1), BCK(h, 1) - BCK(h, 2)) >= 0) h.pop_back();
		h.push_back(pt);
	}
	return h;
}
