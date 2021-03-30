#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <map>
#include <numeric>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include<numeric>
using namespace std;
// bool f3(int x) {return x % 13 == 0;}
// class Solution{
//     public:
//         int find_methods(int N,int max_distance,int point[]){
//             if(N < 3) return 0;
//             int methods = 0;
//             for(int i = 0 ; i < N ; i++ ){
//                 for( int j = i+1 ; j < N ; j++ ){
//                     if(point[j]-point[i] > max_distance) break;
//                     for( int k = j+1 ; k < N ; k++ ){
//                         if(point[k]-point[i] <= max_distance ){
//                             methods ++;
//                         }
//                         else{
//                             break;
//                         }
//                     }
                    
//                 }
//             }
//             return methods;
//         }
// };

int main()
{

    vector<vector<int>> nums = {{1, 0, 1, 1, 0, 1, 0, 1},
                                {1, 0, 1, 1, 0, 1, 1, 1},
                                {0, 0, 0, 0, 0, 0, 0, 1}};
    vector<string> a = { "aaa","adad"};
    // Solution aa;
    // quick_sort(nums,0,nums.size());
    // for(int i = 0; i<nums.size();i++){
    //     cout << nums[i] <<" ";
    // }
    //    int a[][] =  {{1,2,3},{4,5,6}};
    //    cout << a.length << endl;
    int N = 4;
    int max_distance = 3;
    int point[N ] = {1,2,3,4};
    // Solution aa;
    // cout  << aa.find_methods(N,max_distance,point) << endl;
    cout << accumulate(&point[0], &point[2],0) << endl;;
    return 0;
}