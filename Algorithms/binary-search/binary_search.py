def binary_search_recursive(arr, target, left, right):
    if left > right:
        return -1  # Target is not present in the array
    
    mid = (left + right) // 2
    if arr[mid] == target:
        return mid  # Target found at index mid
    elif arr[mid] < target:
        return binary_search_recursive(arr, target, mid + 1, right)  # Search in the right half
    else:
        return binary_search_recursive(arr, target, left, mid - 1)  # Search in the left half

# Example usage
if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    target = 7
    result = binary_search_recursive(arr, target, 0, len(arr) - 1)
    print("Target found at index (recursive):", result)


#Binary is done only on sorted array only.
# time complexity: O(log n)
# space complexity: O(log n) for recursive way, O(1) for iterative
# iterative way is preferred due to its constant space complexity

def binary_search_iterative(arr, target):
    left, right = 0, len(arr) - 1
    
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid  # Target found at index mid
        elif arr[mid] < target:
            left = mid + 1  # Search in the right half
        else:
            right = mid - 1  # Search in the left half
    
    return -1  # Target is not present in the array