#include <iostream>
#include <vector>
#include <math.h>
#include <string>
// #include "myclasses.h"
// #include <utility>
#include <map>
using namespace std;
class longest_Common_Prefix {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size()) {
            return "";
        }
        string prefix = strs[0];
        int count = strs.size();
        for (int i = 1; i < count; ++i) {
            prefix = longestCommonPrefix(prefix, strs[i]);
            if (!prefix.size()) {
                break;
            }
        }
        return prefix;
    }

    string longestCommonPrefix(const string& str1, const string& str2) {
        int length = min(str1.size(), str2.size());
        int index = 0;
        while (index < length && str1[index] == str2[index]) {
            ++index;
        }
        return str1.substr(0, index);
    }
};


int main()
{
    vector<string> strs{"flower","flow","flight"};
    // vector<string> strs{};
    string temp;
    longest_Common_Prefix test;
    cout << test.longestCommonPrefix(strs) << endl;
    // string s;
    // s = to_string(a);
    // cout << s[0]  << "\n" << s[1] << s[2] << endl;
    // cout << (s.length())/2 << endl;

    // // int a = 1534236469;
    // int a = 123;
    // zheng_shu_fan_zhuan zzh;
    // cout << zzh.reverse(a) << endl;
    // pair<string ,string>author {"james","joke"};
    // cout << author.first << endl;
    // cout <<author.second << endl;
    // map<string,int> a;
    // a["aa"] = 5;
    // a.insert({"bb",7});
    // a.insert(make_pair("cc",9));
    // a.insert( pair<string,int>("dd",11) );
    // a.insert( map<string,int> :: value_type("ee",13) );
    // // cout << (a.find("ee") == a.end()) << endl;
    // // auto map_it = a.begin();
    // // cout << map_it->first << endl;
    // auto q = a.count("aa");
    // cout << q << endl;

    return 0;
}
