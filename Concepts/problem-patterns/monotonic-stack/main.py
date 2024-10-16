#
#       MONOTONIC STACK PATTERN
# - This a very useful technique used to solve problems which involves finding the 
#           next or prev greater or smaller element in a list
# - it used a stack to keep elements in a specific order, either increasing or decreasing
# - The key idea is to process elements in a way that guarantees efficient lookups reducing the time 
#           complexity from O(n^2) to O(n)
#   2 TYPES:
#   - Monotonic increaseing stack: a stack where the elements are in increasing order from the bottom to top
#   - monotonic decreasing stack: A stack where the elements are in decreasing order from the bottom to top
# 
#   COMMON USE CASES
# - it used to solve problems involving:
#   - Next greater element or previous greater element.
#   - Next smaller element or previous smaller element.
#   - Range problems, like finding the largest rectangle in a histogram.
# 
#   PATTERN EXPLANATION
# 
# - The basic idear is to traverse an array and use a stack to keep track of elements in a monotonic order.
# - as you encounter new elements, you pop elements from the stack that violate the order.
# - This gives you the required relationship like next greater or smaller for the elements you pop
# 
#   MONOTONIC INCREASEING STACK EXAMPLE
# - this stack is used to find the next greater element or to maintain increase elements
# - when a new element breaks the increasing order, pop the top of the stack, which gives the previous smaller element
# 
#   MONOTONIC DECREASEING STACK EXAMPLE
# - this stack is used to find the next smaller element or maintain decreasing elements
# - when a new element breaks the decreasing order, pop the top of the stack, which gives the prev larger element
# 
# TYPICAL STEPS TO SOLVE A PROBLEM USING MONOTONIC STACK
# 
#   1. init the stack: start with an empty stack
#   2. traverse the array: loop thru each element of the array
#   3. process the stack: for each element while the stack is not empty and the current element
#                   violates  the monotonic property, pop elements from the stack
#   4. update results: use the popped elements to update the results. Ex: for next greater set the result of the popped element to the current element
#   5. push current element: After popping, push the current element or its index onto the stack
# 
#  COMMON LEETCODE PROBLEMS USING MONOTONIC STACK
# 
# 1.LeetCode #739: Daily Temperatures (Next Greater Element)
# 2.LeetCode #496: Next Greater Element I
# 3.LeetCode #84: Largest Rectangle in Histogram
# 4. LeetCode #503: Next Greater Element II
# 5. LeetCode #42: Trapping Rain Water (Decreasing Monotonic Stack)
# ##