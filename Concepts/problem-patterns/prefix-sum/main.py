"""
        PREFIX SUM PATTERN
    - this pattern is commonly used to solve array problems especially those that require adding over
        a range.
    - This pattern optimise those problems from O(n) ^ 2 to O(n)

    - Given an array a prefix sum is defined as:
        prefix[i] = nums[0] + nums[1] + .... + nums[i]
    
    - To get the range between indices l and r use this formula
        sum from l to r = prefix[r] - prefix[l - 1]
        for l == 0, sum is simply prefix[r]
"""

#           LEETCODE PROBLEMS TO PRACTICE
# 1. Range sum query: https://leetcode.com/problems/range-sum-query-immutable/description/ 
# 2. Contigous Array: https://leetcode.com/problems/contiguous-array/description/  
# 4. subarray sum equals: https://leetcode.com/problems/subarray-sum-equals-k/description/ 
#   K## 

# Example to compute prefix sum array
nums = [1, 2, 3, 4, 5]
# Constructing prefix sum array
prefix = [0] * len(nums)
prefix[0] = nums[0]
for i in range(1, len(nums)):
    prefix[i] = prefix[i - 1] + nums[i]

# Sum of range [l, r]
l, r = 1, 3  # sum from index 1 to 3 -> 2 + 3 + 4 = 9
range_sum = prefix[r] - prefix[l - 1]  # 9



