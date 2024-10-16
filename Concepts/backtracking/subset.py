from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        res = []  # List to store all subsets
        subset = []  # Temporary list to store current subset

        # DFS function to explore subsets
        def dfs(i):
            if i >= len(nums):
                res.append(subset.copy())  # Append a copy of the current subset to results
                return
            # Include nums[i] in the subset
            subset.append(nums[i])
            dfs(i + 1)  # Recur with the next index
            # Exclude nums[i] from the subset (backtrack)
            subset.pop()
            dfs(i + 1)  # Recur with the next index without including nums[i]

        dfs(0)  # Start DFS with the first index
        return res

# Main function to test the solution
def main():
    solution = Solution()
    
    # Example test cases
    nums = [1, 2, 3]  # Example input
    result = solution.subsets(nums)
    
    # Print the output
    print("Subsets of", nums, "are:")
    for subset in result:
        print(subset)

if __name__ == "__main__":
    main()
