#               TRIE
#   - STRUCTURE OF TRIE
#       - A trie consists of nodes where each node:
#           - represent a letter or part of a string
#           - can have children representing the next characters in the string
#           - may contain a flag or marker to indicate the end of valid string or word
#       - The root node represents an empty string, and from the root each edge in the trie corresponds to a single chars in a string
#   - KEY CHARACTERISTICS OF TRIES
#       - Insertion and search time complexity are O(L) where L is the length of the string
#       - space complexity: tries use a lot of memory where each node can have k children, where k is the number of possible 
#                           characters, 26 for english alphabets
#   - OPERATION ON TREIES
#       - Insertion: 
#           - start from the root of the node
#           - for each character, check if it exists 
#           - if it does move to that child node, else create a new node
#           - after proessing all characters, mark the node representing the last char as the end of a valid word
#       - search:
#           - start at the root
#           - for each character in the word check if the corresponding child node exists
#           - if a node does'nt exists for any character, the word isnt present
#           - if all characters match and the last node is marked as the end of a word, the word is found
#       - Deletion: 
#           - deleting from a trie can be tricky becuase multiple words might share the same prefix.
#           - you only delete nodes if the ndoe is not shared with another word and the word in questyion has ended at that node
# 
#           IMPLEMENTATION
#   ` 1. insert(word: str):
#       - Inserts a word into the Trie by adding nodes for each character that doesn't already exist.
#       - Marks the end of the word when all characters are inserted.
#     2. search(word: str):
#       -  Searches for an exact word in the Trie.
#       - Returns True only if the word is found and marked as a complete word in the Trie (i.e., endOfWord is True).
#     3. startsWith(prefix: str):
#       - Checks if any word in the Trie starts with the given prefix.
#       - It only checks the presence of the prefix and doesn't require the prefix to be a complete word.
##

class TrieNode:
    def __init__(self):
        # Dictionary to hold children nodes for each character
        self.children = {}
        # Boolean to mark the end of a word
        self.endOfWord = False

class PrefixTree:
    def __init__(self):
        # Initialize the root node of the Trie
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        # Start at the root node
        cur = self.root

        # Traverse through each character in the word
        for c in word:
            # If the character is not already a child node, create a new TrieNode
            if c not in cur.children:
                cur.children[c] = TrieNode()
            # Move to the next node (character) in the Trie
            cur = cur.children[c]
        # After inserting all characters, mark the last node as the end of a word
        cur.endOfWord = True

    def search(self, word: str) -> bool:
        # Start at the root node
        cur = self.root

        # Traverse through each character in the word
        for c in word:
            # If the character is not found in the current node's children, return False
            if c not in cur.children:
                return False
            # Move to the next node (character)
            cur = cur.children[c]
        # Return True if we've found the word and it's marked as the end of a word
        return cur.endOfWord

    def startsWith(self, prefix: str) -> bool:
        # Start at the root node
        cur = self.root

        # Traverse through each character in the prefix
        for c in prefix:
            # If the character is not found in the current node's children, return False
            if c not in cur.children:
                return False
            # Move to the next node (character)
            cur = cur.children[c]
        # Return True since we've successfully traversed the prefix, meaning the prefix exists
        return True
