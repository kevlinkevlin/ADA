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
long long int S[MAX_N];
long long int N, K, A, B;

long long int cost[MAX_N] = {0};
long long int tmp = 0;
long long int find_DP = 0;
long long int ans = 0;
long long int DP[2][MAX_N] = {0};

long long int Pre_MAX[MAX_N] = {0};
long long int Origin_MAX[MAX_N] = {0};
long long int find_max = 0;

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
    scanf("%lld%lld%lld%lld", &N, &K, &A, &B);
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld", &S[i]);
        DP[1][i] = S[i];
        Origin_MAX[i] = max(S[i], Origin_MAX[i - 1]);
    }
    ans = Origin_MAX[N];
    cost[0] = max(0, A * B);
    cost[1] = max(0, A * (B - 1));
    for (int i = 2; i <= K; i++)
    {
        DP[i & 1][1] = DP[(i - 1) & 1][1];
        Pre_MAX[1] = DP[(i - 1) & 1][1] + cost[0];
        // Origin_MAX[1] = DP[(i - 1) & 1][1];
        // ans = max(DP[i & 1][1], ans);
        for (int j = 2; j <= N; j++)
        {

            //Origin_MAX[j-1],Pre_MAX[j-1] - cost,S[j-1] + cost
            find_max = max(Origin_MAX[j - 1], Pre_MAX[j - 1] - A);
            find_max = max(find_max, DP[(i - 1) & 1][j - 1] + cost[1]);
            Pre_MAX[j] = find_max;
            DP[i & 1][j] = S[j] + find_max;

            Origin_MAX[j - 1] = max(Origin_MAX[j - 2], DP[i & 1][j - 1]);
        }
        Origin_MAX[N] = max(Origin_MAX[N - 1], DP[i & 1][N]);
        ans = max(Origin_MAX[N], ans);
    }
    printf("%lld", ans);
    // system("pause");
    return 0;
}