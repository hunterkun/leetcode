'''
13. Roman to Integer
'''
def romanToInt(s):
    d = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000,
         'IV':4, 'IX':9,'XL':40,'XC':90,'CD':400,'CM':900}
    result, i = 0, 0
    while i < len(s):
        try:
            result += d[s[i] + s[i + 1]]
            i += 2
        except (KeyError, IndexError):
            result += d[s[i]]
            i += 1
    return result
romanToInt('IL')