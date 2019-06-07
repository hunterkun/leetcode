
'''
11. Container With Most Water
'''
def MaxArea(height):
    l, r = 0, len(height) - 1
    best = 0
    while l < r:
        volume = min(height[l], height[r]) * (r - l)
        best = max(best, volume)
        if height[l] < height[r]:
            l += 1
        else:
            r -= 1
    return best 