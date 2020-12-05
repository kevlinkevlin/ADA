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
#define MAX_N 500000
int count_rmd;
long long int max_r[MAX_N];
long long int min_r[MAX_N];
long long int max_l[MAX_N];
long long int min_l[MAX_N];
long long int a[MAX_N];
int counter[MAX_N];
vector<int> check_is_calculate;
long long int prefix_sum[MAX_N];

long long int answer = 0;
long long int max(long long int a, long long int b)
{
    return a > b ? a : b;
}
long long int min(long long int a, long long int b)
{
    return a < b ? a : b;
}

void good_pairs(int L, int R, long long int *a, long long int *prefix_sum, int k, int N)
{

    if (R - L < 300)
    {
        long long int maximum, minimum, sum;
        for (int i = L; i < R; i++)
        {
            maximum = a[i];
            minimum = a[i];
            for (int j = i + 1; j <= R; j++)
            {

                maximum = max(a[j], maximum);
                minimum = min(a[j], minimum);
                sum = i > 0 ? prefix_sum[j] - prefix_sum[i - 1] : prefix_sum[j];

                if ((sum - maximum - minimum) % k == 0)
                {
                    answer += 1;
                }
            }
        }
        return;
    }

    int length = R - L + 1;
    int mid = (L + R) / 2;
    good_pairs(L, mid, a, prefix_sum, k, N);
    good_pairs(mid + 1, R, a, prefix_sum, k, N);
    // left half: L ~ mid
    // right half: mid + 1 ~ R

    max_r[mid + 1] = a[mid + 1];
    min_r[mid + 1] = a[mid + 1];
    for (int i = mid + 2; i <= R; i++)
    {
        max_r[i] = max(a[i], max_r[i - 1]);
        min_r[i] = min(a[i], min_r[i - 1]);
    }
    max_l[mid] = a[mid];
    min_l[mid] = a[mid];
    for (int i = mid - 1; i >= L; i--)
    {
        max_l[i] = max(a[i], max_l[i + 1]);
        min_l[i] = min(a[i], min_l[i + 1]);
    }

    int ptr_l;
    int ptr_r;

    // (max, min) = (left, left)
    check_is_calculate.clear();

    ptr_r = mid;
    for (int i = mid; i >= L; i--)
    {
        while ((ptr_r + 1 <= R) && (min_l[i] <= min_r[ptr_r + 1]) && (max_l[i] >= max_r[ptr_r + 1]))
        {
            // (i, ptr_r + 1) is a pair of this case
            count_rmd = (prefix_sum[ptr_r + 1] % k);
            counter[count_rmd]++;
            ptr_r++;
            check_is_calculate.push_back(count_rmd);
        }

        answer += i > 0 ? counter[((prefix_sum[i - 1] % k + min_l[i] % k + max_l[i] % k) % k)]
                        : counter[((min_l[i] % k + max_l[i] % k) % k)];
    }

    // (max, min) = (right, right)
    for (vector<int>::iterator it = check_is_calculate.begin(); it != check_is_calculate.end(); ++it)
        counter[*it] = 0;
    check_is_calculate.clear();

    ptr_l = mid + 1;
    for (int i = mid + 1; i <= R; i++)
    {
        while ((ptr_l - 1 >= L) && (min_r[i] < min_l[ptr_l - 1]) && (max_r[i] > max_l[ptr_l - 1]))
        {
            // (ptr_l - 1, i) is a pair of this case
            if (ptr_l - 1 != 0)
            {
                count_rmd = (prefix_sum[ptr_l - 2] % k);
                counter[count_rmd]++;
                check_is_calculate.push_back(count_rmd);
            }
            else
            {
                counter[0]++;
                check_is_calculate.push_back(0);
            }
            ptr_l--;
        }
        //printf("ans is incremented by counter[%d] = %lld \n", (((prefix_sum[i] - min_r[i] - max_r[i]) % k) + k) % k, counter[(((prefix_sum[i] - min_r[i] - max_r[i]) % k) + k) % k]);
        answer += counter[(((prefix_sum[i] % k - min_r[i] % k - max_r[i] % k) % k) + k) % k];
    }

    int max_ptr, min_ptr;

    // (max, min) = (left, right)
    for (vector<int>::iterator it = check_is_calculate.begin(); it != check_is_calculate.end(); ++it)
        counter[*it] = 0;
    check_is_calculate.clear();
    max_ptr = mid;
    min_ptr = mid + 1;
    for (int i = mid; i >= L; i--)
    {

        // min_ptr
        while ((min_ptr != R + 1) && (min_l[i] <= min_r[min_ptr]))
        {
            // not satisfied
            if (min_ptr <= max_ptr)
            {
                count_rmd = (((prefix_sum[min_ptr] % k - min_r[min_ptr] % k) % k) + k) % k;
                counter[count_rmd]--;
                check_is_calculate.push_back(count_rmd);
            }
            min_ptr++;
        }

        // max_ptr
        while ((max_ptr != R) && (max_l[i] >= max_r[max_ptr + 1]))
        {
            // satisfied
            max_ptr++;
            if (min_ptr <= max_ptr)
            {
                count_rmd = (((prefix_sum[max_ptr] % k - min_r[max_ptr] % k) % k) + k) % k;
                counter[count_rmd]++;
                check_is_calculate.push_back(count_rmd);
            }
        }
        answer += i > 0 ? counter[((prefix_sum[i - 1] % k + max_l[i] % k) % k)]
                        : counter[(max_l[i] % k)];
    }

    // (max, min) = (right, left)

    for (vector<int>::iterator it = check_is_calculate.begin(); it != check_is_calculate.end(); ++it)
        counter[*it] = 0;
    check_is_calculate.clear();
    max_ptr = mid + 1;
    min_ptr = mid;
    for (int i = mid; i >= L; i--)
    {
        // max_ptr
        while ((max_ptr != R + 1) && (max_l[i] >= max_r[max_ptr]))
        {
            // not satisfied
            if (max_ptr <= min_ptr)
            {
                count_rmd = (((prefix_sum[max_ptr] % k - max_r[max_ptr] % k) % k) + k) % k;
                counter[count_rmd]--;
                check_is_calculate.push_back(count_rmd);
            }
            max_ptr++;
        }

        // min_ptr
        while ((min_ptr != R) && (min_l[i] <= min_r[min_ptr + 1]))
        {
            // satisfied
            min_ptr++;
            if (max_ptr <= min_ptr)
            {
                count_rmd = (((prefix_sum[min_ptr] % k - max_r[min_ptr] % k) % k) + k) % k;
                counter[count_rmd]++;
                check_is_calculate.push_back(count_rmd);
            }
        }
        answer += i > 0 ? counter[((prefix_sum[i - 1] % k + min_l[i] % k) % k)]
                        : counter[(min_l[i] % k)];
    }
    for (vector<int>::iterator it = check_is_calculate.begin(); it != check_is_calculate.end(); ++it)
        counter[*it] = 0;
    check_is_calculate.clear();
    return;
}

int main()
{
    int N, k;
    scanf("%d%d", &N, &k);
    long long int tmp = 0;
    for (int i = 0; i < N; i++)
    {
        scanf("%lld", &a[i]);
        prefix_sum[i] = a[i] + tmp;
        tmp = prefix_sum[i];
    }
    check_is_calculate.reserve(MAX_N);
    good_pairs(0, N - 1, a, prefix_sum, k, N);

    printf("%lld", answer);

    // system("pause");
    return 0;
}