def partition(arr, low, high):
    pivot = arr[high]  # Choosing the last element as pivot
    i = low - 1  # Index of smaller element

    for j in range(low, high):
        # If the current element is smaller than or equal to the pivot
        if arr[j] <= pivot:
            i = i + 1  # Increment index of smaller element
            arr[i], arr[j] = arr[j], arr[i]  # Swap

    arr[i + 1], arr[high] = arr[high], arr[i + 1]  # Swap the pivot element
    return i + 1

def quicksort(arr, low, high):
    if low < high:
        # pi is the partitioning index, arr[pi] is now at the right place
        pi = partition(arr, low, high)

        # Separately sort elements before partition and after partition
        quicksort(arr, low, pi - 1)
        quicksort(arr, pi + 1, high)


#time complexity: Best/average case O(n log n), worst case: O(n^2)
# Space complexity: O(log n) for in-place due to recursion stack

"""
            TIME AND SPACE COMPLEXITY OF QUICK-SORT
    Quick Sort is an efficient sorting algorithm with different time complexities based on the situation:

Average Case:

O(n log n): On average, quick sort performs well, taking O(n log n) time. 
This happens because the list is divided roughly in half at each step, and sorting each half takes O(n) time.

Best Case:

O(n log n): The best-case scenario is similar to the average case, occurring when 
the pivot element perfectly splits the array into two equal parts each time.

Worst Case:

O(n^2): The worst-case scenario happens when the pivot elements are the smallest or largest elements, 
causing one side of the partition to be empty. This results in n recursive calls, each taking O(n) time, leading to O(n^2).

Quick Sort Space Complexity
In-Place Sorting:

O(log n): Quick sort is generally an in-place sort (it doesn't need extra space proportional to the input size). 
However, it uses space for the recursion stack. In the average and best cases, the depth of recursion is O(log n), 
so the space complexity is O(log n).

Worst Case:

O(n): In the worst case, the depth of recursion can go up to O(n), 
where the recursion stack can hold up to n recursive calls.
"""