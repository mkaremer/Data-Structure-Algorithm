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

# Main function to test the PrefixTree class
def main():
    # Initialize a PrefixTree object
    trie = PrefixTree()
    
    # Insert words into the trie
    trie.insert("apple")
    trie.insert("app")
    
    # Test cases for search
    print(trie.search("apple"))  # Output: True
    print(trie.search("app"))    # Output: True
    print(trie.search("ap"))     # Output: False
    print(trie.search("banana")) # Output: False
    
    # Test cases for startsWith
    print(trie.startsWith("app"))  # Output: True
    print(trie.startsWith("ban"))  # Output: False
    print(trie.startsWith("appl")) # Output: True
    print(trie.startsWith("bana")) # Output: False

# Run the main function
if __name__ == "__main__":
    main()
