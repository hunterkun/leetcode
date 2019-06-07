'''
125. Valid Palindrome
Given a string, determine if it is a palindrome, considering only alphanumeric 
characters and ignoring cases.
'''
# Two Pointer
def isPalindrome(s):
    i = next_of_alnum(s, 0)
    j = prev_of_alnum(s, len(s) - 1)
    while (i < j):
        if (s[i].lower() != s[j].lower()):
            return False
        else:
            i, j = next_of_alnum(s, i + 1), prev_of_alnum(s, j - 1)
    return True
    

def next_of_alnum(s, pos):
    while (not s[pos].isalnum()):
        pos += 1
        if pos == len(s):
            return len(s)
    return pos

def prev_of_alnum(s, pos):
    while (not s[pos].isalnum()):
        pos -= 1
        if pos == -1:
            return -1
    return pos
