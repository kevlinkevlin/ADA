#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <limits.h>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;

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
#define MAX_N 100001
#define MAX_OUTPUT_SIZE 10000000
long long int N;
long long int C[MAX_N] = {0};
vector<int> ans;
int flag;
struct left_and_right
{
    long long int left = 0;
    long long int right = 0;
};
left_and_right Sum[MAX_N] = {0};

long long int max(long long int a, long long int b)
{
    return a > b ? a : b;
}
long long int min(long long int a, long long int b)
{
    return a < b ? a : b;
}

int main()
{

    scanf("%lld", &N);
    long long int Max_val = 0;
    int Max_ind = 0;
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld", &C[i]);
        if (C[i] > Max_val)
        {
            Max_val = C[i];
            Max_ind = i;
        }
        Sum[i].left = Sum[i - 1].left + C[i - 1];
    }
    scanf("%d", &flag);
    long long int All_sum = Sum[N].left + C[N];
    ans.reserve(MAX_OUTPUT_SIZE);
    Sum[Max_ind].right = All_sum - C[Max_ind] - Sum[Max_ind].left;

    int pivot = Max_ind;
    long long int left = Sum[pivot].left;
    long long int right = Sum[pivot].right;
    while (true)
    {
        C[pivot]--;
        ans.emplace_back(pivot);
        if (left > 0 && left <= right)
        {
            if (C[pivot] > 0)
                right += C[pivot];
            pivot--;
            if (C[pivot] > 0)
                left -= C[pivot];
        }
        else if (right > 0 && right <= left)
        {
            if (C[pivot] > 0)
                left += C[pivot];
            pivot++;
            if (C[pivot] > 0)
                right -= C[pivot];
        }
        else if (left > 0)
        {
            if (C[pivot] > 0)
                right += C[pivot];
            pivot--;
            if (C[pivot] > 0)
                left -= C[pivot];
        }
        else if (right > 0)
        {
            if (C[pivot] > 0)
                left += C[pivot];
            pivot++;
            if (C[pivot] > 0)
                right -= C[pivot];
        }
        else if (C[pivot] > 0)
        {
            if (pivot > 1)
            {
                right += C[pivot];
                pivot--;
            }
            else if (pivot < N)
            {
                left += C[pivot];
                pivot++;
            }
        }
        else
        {
            break;
        }
    }
    printf("%d\n", ans.size() - All_sum);

    if (flag)
    {
        for (vector<int>::iterator it = ans.begin(); it != ans.end(); it++)
        {
            printf("%d ", *it);
        }
    }

    system("pause");
    return 0;
}