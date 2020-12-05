#include <stdio.h>
// #include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>

#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

using namespace std;

struct Point
{
    int x, y;
};

unsigned long long mindist = LLONG_MAX;
float sqrt_mindist = __FLT_MAX__;

inline bool CompareX(Point p1, Point p2)
{
    return (p1.x < p2.x);
} // order by x

inline bool CompareY(Point p1, Point p2)
{
    return (p1.y < p2.y);
} //order by y

inline unsigned long long dist(Point &p1, Point &p2)
{
    return (unsigned long long)(p1.x - p2.x) * (p1.x - p2.x) +
           (unsigned long long)(p1.y - p2.y) * (p1.y - p2.y);
}

inline void decideminimun(Point &p1, Point &p2)
{

    unsigned long long Tmp_d = dist(p1, p2);
    if (Tmp_d < mindist)
        mindist = Tmp_d;
    sqrt_mindist = sqrtf(mindist);
    return;
}

inline void findmin(vector<Point> P, int n)
{
    // n <=3  ==> max loop time: three
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            decideminimun(P[i], P[j]);
    return;
}

void merge(vector<Point> P_l, vector<Point> P_r) //both vector are increasing sequence by y
{
    vector<Point>::iterator it_tmp = P_r.begin();
    for (vector<Point>::iterator it_l = P_l.begin(); it_l != P_l.end(); ++it_l)
    {
        Point left = *it_l;
        for (vector<Point>::iterator it_r = it_tmp; it_r != P_r.end(); ++it_r)
        {
            Point right = *it_r;
            if ((right.y - left.y) > sqrt_mindist)
                break;
            else if ((left.y - right.y) > sqrt_mindist)
            {
                it_tmp = it_r;
                continue;
            }
            else
            {
                decideminimun(left, right);
            }
        }
    }

    return;
}

void divide(vector<Point> Px, vector<Point> Py, int n)
{
    if (n <= 87)
        return findmin(Py, n);

    int mid = n & 1 == 0 ? n >> 1 - 1 : n >> 1;
    Point midPoint = Px[mid];
    mid++;
    vector<Point> Py_l, Py_r;
    Py_l.reserve(mid);
    Py_r.reserve(mid);

    // int l_size=0;
    // for (vector<Point >::iterator it=Px.begin(); it!=Px.end(); ++it){
    //     Point myp = *it; //O(n/2)
    //     if (myp.x < midPoint.x)
    //         	l_size++;
    //     else
    //     	break;
    // }
    // int mid_n = mid-l_size; // the # of point (x equal to midPoint.x ) can put in left vector

    int mid_n = 1;
    for (vector<Point>::iterator it = Px.begin() + mid - 1; it != Px.begin(); --it)
    {
        Point myp = *it; //O(n/2)
        if (myp.x == midPoint.x)
            mid_n++;
        else
            break;
    }

    for (vector<Point>::iterator it = Py.begin(); it != Py.end(); ++it)
    {
        Point myp = *it; //O(n)
        if (myp.x < midPoint.x)
            Py_l.emplace_back(myp);
        else if (myp.x > midPoint.x)
            Py_r.emplace_back(myp);
        else
        {
            if (mid_n > 0)
            {
                Py_l.emplace_back(myp);
                mid_n -= 1;
            }
            else
                Py_r.emplace_back(myp);
        }
    }

    divide(vector<Point>(Px.begin(), Px.begin() + mid), Py_l, mid);
    divide(vector<Point>(Px.begin() + mid, Px.end()), Py_r, n - mid);

    vector<Point> middle_l, middle_r;
    middle_l.reserve(mid);
    middle_r.reserve(n - mid);
    //O(n)

    for (vector<Point>::iterator it = Py_l.begin(); it != Py_l.end(); ++it)
    {
        Point myp = *it;
        if (midPoint.x - myp.x < sqrt_mindist)
            middle_l.emplace_back(myp);
    }
    for (vector<Point>::iterator it = Py_r.begin(); it != Py_r.end(); ++it)
    {
        Point myp = *it;
        if (myp.x - midPoint.x < sqrt_mindist)
            middle_r.emplace_back(myp);
    }

    merge(middle_l, middle_r);
    return;
}

int main()
{
    int n;
    scanf("%d", &n);
    Point myP;
    vector<Point> myvec_x, myvec_y;
    myvec_x.reserve(n);
    myvec_y.reserve(n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d %d", &myP.x, &myP.y);
        myvec_x.emplace_back(myP);
    }

    sort(myvec_x.begin(), myvec_x.end(), CompareX);
    myvec_y.assign(myvec_x.begin(), myvec_x.end());
    sort(myvec_y.begin(), myvec_y.end(), CompareY);
    divide(myvec_x, myvec_y, n);
    printf("%lld", ~mindist + 1);
    // system("pause");
}