#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string>
#include "myclasses.h"
using namespace std;

/////整数反转
// int zheng_shu_fan_zhuan::reverse(int a)
// {
//     long sum = 0;
//     vector<int> p;
//     while (abs(a) >= 1)
//     {
//         p.push_back(a % 10);
//         a = a / 10;
//     }
//     for (int i = 0; i < p.size(); i++)
//     {
//         cout << p[i] << "\t" << p[p.size() - i - 1] * pow(10, i) << "\t" << sum << endl;
//         sum = sum + (p[p.size() - i - 1] * pow(10, i));
//         if (sum > (pow(2, 31) - 1) || sum < -pow(2, 31))
//         {
//             sum = 0;
//         }
//     }
//     // cout << "sum :  " << sum << endl;
//     // cout << "-pow(2,31  :  " << -pow(2, 31) << endl;
//     // if (sum >= (pow(2, 31) - 1) || sum <= -pow(2, 31))
//     //     return 0;
//     return sum;
// }

// //////判断是不是回文数
// bool pan_duan_hui_wen::isPalindrome(int x)
// {
//     string s;
//     s = to_string(x);
//     for (int i = 0; i < (s.length() / 2); i++)
//     {
//         if (s[i] != s[s.length() - 1 - i])
//         {
//             return 0;
//         }
//     }
//     return 1;
// }

//// 最长字符串字头
string longest_Common_Prefix::longestCommonPrefix(vector<string> &strs)
{
    if (!strs.size())
    {
        return "";
    }
    string temp;
    temp = strs[0];
    for (int i = 0; i < strs.size(); i++)
    {
        if (strs[i] < temp)
        {
            temp = strs[i];
        }
    }
    string temp1 = temp;
    for (int i = 0; i < strs.size(); i++)
    {
        for (int j = 0; j < temp.length(); j++)
        {
            if (strs[i][temp.length() - j - 1] != temp[temp.length() - j - 1])
            {
                temp1.erase(temp.length() - j - 1);
            }
        }
        temp = temp1;
    }
    return temp;
}
