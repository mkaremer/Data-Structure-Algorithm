#    BACKTRACKING
# - KEY CONCEPT OF BACKTRACKING
#   - the basic idea of backtracking is to search for a solution to a problem by trying out different posibilities
#   - if a certain possibility does nto lead to a valid solution, we backtrack by returning to a previous state adn trying a new option
# 
# - Backtracking if often used for problems that can be described by the following structure:
#       1. search space: there is a set of choices or decisions that need to be made often with constraints
#       2. partial solution: at any step in the process a partial solution is build.
#       3. backtracking condition: if the partial solution violates any constraints or can't lead to a valid solution,
#               we backtrack (discard the current partial soluton and explore a differnt one.)
#       4. Base case: when a valid solution is found or all possibilities are explored, the process stops
# 
# - WHEN IS BACKTRACKING USEFUL?
#   - Backtracking is ideal fro problems where:
#       - the solution involves making a series of choices
#       - there are constraints to respect
#       - you need to explore all possibilites but in an effient way
#       - pruning parts of the search space early can help avoid unnecessary work
# 
# - BACKTRACKING IN ACTION: PROBLEM-SOLVING STEPS
#   1. start from initial state: Begin with an empty or initial solution, and attempt to extend it by adding more elements
#   2. Move forward: Try one option or possibility at a time from the set of choices. 
#           Add the possibility to the current partial solution
#   3. check for feasibility: after each decision or step, check if the current partil solution is still valid. 
#           (i.e: it satisfies problem contraints)
#   4. backtrack if necessary: If a partial solution is invalid or doesn't lead to a full solution, 
#           undo the last decision (backtrack) and try another option.
#   5 . Base Case or Goal: If the current partial solution leads to a valid full solution, return that solution. 
#               If no further possibilities exist, return no solution or stop.
# 
#                   PRACTICE PROBLEMS##

"""
       WORD SEARCH PROBLEM:
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or 
vertically neighboring. The same letter cell may not be used more than once.

        THE ALGORITHM SOLUTION:
Outer Loop: The algorithm goes through each cell in the board to see if the word can start from that cell. 
It uses the backtrack function to search for the word starting from the first character.

Backtracking Function:
    The function checks if the current cell can match the current letter in the word.
    If all the letters in the word are matched, it returns True.
    If the cell is out of bounds or the letter doesn’t match, it returns False.
    It marks the cell as visited to avoid using it again in the same path.
    Then, it tries moving in all four directions (up, down, left, right) to continue matching the next letters.
    If no valid path is found, it undoes the changes (backtracks) and returns False.
Return: If the function finds the word, it returns True; if not, it returns False.

TIME AND SPACE COMPLEXITY

    1. Time complexity: The algorithm checks each cell on the board, and for each cell, it can explore up to 4 directions.
      In the worst case, it explores every possible path of length equal to the word. So, the time complexity is:
        O(m * n * 4^l)
        where: m x n is the size of the baord
                l is the length of the word
    2. Space complexity:
        The maximum depth of recursion is the length of the word, so the space complexity is:
                O(l) due to the recursion stack

"""

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        # This helper function performs the backtracking search
        # i, j are the coordinates on the board, and k is the index of the character in the word that we're trying to match
        def backtrack(i, j, k):
            # Base case: If we have matched all characters in the word, return True
            if k == len(word):
                return True
            
            # Check if the current position is out of bounds or if the current character on the board
            # does not match the k-th character in the word. If so, return False.
            if i < 0 or i >= len(board) or j < 0 or j >= len(board[0]) or board[i][j] != word[k]:
                return False

            # Temporarily mark the current cell as visited by setting it to a space (or any non-alphabet character)
            # This is done to avoid revisiting the same cell in the same search path.
            temp = board[i][j]
            board[i][j] = " "

            # Explore the next character in the word by recursively calling backtrack on all four possible directions
            # (down, up, right, and left). If any of the recursive calls return True, we have found the word.
            if (backtrack(i + 1, j, k + 1) or   # Move down
                backtrack(i - 1, j, k + 1) or   # Move up
                backtrack(i, j + 1, k + 1) or   # Move right
                backtrack(i, j - 1, k + 1)):    # Move left
                return True
            
            # Backtrack: Restore the original character in the board after exploring all directions.
            board[i][j] = temp

            # If no valid path was found, return False
            return False
        
        # Loop over each cell in the board to find the starting point of the word
        for i in range(len(board)):         # Iterate over rows
            for j in range(len(board[0])):  # Iterate over columns
                # Start the backtracking search from the current cell (i, j) with the first character in the word (index 0)
                if backtrack(i, j, 0):
                    return True  # If a valid path for the word is found, return True immediately
        
        # If no valid path for the word is found in any starting position, return False
        return False
