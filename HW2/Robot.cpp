#include <stdio.h>
// #include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>
#include <string>
#pragma GCC optimize(3)

using namespace std;

struct Point
{
    int pre_dim, pre_x, pre_y;
    long long int sweet;
};
struct MaxPoint
{
    int x, y;
    long long int sweet;
};
struct Robot
{
    bool is_jump;
    int x, y, dim;
};

void buildDP(vector<vector<vector<Point>>> &D, int dim, int n, int m, vector<MaxPoint> &Max_point)
{
    long long int max;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            max = LLONG_MIN;
            if (i > 0)
            {
                // look up
                if (max <= D[dim][i - 1][j].sweet)
                {
                    max = D[dim][i - 1][j].sweet;
                    D[dim][i][j].pre_x = i - 1;
                    D[dim][i][j].pre_y = j;
                    D[dim][i][j].pre_dim = dim;
                }
            }

            if (j > 0)
            {
                // look left
                if (max <= D[dim][i][j - 1].sweet)
                {
                    max = D[dim][i][j - 1].sweet;
                    D[dim][i][j].pre_x = i;
                    D[dim][i][j].pre_y = j - 1;
                    D[dim][i][j].pre_dim = dim;
                }
            }

            if (dim > 0)
            {
                // look last dim
                if (max <= Max_point[dim - 1].sweet)
                {
                    max = Max_point[dim - 1].sweet;
                    D[dim][i][j].pre_x = Max_point[dim - 1].x;
                    D[dim][i][j].pre_y = Max_point[dim - 1].y;
                    D[dim][i][j].pre_dim = dim - 1;
                }
            }
            if (dim + i + j == 0)
            {
                D[dim][i][j].pre_x = 0;
                D[dim][i][j].pre_y = 0;
                D[dim][i][j].pre_dim = -1;
                continue;
            }
            D[dim][i][j].sweet += max;
            if (D[dim][i][j].sweet >= Max_point[dim].sweet)
            {
                Max_point[dim].x = i;
                Max_point[dim].y = j;
                Max_point[dim].sweet = D[dim][i][j].sweet;
            }
        }
    }
}

int main()
{

    int n, m, k;
    long long int c;
    scanf("%d %d %d %lld", &n, &m, &k, &c);
    vector<vector<vector<Point>>> D(k + 1, vector<vector<Point>>(n, vector<Point>(m)));
    vector<MaxPoint> Max_point(k + 1);
    for (int i = 0; i <= k; i++)
    {
        Max_point[i].sweet = LLONG_MIN;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%lld", &D[0][i][j].sweet);
            for (int dim = 1; dim < k + 1; dim++)
            {
                D[dim][i][j].sweet = D[dim - 1][i][j].sweet - c;
            }
        }
    }
    long long int answer;
    int jump_count = 0;
    if (n * m == 1)
    {
        answer = D[0][0][0].sweet;
        for (int i = 1; i <= k; i++)
        {
            if (D[i][0][0].sweet > 0)
            {
                answer += D[i][0][0].sweet;
                jump_count++;
            }
        }
        printf("%lld\n%d", answer, jump_count);
        for (int i = 0; i < jump_count; i++)
        {
            printf("\nJump 0 0");
        }
        return 0;
    }
    for (int dim = 0; dim < k + 1; dim++)
    {
        buildDP(D, dim, n, m, Max_point);
    }
    /*     for(int d = 0 ; d <= k ; d++){
        printf("max in dim %d is %d, in (%d,%d)\n", d, Max_point[d].sweet, Max_point[d].x, Max_point[d].y);
        printf("D[%d][n-1][m-1]=%d\n", d, D[d][n-1][m-1].sweet);
    } 

 for (int dim = 0;dim < k + 1;dim++)
{
    printf("\n");
    printf("dim = %d\n",dim);
    for (int i = 0;i < n;i++)
    {
        for (int j = 0;j < m;j++)
        {
            printf("(%d,%d,%d)|",D[dim][i][j].pre_dim,D[dim][i][j].pre_x,D[dim][i][j].pre_y);
        }
        printf("\n");
    }
    printf("\n");
}  */

    long long int findmax = 0, finddim = 0;
    findmax = D[finddim][n - 1][m - 1].sweet;
    for (int dim = 1; dim < k + 1; dim++)
    {
        if (findmax < D[dim][n - 1][m - 1].sweet)
        {
            finddim = dim;
            findmax = D[finddim][n - 1][m - 1].sweet;
        }
    }
    printf("%lld\n", findmax);
    vector<Robot> ans;
    Robot root;
    int nowx = n - 1;
    int nowy = m - 1;
    int predim = D[finddim][nowx][nowy].pre_dim;
    if (predim != finddim)
    {
        root.is_jump = true;
    }
    else
    {
        root.is_jump = false;
    }
    root.x = nowx;
    root.y = nowy;
    ans.emplace_back(root);
    nowx = D[finddim][root.x][root.y].pre_x;
    nowy = D[finddim][root.x][root.y].pre_y;

    while (nowx + nowy + predim != 0)
    {
        root.x = nowx;
        root.y = nowy;
        root.dim = predim;

        nowx = D[root.dim][root.x][root.y].pre_x;
        nowy = D[root.dim][root.x][root.y].pre_y;
        predim = D[root.dim][root.x][root.y].pre_dim;
        if (predim != root.dim)
        {
            root.is_jump = true;
        }
        else
        {
            root.is_jump = false;
        }
        ans.emplace_back(root);
    }
    printf("%d", ans.size());
    for (int i = ans.size() - 1; i >= 0; i--)
    {
        if (ans[i].is_jump)
        {
            printf("\nJump %d %d", ans[i].x, ans[i].y);
        }
        else
        {
            printf("\nMove %d %d", ans[i].x, ans[i].y);
        }
    }
}