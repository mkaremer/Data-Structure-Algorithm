def find_subsets(nums, target):
    result = []  # To store all the subsets that sum up to the target

    # Helper function for backtracking
    def backtrack(start, current_subset, current_sum):
        # If the current sum equals the target, add the current subset to the result
        if current_sum == target:
            result.append(current_subset[:])  # Make a copy of the current subset
            return
        
        # If the current sum exceeds the target, no need to proceed further
        if current_sum > target:
            return
        
        # Iterate through the remaining numbers, starting from the 'start' index
        for i in range(start, len(nums)):
            # Add the current number to the subset and update the sum
            current_subset.append(nums[i])
            backtrack(i + 1, current_subset, current_sum + nums[i])  # Move to the next number
            # Backtrack: remove the last added number and try other possibilities
            current_subset.pop()

    # Start the backtracking process
    backtrack(0, [], 0)
    return result

# Example usage:
nums = [2, 3, 6, 7]
target = 7
subsets = find_subsets(nums, target)
print("Subsets that sum to", target, ":", subsets)
