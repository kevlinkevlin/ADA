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
#define MAX_NUM 500001
unsigned long long int CityTreasure[MAX_NUM] = {0};
unsigned long long int City_Weight[MAX_NUM] = {0};
int N, M;
int longest_target = 0;
unsigned long long int longest_path_weight = 0;

struct Path
{
    int city_v;
    unsigned long long int weight;
};
vector<Path> PathTreasure[MAX_NUM];

bool findlongest[MAX_NUM] = {false};
bool visit[MAX_NUM] = {false};
vector<int> topological;
// vector<Path> InversePathTreasure[MAX_NUM];
// bool inverse_visit[MAX_NUM];
// vector<vector<int>> inverse_topological;

// void Find_Longest_Path(int root)
// {
//     //initialize
//     for (int point = 1; point <= N; point++)
//     {
//         City_Weight[point] = -__LONG_LONG_MAX__;
//     }
//     City_Weight[root] = CityTreasure[root];
//     vector<int> search;
//     vector<int> search_tmp;
//     search.clear();
//     search.reserve(N + 1);
//     search_tmp.clear();
//     search_tmp.reserve(N + 1);
//     search_tmp.emplace_back(root);

//     //check all the vertice are the same or not
//     bool is_the_same;
//     //check there is a point will be search next time
//     bool search_additional_point = true;
//     //if a point is already run BFS, omitting it
//     int already_search_point = 0;
//     if (City_Weight[root] > longest_path_weight)
//     {
//         longest_path_weight = City_Weight[root];
//     }
//     //at most do N-1 times
//     for (int time = 1; time < N; time++)
//     {

//         if (time == 1)
//         {
//             is_the_same = false;
//         }
//         else
//         {
//             is_the_same = true;
//         }

//         if (search_additional_point)
//         {
//             search_additional_point = false;
//             search.assign(search_tmp.begin() + already_search_point, search_tmp.end());
//         }
//         else
//         {
//             break;
//         }

//         for (vector<int>::iterator search_it = search.begin(); search_it != search.end(); search_it++)
//         {
//             int search_point = *search_it;
//             already_search_point++;
//             //search all the path from u to v
//             for (vector<Path>::iterator it = PathTreasure[search_point].begin(); it != PathTreasure[search_point].end(); it++)
//             {
//                 Path path = *it;
//                 //if a point has not been search yet, push it into the queue for next time
//                 if (City_Weight[path.city_v] == -__LONG_LONG_MAX__)
//                 {
//                     is_the_same = false;
//                     search_additional_point = true;
//                     search_tmp.emplace_back(path.city_v);
//                 }
//                 if (City_Weight[path.city_v] < City_Weight[search_point] + path.weight + CityTreasure[path.city_v])
//                 {
//                     City_Weight[path.city_v] = City_Weight[search_point] + path.weight + CityTreasure[path.city_v];
//                     if (City_Weight[path.city_v] > longest_path_weight)
//                     {
//                         longest_path_weight = City_Weight[path.city_v];
//                     }
//                 }
//             }
//         }

//         if (is_the_same)
//             break;
//     }
// }
// void Longest_Target(int start_point)
// {
//     if (InversePathTreasure[start_point].begin() == InversePathTreasure[start_point].end())
//     {
//         Find_Longest_Path(start_point);
//         return;
//     }
//     for (vector<Path>::iterator it = InversePathTreasure[start_point].begin(); it != InversePathTreasure[start_point].end(); it++)
//     {
//         Path path = *it;
//         Longest_Target(path.city_v);
//     }
// }
void Find_Longest(int root)
{
    findlongest[root] = true;
    if (City_Weight[root] > longest_path_weight)
    {
        longest_path_weight = City_Weight[root];
    }
    for (vector<Path>::iterator path_it = PathTreasure[root].begin(); path_it != PathTreasure[root].end(); path_it++)
    {
        if (City_Weight[path_it->city_v] < City_Weight[root] + path_it->weight + CityTreasure[path_it->city_v])
        {
            City_Weight[path_it->city_v] = City_Weight[root] + path_it->weight + CityTreasure[path_it->city_v];
            Find_Longest(path_it->city_v);
        }
    }
}

void Topological_Sort(int v, bool check[], vector<int> &stack)
{
    check[v] = true;
    for (vector<Path>::iterator path_it = PathTreasure[v].begin(); path_it != PathTreasure[v].end(); path_it++)
    {
        if (!check[path_it->city_v])
        {
            Topological_Sort(path_it->city_v, check, stack);
        }
    }
    stack.emplace_back(v);
}
// void Inverse_Topological_Sort(int v, bool visit[], vector<vector<int>> &stack, vector<int> &cycledetect)
// {
//     visit[v] = true;
//     cycledetect.emplace_back(v);
//     for (vector<Path>::iterator it = InversePathTreasure[v].begin(); it != InversePathTreasure[v].end(); it++)
//     {
//         Path path = *it;
//         if (!visit[path.city_v])
//         {
//             Inverse_Topological_Sort(path.city_v, visit, stack, cycledetect);
//         }
//     }
// }
int main()
{

    scanf("%d%d", &N, &M);
    PathTreasure->reserve(M);
    topological.reserve(N + 1);
    for (int city = 1; city <= N; city++)
    {
        scanf("%llu", &CityTreasure[city]);
    }
    Path input;
    int u, tmp_u;
    for (int path = 0; path < M; path++)
    {
        scanf("%d%d%llu", &u, &input.city_v, &input.weight);
        PathTreasure[u].emplace_back(input);
        // tmp_u = u;
        // u = input.city_v;
        // input.city_v = tmp_u;
        // InversePathTreasure[u].emplace_back(input);
    }

    for (int city = 1; city <= N; city++)
    {
        if (!visit[city])
        {
            Topological_Sort(city, visit, topological);
        }
    }
    for (vector<int>::reverse_iterator rit = topological.rbegin(); rit != topological.rend(); rit++)
    {
        if (!findlongest[*rit])
        {
            if (City_Weight[*rit] < CityTreasure[*rit])
            {
                City_Weight[*rit] = CityTreasure[*rit];
            }
            Find_Longest(*rit);
        }
    }
    // vector<int> cycledetect;
    // for (vector<int>::reverse_iterator rit = topological.rbegin(); rit != topological.rend(); rit++)
    // {
    //     int u = *rit;
    //     if (!inverse_visit[u])
    //     {
    //         cycledetect.clear();
    //         Inverse_Topological_Sort(u, inverse_visit, inverse_topological, cycledetect);
    //     }
    // }
    // for (vector<vector<int>>::iterator it = inverse_topological.begin(); it != inverse_topological.end(); it++)
    // {
    //     vector<int> connected_componet = *it;
    // }
    printf("%llu\n", longest_path_weight);
    system("pause");
}