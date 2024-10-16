'''
            HEAP
    - A heap is a specialized binary tree that satisfies the heap property.
    - In python heapQ module provides a way to maintain a heap using a list
    
            TYPES OF HEAPS
    1. Min-heap
        - in min-heap smallest elemets is always at the root
        - Every parent node has a value smaller than or equal to its children
        - This allows for efficient retrieveal fo the min element

    2. Max-heap
        - in a max-heap, the largest element is at the root
        - every parent node has a value greater thatn or equal to its children
        - this allows for efficient retrieval of the max element
    
    NOTE: python implments a min-heap by default. a Max-heap can be simulated by inverting the sign
            of the values being stored. (i.e: stroing the negative of numbers)

    
    PYTHON'S heapq MODULE

    1. Key operations of heapQ:
        - heapq.heappush(heap, item):
            - pushes element to heap while maintaining its property
            - time complexity: O(log n) where n is the size of the heap
        - heapq.heappop(heap):
            - removes and returns smallest elemnt from heap
            - the heap property is maintained after this
            - time complexity: O(log n) where n is the size of the heap

        - heapq.heapify(iterable):
            - transforms a list into a heap, in-place
            - heap property applied to entire list
            - time complexity: O(n), where n is the number of elements in list
        - heapq.heappushpop(heap, item):
            - pushes a new element onto the heap, then pops and returns the smallest element
            - This is more efficient than calling heappush() followed by heappop()
            - time complexity: O(log n)
        - heapq.heapreplace(heap, item):
            - pops the smallest element and then pushes a new element onto the heap
            - this is more efficient than calling heappop() followed by heappush()
            - time complexity: O(log n)
        - heapq.nlargest(n, iterable):
            - returns the n largest elements from the iteratble in descending order
            - time complexity: O(n log n)
        - heapq.nsmallest(n, iterable):
            - returns the n smallest elements from the iterable in ascending order
            - time complexity: O(n log n)
'''
import heapq

#creating an empty heap
heap = []

#pushing elements into the heap
heapq.heappush(heap, 3)
heapq.heappush(heap, 1)
heapq.heappush(heap, 4)
heapq.heappush(heap, 2)

# The smallest element is at the root (index 0)
# print(heap)  # Output: [1, 2, 4, 3]

# Popping the smallest element
smallest = heapq.heappop(heap)
# print(smallest)  # Output: 1
# print(heap)      # Output: [2, 3, 4]

# Transforming a list into a heap
lst = [5, 7, 9, 1, 3]
heapq.heapify(lst)
print(lst)  # Output: [1, 3, 9, 7, 5]

# Using heappushpop (pushes 0, then pops the smallest)
result = heapq.heappushpop(lst, 0)
print(result)  # Output: 0
print(lst)     # Output: [1, 3, 9, 7, 5]

# Using heapreplace (pops 1, pushes 10)
result = heapq.heapreplace(lst, 10)
print(result)  # Output: 1
print(lst)     # Output: [3, 5, 9, 7, 10]

# Finding the 3 largest elements
largest_three = heapq.nlargest(3, lst)
print(largest_three)  # Output: [10, 9, 7]

# Finding the 3 smallest elements
smallest_three = heapq.nsmallest(3, lst)
print(smallest_three)  # Output: [3, 5, 7]


""" MAX-HEAP IMPLEMENTATION
    - There is no implementation of max heap, to simulate a max heap, 
        you store the negative values in the heap
    - when retrieving from heap, simply negate the values back to their original form
"""
# Max-Heap simulation by storing negative values
max_heap = []

# Push elements (store negative values)
heapq.heappush(max_heap, -3)
heapq.heappush(max_heap, -1)
heapq.heappush(max_heap, -4)
heapq.heappush(max_heap, -2)

# The largest element is the smallest negative number
print(-heapq.heappop(max_heap))  # Output: 4
print(-heapq.heappop(max_heap))  # Output: 3


"""
        USE CASES OF HEAPS
    1. priority queues: Heaps are ideal for implementing priority queues where elements with the highest or 
            lowest priority are efficiently retrieved and processed.
    2. Finding the K Smallest/Largest Elements: Heaps can be used to find the top k smallest or largest 
            elements in a collection efficiently without fully sorting it.
    3. Merging Sorted Sequences: Heaps can be used to efficiently merge multiple sorted sequences.
    4. Dijkstra's Algorithm: In graph algorithms like Dijkstra's, heaps help efficiently retrieve the 
        vertex with the smallest tentative distance.


    ADVANTAGES OF HEAPS

    1. Heaps provide efficient time complexity for insertions, deletions, and retrieval of the minimum or 
            maximum element.
    2. They are suitable for streaming data or continuously updating datasets where you need to 
            maintain the smallest or largest elements.

"""

""" Problem: Kth Largest number

Design a class to find the kth largest integer in a stream of values, including duplicates. E.g. the 2nd largest 
from [1, 2, 3, 3] is 3. The stream is not necessarily sorted.

Implement the following methods:

constructor(int k, int[] nums) Initializes the object given an integer k and the stream of integers nums.
int add(int val) Adds the integer val to the stream and returns the kth largest integer in the stream.

Algorithm:
    - We use top k element pattern
        - use a min heap to keep track of the k elements.
        - in the constructor, add them to the heap. if you see a number that is greater than the one on the 
            top of the heap replace it. 
        - at the end return the number at the top of the heap.
    Time and space:
        1. time: 
            - in constructor, we loop thru each element adding to the heap. pushing to the heap takes
                O(log k), there total of n elements so the total time is O(n log k)
           
        2. Space: 
             - space complexity is O(k) since the heap only stores k elements.
"""
class KthLargest:
    def __init__(self, k: int, nums: list):
        # Initialize the object with k and the list of test scores
        self.k = k
        self.min_heap = []
        
        # Add each element in nums to the heap
        for num in nums:
            self.add(num)
    
    def add(self, val: int) -> int:
        # Add the new test score (val) to the heap
        if len(self.min_heap) < self.k:
            # If the heap has fewer than k elements, just add the element
            heapq.heappush(self.min_heap, val)
        elif val > self.min_heap[0]:
            # If the heap is full (size k) and val is larger than the smallest element, replace the smallest
            heapq.heapreplace(self.min_heap, val)
        
        # The kth largest element is always the root of the min-heap
        return self.min_heap[0]

""" Problem: Last Stone Weight
    You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together. 
Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the weight of the last remaining stone. If there are no stones left, return 0.

Algorithm:
    - use a maxheap to solve this problem
    - push negative weiths of stones into a min heap
    - pop the largest two stones
    - if both stones are equal, destroyed them
    - if they are not equal, push their difference to heap
    - repeat the above process as long as len(max_heap) > 1
    - return the first elemnt of max_heap if not empty else 0

Time:
    - heapify list takes O(n)
    - each pop and push takes O(log n)
    - since we did the above operations k times, the total will be O(k log n)
space: 
    - space is O(n) when n is number of elements
"""
class Solution:
    def lastStoneWeight(self, stones: list[int]) -> int:
        # Convert all stone weights to negative and create a max-heap using heapq (min-heap in Python)
        max_heap = [-stone for stone in stones]
        
        # Heapify the list to turn it into a heap
        heapq.heapify(max_heap)
        
        # Continue smashing until we have less than 2 stones
        while len(max_heap) > 1:
            # Pop the two largest stones (heaviest ones)
            stone1 = -heapq.heappop(max_heap)  # Convert back to positive
            stone2 = -heapq.heappop(max_heap)  # Convert back to positive
            
            # If stone1 and stone2 are not the same, the remainder goes back into the heap
            if stone1 != stone2:
                new_stone = stone1 - stone2
                heapq.heappush(max_heap, -new_stone)  # Push the negative weight back
        
        # If there's one stone left, return its weight, otherwise return 0
        return -max_heap[0] if max_heap else 0

"""
    Problem: K Closest points to the origin

You are given an 2-D array points where points[i] = [xi, yi] represents the coordinates of a point on an X-Y axis plane. 
You are also given an integer k. Return the k closest points to the origin (0, 0).
The distance between two points is defined as the Euclidean distance (sqrt((x1 - x2)^2 + (y1 - y2)^2)).
You may return the answer in any order.

Algorithm:
    - Loop thru the points and find distances of each to the origin
    - store the result of each point with dist, and coordinates like this [dist, x, y]
    - heapify the list result
    - pop from the list k times and return the coordinates
time complexity:
    - getting distances of points: O(n) when n is number of points
    - heapifying the list: O(n)
    - poping from the heap: O(k log n), we popped k times, each operation was O(log n)

"""
class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        # Initialize an empty list to store distances and points as (distance, x, y)
        minHeap = []
        
        # Loop through each point in the input list 'points'
        for x, y in points:
            # Calculate the squared Euclidean distance from the origin (0, 0)
            # We don't take the square root because we only need to compare distances
            dist = (x ** 2) + (y ** 2)
            
            # Append the distance and the point (x, y) as a tuple to the minHeap
            # Format: [distance, x, y]
            minHeap.append([dist, x, y])
        
        # Convert the list into a min-heap (heapify) to efficiently get the smallest elements
        heapq.heapify(minHeap)
        
        # Initialize an empty list to store the closest k points
        res = []

        # Extract the k closest points
        while k > 0:
            # Pop the smallest distance point from the heap (based on distance)
            dist, x, y = heapq.heappop(minHeap)
            
            # Append the coordinates [x, y] of the closest point to the result list
            res.append([x, y])
            
            # Decrease k by 1 (one closest point has been processed)
            k -= 1
            
        # Return the list of k closest points
        return res
