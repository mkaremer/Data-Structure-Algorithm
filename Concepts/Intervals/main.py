"""
        INTERVALS PROBLEMS PATTERNS
    1. Sorting intervals
        - some problems requres sorting intervals based on start times or sometimes the end time. 
        - Sorting helps in identifying overlaps, gaps, and getting the correct order of intervals
        - Common use:
            - before merging intervals or checking conflicts
            - sorting intervals by their start time often simplifies the problem
"""
# Example: Given a list of intervals, merge all overlapping intervals
intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
intervals.sort(key=lambda x: x[0])  # Sort by start time

"""
        2. Merging Intervals
    - a typical pattern is merging intervals where the current interval overlaps with the previous one
    - key idea: if the start time of the current interval is less than or equal to the previous interval, merge them
    - Time and space:
        - time: 
            - sorting takes O(n log n)
            - iteration takes: O(n) when n is the number of intervals
            - overal time: O(n log n) since it's bigger
        - space: 
            - sort() operates in-place 
            - merge list will store n intervals
            - Overal space is O(n)

"""
def merge(intervals):
    # Sort the intervals by their start time (x[0] refers to the start time of each interval)
    intervals.sort(key=lambda x: x[0])
    
    # Initialize an empty list to store the merged intervals
    merged = []
    
    # Loop through each interval in the sorted intervals list
    for interval in intervals:
        # Check if the merged list is empty OR if the current interval does not overlap
        # with the last merged interval (i.e., if the end of the last merged interval is less than the start of the current interval)
        if not merged or merged[-1][1] < interval[0]:
            # If there's no overlap, simply add the current interval to the merged list
            merged.append(interval)
        else:
            # If there is an overlap, update the end of the last merged interval.
            # We do this by setting the end time of the last interval in merged to the
            # maximum of the current interval's end and the last merged interval's end.
            merged[-1][1] = max(merged[-1][1], interval[1])
    
    # Return the merged intervals after processing all intervals
    return merged

"""
        3. Greedy Approach
    - Many interval problems can be solved by selecting intervals in a greedy way. The key
        is to sort by start or end time then pick intervals based on specific conditions
    - Common use: Problems like finding the minimm number of intervals to remove to make the rest non-overlapping
        - sort the intervals by end time first. This is to maximize the number of intervals because if we sort by
                start time, we might have a long interval that takes up the whole space.

        Time complexity:
            - sorting: O(n log n)
            - looping through interval: O(n) where n is the number of intervals
            - Overal time: O(n log n)
        Space complexity:
            - sorting: sorting in python use timsort which takes O(n) space in the worst case
            - Overall space is O(n)
"""

def eraseOverlapIntervals(intervals):
    # Sort the intervals by their end time (x[1] refers to the end time of each interval)
    # This helps to pick intervals that finish earlier, which leaves the most room
    # for subsequent intervals to be included without overlap.
    intervals.sort(key=lambda x: x[1])
    
    # Initialize count (number of intervals to remove) to 0
    # Initialize end to negative infinity, which ensures that the first interval will
    # always be considered because any start time will be greater than negative infinity.
    count, end = 0, float('-inf')
    
    # Loop through the sorted intervals, unpacking each interval into `start` and `finish`
    for start, finish in intervals:
        # If the current interval's start time is greater than or equal to the end time
        # of the last non-overlapping interval, we can include this interval.
        if start >= end:
            # Update the `end` to the finish time of the current interval
            # This means the current interval is now part of the set of non-overlapping intervals.
            end = finish
        else:
            # If the start time is less than the end time, it means there is an overlap.
            # In that case, increment the count because we need to remove this interval.
            count += 1
    
    # Return the total number of intervals we need to remove to make the rest non-overlapping.
    return count

"""
        4. Two pointers technique
    - use two pointers when you have two sets of intervals and need to compare or merge them.
    - Key idea: use two pointers to traverse both sets simultaneously, comparing intervals at each step

    - Example problem: Interval List Intersections
    You are given two lists of closed intervals, firstList and secondList, where firstList[i] = [starti, endi] 
    and secondList[j] = [startj, endj]. Each list of intervals is pairwise disjoint and in sorted order.
    Return the intersection of these two interval lists.

    A closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.
    
    The intersection of two closed intervals is a set of real numbers that are either empty or represented as a 
    closed interval. For example, the intersection of [1, 3] and [2, 4] is [2, 3].

        - Algorithm solution:
            - use two pointers technique
            - find the overlap by taking doing this:
                - get start from max number betweem both starting points of interval
                    - like this: start = max(A[i][0], B[j][0])
                - get the end from min number between both ends points of intervals
                    - like this: end = min(A[i][0], B[j][1])
            - check if they overlap. they overlap is start is less than or equal to the end
                - if start <= end
            - Move pointers: Move the pointer of the interval that finishes first b/c it is guaranteed that this interval will not overlap with futur intervals
                - like this: if A[i][1] < B[j][1] basically if A[i] finishes before B[j] move pointer i to the next interval in A
                                else move j to next interval B
            - the loop contines while there are intervals in both lists

        - Time:
            - O(m + n), where m is len of list A and n is len of list B
        - Space: 
            - O(k), where k is number of intersections
"""
def intervalIntersection(A, B):
    i, j = 0, 0  # Two pointers for A and B
    result = []  # List to store the intersections

    # While there are intervals left to compare in both A and B
    while i < len(A) and j < len(B):
        # Find the overlap between A[i] and B[j]
        start = max(A[i][0], B[j][0])  # The overlap starts at the later start time
        end = min(A[i][1], B[j][1])    # The overlap ends at the earlier end time

        if start <= end:  # If the intervals overlap
            result.append([start, end])  # Add the overlapping interval to the result

        # Move the pointer of the interval that finishes first
        if A[i][1] < B[j][1]:
            i += 1  # Move pointer i forward if A[i] finishes first
        else:
            j += 1  # Otherwise, move pointer j forward

    return result

