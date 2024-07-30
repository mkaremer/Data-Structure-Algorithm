"""
                        STACK
    - A stack is a linear data structure that follows the Last In First Out (LIFO) principle. 
    - This means that the last element added to the stack is the first one to be removed.
    - It is analogous to a stack of plates where you can only add or remove the top plate.

        KEY OPERATIONS ON A STACK

    1. Push: Add an element to the top of the stack.
    2. Pop: Remove and return the top element of the stack.
    3. Peek/Top: Return the top element of the stack without removing it.
    4. isEmpty: Check if the stack is empty.
    5. Size: Return the number of elements in the stack.

        CHARACTERISTICS OF A STACK
    - LIFO (Last In, First Out): The last element added is the first to be removed.
    - Dynamic Size: The stack can grow and shrink as needed (in implementations that do not have a fixed size).

        STACK IMPLEMENTATION IN PYTHON
    - In Python, a stack can be implemented using a list. 
    - Python's list provides an efficient way to perform the stack operations with the following methods:
        - append() to push an element to the stack.
        - pop() to remove and return the top element.
"""
class Stack:
    def __init__(self):
        self.items = []  # Initialize an empty list to store stack elements

    def is_empty(self):
        return len(self.items) == 0  # Return True if the stack is empty, False otherwise

    def push(self, item):
        self.items.append(item)  # Add an element to the top of the stack

    def pop(self):
        if not self.is_empty():
            return self.items.pop()  # Remove and return the top element if the stack is not empty
        else:
            return None  # Return None if the stack is empty (can also raise an exception)

    def peek(self):
        if not self.is_empty():
            return self.items[-1]  # Return the top element without removing it
        else:
            return None  # Return None if the stack is empty

    def size(self):
        return len(self.items)  # Return the number of elements in the stack

    def display(self):
        print(self.items)  # Display the elements of the stack

"""
            EXAMPLE PROBLEM
    - Validate parentheses: 
    You are given a string s consisting of the following characters: '(', ')', '{', '}', '[' and ']'.

The input string s is valid if and only if:

Every open bracket is closed by the same type of close bracket.
Open brackets are closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
Return true if s is a valid string, and false otherwise.

SOLUTION ALGORITHM:
This solution checks if a string of brackets is valid. Here's how it works:

Use a Stack: It uses a stack (like a list) to keep track of opening brackets.
Mapping Brackets: A dictionary maps closing brackets to their matching opening brackets.
Iterate Through the String: For each character in the string:
If it's a closing bracket, check if it matches the last opening bracket in the stack.
If it matches, remove the last opening bracket from the stack.
If it doesn't match, return False (the string is not valid).
If it's an opening bracket, add it to the stack.
Final Check: After checking all characters, if the stack is empty, all brackets matched correctly, so return True. 
If the stack is not empty, return False.
"""
class Solution:  # Define a class named Solution
    def isValid(self, s: str) -> bool:  # Define a method that takes a string and returns a boolean
        stack = []  # Initialize an empty list to use as a stack
        closeToOpen = {"}": "{", "]": "[", ")": "("}  # Dictionary to map closing brackets to their corresponding opening brackets

        for c in s:  # Iterate over each character in the input string
            if c in closeToOpen:  # Check if the character is a closing bracket
                if stack and stack[-1] == closeToOpen[c]:  # Check if the stack is not empty and the top of the stack is the matching opening bracket
                    stack.pop()  # If it matches, pop the top of the stack
                else:  # If it doesn't match
                    return False  # Return False indicating the string is not valid
            else:  # If the character is an opening bracket
                stack.append(c)  # Push it onto the stack
        
        return True if not stack else False  # Return True if the stack is empty (all brackets matched), otherwise return False

