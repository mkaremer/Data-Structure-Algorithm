"""
                        TWO POINTER TECHNIQUE
    - The two pointers technique is a simple method used to solve problems with arrays or 
        lists by using two pointers (or indices).

            HOW IT WORKS

    1. start: You set two pointers at different positions. Usually, one at the beginning and one at the end.
    2. Move: Depending on the problem, you move the pointers towards each other or in a specific way.
    3. Check: At each step, you check if the current positions of the pointers meet the problem's condition.
    4. Stop: The process stops when the pointers meet the condition or each other.

            Common Examples
    1. Finding pairs with a sum

        - Problem: Find two numbers in a sorted array that add up to a target sum.

        - Solution Algorithm:
            - Start one pointer at the beginning and the other at the end.
            - Check the sum of the numbers at these pointers.
            - If the sum matches the target, you're done.
            - If the sum is too low, move the left pointer right to increase the sum.
            - If the sum is too high, move the right pointer left to decrease the sum.
"""
def find_pair_with_sum(arr, target):  # Define the function with array and target as parameters
    left, right = 0, len(arr) - 1  # Initialize two pointers, left at the start and right at the end of the array
    
    while left < right:  # Continue the loop while the left pointer is less than the right pointer
        current_sum = arr[left] + arr[right]  # Calculate the sum of the values at the left and right pointers
        
        if current_sum == target:  # If the current sum equals the target
            return (left, right)  # Return the indices of the left and right pointers as a tuple
        
        elif current_sum < target:  # If the current sum is less than the target
            left += 1  # Increment the left pointer to increase the sum
        
        else:  # If the current sum is greater than the target
            right -= 1  # Decrement the right pointer to decrease the sum
    
    return None  # If no pair is found, return None

"""
    WHY USE TWO POINTERS?

        1. Fast: Usually quicker than other methods.
        2. Simple: Easy to write and understand.
        3. Memory Efficient: Uses very little extra space.
    
    COMMON USES
        - Finding pairs or groups in arrays.
        - Sliding window problems like finding subarrays.
        - Partitioning arrays like separating even and odd numbers.
        - String problems like finding palindromes.
    
    The two pointers technique is a handy tool for solving many common programming problems quickly and efficiently.
"""

"""
            EXAMPLE PROBLEM 2
    - Given a sorted array, remove duplicates in-place such that each element appears 
            only once and return the new length.
    SOLUTION:
        - init two pointers, i initially at the start and j initially at the second element
        - traverse the array with j pointer
        - if arr[j] is different from arr[i], increment i and copy arry[i] to arry[i]
        - continue until j reaches the end of the array
"""
def remove_duplicates(arr):  # Define the function to remove duplicates from a sorted array
    if not arr:  # Check if the array is empty
        return 0  # Return 0 if the array is empty

    i = 0  # Initialize the first pointer 'i' to the start of the array

    for j in range(1, len(arr)):  # Iterate through the array starting from the second element
        if arr[j] != arr[i]:  # Check if the current element is different from the element at pointer 'i'
            i += 1  # Increment the pointer 'i' to move to the next unique position
            arr[i] = arr[j]  # Update the position at 'i' with the new unique element
    
    return i + 1  # Return the number of unique elements, which is 'i' plus one
