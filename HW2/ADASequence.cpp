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
#define MAX_N 201
#define MAX_S 601
long long int A[MAX_N] = {0}, C[MAX_N] = {0};
int S[MAX_N] = {0};
long long int N, K, D;

struct Table
{
    int value = 0;
    long long int cost = 0;
    bool index; //  !!?
    int pre_i = -10, pre_j = -10, pre_s = -10;
    int change_ind = 0;
    int change_value = 0;
};
Table table[MAX_N][MAX_N][MAX_S];
inline bool Compare(int i, int j)
{
    return (i < j);
} // order by x
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
    int Si_sum = 0;
    scanf("%lld%lld%lld", &N, &K, &D);
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld", &A[i]);
    }
    for (int i = 1; i <= N; i++)
    {
        scanf("%lld", &C[i]);
    }
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &S[i]);

        table[i][i][S[i]].value = S[i];
        Si_sum += S[i];
    }
    for (int s = 0; s <= Si_sum; s++)
    {
        for (int i = 1; i <= N; i++)
        {
            if (table[i][i][s].value == 0)
                table[i][i][s].cost = 100000000000;
        }
    }
    long long int left, down, bottom_left, pre_bottom_left;
    long long int find_min;
    for (int score = 0; score <= Si_sum; score++)
    {
        for (int i = 1; i < N; i++)
        {
            for (int j = 1; j < N - i + 1; j++)
            {
                left = 100000000000;
                down = 100000000000;
                bottom_left = 100000000000;
                pre_bottom_left = 100000000000;
                if (table[j][j + i - 1][score].value > 0)
                {
                    left = table[j][j + i - 1][score].cost;
                }
                if (table[j + 1][j + i][score].value > 0)
                {
                    down = table[j + 1][j + i][score].cost;
                }
                if (abs(A[j] - A[j + i]) <= D)
                {
                    if (score - S[j] - S[j + i] >= 0 && table[j + 1][j + i - 1][score - S[j] - S[j + i]].value > 0)
                    {
                        bottom_left = table[j + 1][j + i - 1][score - S[j] - S[j + i]].cost;
                    }
                }
                if (abs(A[j] - A[j + i]) > D)
                {
                    if (score - S[j] - S[j + i] >= 0 && table[j + 1][j + i - 1][score - S[j] - S[j + i]].value > 0)
                    {
                        if (C[j] <= C[j + i])
                        {
                            pre_bottom_left = table[j + 1][j + i - 1][score - S[j] - S[j + i]].cost + C[j];
                        }
                        else
                        {
                            pre_bottom_left = table[j + 1][j + i - 1][score - S[j] - S[j + i]].cost + C[j + i];
                        }
                    }
                }
                find_min = min(left, down);
                find_min = min(find_min, bottom_left);
                find_min = min(find_min, pre_bottom_left);

                table[j][j + i][score].cost = find_min;

                if (find_min == 100000000000)
                {
                    continue;
                }
                else if (find_min == bottom_left)
                {
                    table[j][j + i][score].value = score;
                    table[j][j + i][score].pre_i = j + 1;
                    table[j][j + i][score].pre_j = j + i - 1;
                    table[j][j + i][score].pre_s = score - S[j] - S[j + i];
                }
                else if (find_min == left)
                {
                    table[j][j + i][score].value = score;
                    table[j][j + i][score].pre_i = j;
                    table[j][j + i][score].pre_j = j + i - 1;
                    table[j][j + i][score].pre_s = score;
                }
                else if (find_min == down)
                {
                    table[j][j + i][score].value = score;
                    table[j][j + i][score].pre_i = j + 1;
                    table[j][j + i][score].pre_j = j + i;
                    table[j][j + i][score].pre_s = score;
                }
                else if (find_min == pre_bottom_left)
                {
                    table[j][j + i][score].value = score;
                    if (C[j] <= C[j + i])
                    {
                        table[j][j + i][score].change_ind = j;
                        table[j][j + i][score].change_value = A[j + i];
                    }
                    else
                    {
                        table[j][j + i][score].change_ind = j + i;
                        table[j][j + i][score].change_value = A[j];
                    }
                    table[j][j + i][score].pre_i = j + 1;
                    table[j][j + i][score].pre_j = j + i - 1;
                    table[j][j + i][score].pre_s = score - S[j] - S[j + i];
                }
            }
        }
    }
    for (int i = Si_sum; i >= 0; i--)
    {
        if (table[1][N][i].cost <= K && table[1][N][i].value > 0)
        {
            printf("%d\n", table[1][N][i].value);
            int tmpi, tmpj, tmps;
            int nowi = 1, nowj = N, nows = i;
            vector<pair<int, int>> change_point;
            vector<int> ans_ind;
            while (table[nowi][nowj][nows].pre_i != -10 && table[nowi][nowj][nows].pre_j != -10 && table[nowi][nowj][nows].pre_s != -10)
            {
                if (table[nowi][nowj][nows].change_ind != 0 && table[nowi][nowj][nows].change_value != 0)
                    change_point.emplace_back(make_pair(table[nowi][nowj][nows].change_ind, table[nowi][nowj][nows].change_value));
                tmpi = table[nowi][nowj][nows].pre_i;
                tmpj = table[nowi][nowj][nows].pre_j;
                tmps = table[nowi][nowj][nows].pre_s;
                if (tmpi == tmpj && tmpi > 0)
                {
                    ans_ind.emplace_back(tmpi);
                }
                if (tmpi - nowi == 1 && nowj - tmpj == 1)
                {
                    ans_ind.emplace_back(nowi);
                    ans_ind.emplace_back(nowj);
                }
                nowi = tmpi;
                nowj = tmpj;
                nows = tmps;
            }
            printf("%d\n", change_point.size());
            for (vector<pair<int, int>>::iterator trace = change_point.begin(); trace != change_point.end(); trace++)
                printf("%d %d\n", trace->first, trace->second);
            sort(ans_ind.begin(), ans_ind.end(), Compare);
            printf("%d\n", ans_ind.size());
            for (vector<int>::iterator ind = ans_ind.begin(); ind != ans_ind.end(); ind++)
                printf("%d ", *ind);
            break;
        }
    }

    system("pause");
}