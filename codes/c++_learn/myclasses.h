#ifndef MYCLASSES_H_
#define MYCLASSES_H_

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <string>

// using namespace std;
// //整数反转
// class zheng_shu_fan_zhuan{
//     public:
//     int reverse(int a);

// };

// ///判断回文数
// class pan_duan_hui_wen {
// public:
//     bool isPalindrome(int x);

// };

//最长字符串字头
class longest_Common_Prefix{
public:
    std::string longestCommonPrefix(vector<std::string> &strs);
};
#endif