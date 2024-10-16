"""
        SORTING IN PYTHON
    - in python there two functions for sorting:
        1. sorted()
        2. list.sort()
    
    1. Sorted()
        - Sorted() returns a new sorted list without modifying the original iterable
        - Syntax: sorted(iterable, key=None, reverse=False)
        - parameter: 
            - iterable: list, tuple, etc you want to sort
            - key: a function that serves as a key for sorting. for ex: key=len, will sort by length of items
            - reverse: if set to true, the list is sorted in descending order. the default is False for ascending order
"""
#Examples:
# Sorting a list of numbers
numbers = [5, 2, 9, 1, 5, 6]
sorted_numbers = sorted(numbers)
print(sorted_numbers)  # Output: [1, 2, 5, 5, 6, 9]

# Sorting in reverse order
sorted_numbers_reverse = sorted(numbers, reverse=True)
print(sorted_numbers_reverse)  # Output: [9, 6, 5, 5, 2, 1]

# Sorting by the length of strings
words = ["apple", "banana", "pear", "cherry"]
sorted_by_length = sorted(words, key=len)
print(sorted_by_length)  # Output: ['pear', 'apple', 'cherry', 'banana']

"""
        2. list.sort
    - the list.sort() method sorts a list in place, meaning it modifies the original list and doesn't return a new list.
    - it only works on lists
    - Syntax:
        list.sort(key=None, reverse=False)
    - Parameters:
        - key: function that severes as a key for sorting
        - reverse: if set to True, the list is sorted in descending, the default is False

"""
# Sorting a list of numbers in place
numbers = [5, 2, 9, 1, 5, 6]
numbers.sort()
print(numbers)  # Output: [1, 2, 5, 5, 6, 9]

# Sorting in reverse order
numbers.sort(reverse=True)
print(numbers)  # Output: [9, 6, 5, 5, 2, 1]

# Sorting by the length of strings
words = ["apple", "banana", "pear", "cherry"]
words.sort(key=len)
print(words)  # Output: ['pear', 'apple', 'cherry', 'banana']

"""
    Usability: sorted() can be used on any iterable (e.g., lists, tuples, strings), while list.sort() only works on lists.
    Return value: sorted() returns a new list, while list.sort() modifies the original list in place and returns None.
    Time complexity: They both use Timsort algorithm with an average and worst-case time of O(n log n)
"""

"""
            MORE ON KEY FUNCTION
    - When you provide a key function, the elements are not compared directly, instead their key values produced by the key function are compared
    - Syntax:
        - sorted(iterable, key=your_function)
        - list.sort(key=your_function)
        - your_function: should be a function or a lambda expression that takes one argument and returns a value that will be used for comparison

"""
#Example 1: Sorting a list of strings by length
# Sorting a list of words by their length
words = ["banana", "apple", "kiwi", "cherry"]

# The key function is len, which returns the length of each word
sorted_words = sorted(words, key=len)

print(sorted_words)
# Output: ['kiwi', 'apple', 'banana', 'cherry']

# Example 2: Sorting by custom attributes in objects
## Suppose you have a list of objects and want to sort them by a specific attribute
# the key function can help.#
# Define a class Person
class Person:
    def __init__(self, name, age):
        self.name = name
        self.age = age

# Create a list of Person objects
people = [Person("Alice", 30), Person("Bob", 25), Person("Charlie", 35)]

# Sort by age using a lambda as the key function
sorted_people = sorted(people, key=lambda person: person.age)

# Print the sorted list (by age)
for person in sorted_people:
    print(person.name, person.age)
# Output:
# Bob 25
# Alice 30
# Charlie 35

# Example 3: Sorting tuples by the second element
# List of tuples where each tuple is (name, score)
students = [("John", 80), ("Jane", 90), ("Dave", 85)]

# Sort by the second element (the score)
sorted_students = sorted(students, key=lambda student: student[1])

print(sorted_students)
# Output: [('John', 80), ('Dave', 85), ('Jane', 90)]

"""
    Common functions used as Key:
"""
# 1. len: used to sort by length of elements
words = ['banana', 'apple', 'pear']
sorted_by_length = sorted(words, key=len)

# 2. str.lower: used to sort string in a case-insensitive manner
strings = ['Apple', 'banana', 'Cherry']
sorted_case_insensitive = sorted(strings, key=str.lower)

# 3. operator.itemgetter(): used to sort items in dictionaries or tuples based on specific keys or indices
import operator
tuples = [(1, 'b'), (2, 'a'), (3, 'c')]
sorted_by_second_element = sorted(tuples, key=operator.itemgetter(1))

