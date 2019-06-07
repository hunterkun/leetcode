
/*125. Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric 
characters and ignoring cases.
*/
bool isPalindrome(string s)
{
    int n = s.length();
    int l = 0, r = n - 1;
    while (l < r)
    {
        if (!isalnum(s[l]))
            l++;
        else if (!isalnum(s[r]))
            r--;
        else
        {
            if (tolower(s[l]) != tolower(s[r]))
                return false;
            l++;
            r--;
        }
    }
    return true;
}

