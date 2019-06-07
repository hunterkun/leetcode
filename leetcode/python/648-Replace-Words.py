
'''
648. Replace Words
Input: dict = ["cat", "bat", "rat"]
sentence = "the cattle was rattled by the battery"
Output: "the cat was rat by the bat"
'''
def replaceWords(d, sentence):
    d = set(d)
    words = sentence.split()
    res = []
    for word in words:
        res.append(get_root(word))
    ' '.join(res)

def get_root(word):
    for i in range(1, len(word)):
        if word[0:i] in d:
            return word[0:i]
    return word

#split函数和join函数的实现
def split(s, delimiter):
    res=[]
    i = 0
    while i < len(s):
        pos = s.find(delimiter, i)
        if(pos == -1):
            res.append(s[i:])
            break
        else:
            res.append(s[i: pos])
            i = pos + 1
    return res


def join(s, delimiter):
    if len(s) == 0:
        return ""
    ret = s[0]
    for i in range(1, len(s)):
        ret += (delimiter+s[i])
    return ret