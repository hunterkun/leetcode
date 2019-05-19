#include <string>
#include <iostream>
using namespace std;

/*
Given a string s, find the longest palindromic substring in s. 
You may assume that the maximum length of s is 1000.
*/

int myAtoi(string str)
{
    int res = 0, sign, i = str.find_first_not_of(' ');
    if (str[i] == '+' || str[i] == '-')
    {
        sign = str[i++] == '+' ? 1 : -1;
    }
    while (isdigit(str[i]))
    {
        if (res > INT32_MAX / 10 || (res == INT32_MAX / 10 && str[i] - '0' > 7))
            return sign > 0 ? INT32_MAX : INT32_MIN;
        res += res * 10 + str[i] - '0';
    }
}