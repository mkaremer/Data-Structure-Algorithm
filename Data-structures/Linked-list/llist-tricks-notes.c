/*
           4 Incredibly Useful Linked List Logic for Interview

           Source: https://medium.com/javarevisited/4-incredibly-useful-linked-list-tips-for-interview-79d80a29f8fc

            What I will learn in these notes:
                - Top 4 Logic that solves 20+ Linked List FAANG Interview Problems.
                    1. Reverse Linked List 
                    2. Two Pointer Approach
                    3. Merge Linked Lists
                    4. Sentinel Node (Dummy Node) 

            All of these are Simple Logic, But when Employed together it can make wonders.
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

/*
                1. REVERSE LINKED LIST
    problem: Reverse a singly linked list.

    Input: 1->2->3->4->5->NULL
    Output: 5->4->3->2->1->NULL
*/
// Function to reverse a singly linked list
Node* reverseList(Node* head) {
    Node* prev = NULL;     // Initialize previous node to NULL
    Node* current = head;  // Start with the current node as head
    Node* next = NULL;     // Initialize next node to NULL

    while (current != NULL) {  // Iterate through the list
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the current node's pointer
        prev = current;        // Move the previous node to current
        current = next;        // Move the current node to next
    }
    head = prev;  // Update the head to the new first node (previously the last node)
    return head;  // Return the new head of the reversed list
}

/*
            1.a: Reverse Linked list 2 (REVIEW THIS!!! )

    problem: Reverse a linked list from position m to n. Do it in one-pass.

    Note: 1 ≤ m ≤ n ≤ length of list.
            pv    tn
    Input: 1-> 2->3->4 ->5->NULL, m = 2, n = 4
                st
    Output: 1->4->3->2->5->NULL
*/
// Function to reverse a sublist from position m to n
Node* reverseBetween(Node* head, int m, int n) {
    if (!head || m == n) return head;  // If the list is empty or m equals n, no changes are needed

    Node dummy;  // Create a dummy node to simplify edge cases
    dummy.next = head;  // Set the dummy node's next to the head of the list
    Node* prev = &dummy;  // Initialize prev to the dummy node

    // Move prev to the node just before the m-th node
    for (int i = 1; i < m; i++) {
        prev = prev->next;  // Advance prev one node at a time
    }

    Node* const start = prev->next;  // start points to the m-th node
    Node* then = start->next;  // then points to the node after start

    // Reverse the segment from m to n
    for (int i = 0; i < n - m; i++) {
        start->next = then->next;  // Bypass then
        then->next = prev->next;  // Insert then at the beginning of the reversed segment
        
        prev->next = then;  // Update prev to point to the new first node of the reversed segment
        then = start->next;  // Move then to the next node to be reversed
    }

    return dummy.next;  // Return the new head of the list
}

/*

            2. FAST AND SLOW POINTER TECHNIQUE
    - Use two pointers, slow and fast. 
    - both start at the head of the list
    - Move slow one step at a time
        slow = slow->next
    - Move fast two step at a time
        fast = fast->next
    - When fast reaches the end of list, slow will be at the middle
        fast is NULL(odd list) or fast->next(even list) is NULL
       
*/
Node* middleNode(Node* head){
    if(head == NULL || head->next == NULL ){
        return head;
    }

    Node* slow = head;
    Node* fast = head;

    while(fast != NULL || fast->next != NULL){
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

/*
        3. PALINDROME LINKED LIST
    Given a singly linked list, determine if it is a palindrome.

    EX: 1->2, False
        1->2->2->1, True
    Algorithm:
        - Find the middle of the linked list using the slow and fast pointer technique.
        - Reverse the second half of the linked list.
        - Compare the first half with the reversed second half.
        - If the values in both halves are the same, then the linked list is a palindrome.
*/
bool isPalindrome(Node* head){
    if(head == NULL || head->next == NULL){
        return true;
    }

    //find the middle of the linked list
    Node* slow = head;
    Node* fast = head;

    while(fast != NULL || fast->next != NULL){
        slow = slow->next;
        fast = fast->next;
    }

    //reverse the second half
    Node* secHalf = reverseList(slow);
    Node* firstHalf = head;

    //compare first and second half
    while(secHalf != NULL){
        if(firstHalf->data != secHalf->data){
            return false;
        }
        firstHalf = firstHalf->next;
        secHalf = secHalf->next;
    }

    return true;
}

/*
        4. Linked List Cycle Detection
    - Given a linked list, determine if it has a cycle in it.
    - To represent a cycle in the given linked list, we use an integer pos which
        represents the position (0-indexed) in the linked list where tail connects to.
        pos is -1, then there is no cycle in the linked list.
    
    - Example 1:
        - Input: head = [3,2,0,-4], pos = 1
        - Output: true
        - Explanation: There is a cycle in the linked list, where tail connects to the second node.
    
    - Algorithm:
        - Initialize two pointers, slow and fast, both pointing to the head of the list.
        -  Move slow one step at a time and fast two steps at a time.
        -  If there is a cycle, slow and fast will meet at some point.
        -  If fast or fast->next becomes NULL, then the list does not have a cycle.

*/
bool hasCycle(Node* head){
    if (head == NULL) {
        return false;
    }

    Node* slow = head;
    Node* fast = head;

    while(fast != NULL || fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            return true;
    }

    return false;
}

/*
        LINKED LIST CYCLE DETECTION II
    Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

    Algorithm:
        - Use the slow and fast pointers to determine if there is a cycle.
        - If the fast pointer meets the slow pointer, there is a cycle.
        - Initialize a pointer at the head of the list and another at the meeting point.
        - Move both pointers one step at a time. The point where they meet is the start of the cycle.
*/
// Function to detect if there is a cycle and return the node where the cycle begins
Node* detectCycle(Node* head) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    Node* slow = head;
    Node* fast = head;

    // Detect cycle using the Tortoise and Hare algorithm
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            // Cycle detected, find the start of the cycle
            Node* entry = head;
            while (entry != slow) {
                entry = entry->next;
                slow = slow->next;
            }
            return entry;
        }
    }

    return NULL; // No cycle
}

/*
        GET INTERSECTION OF LINKED LIST
    Write a program to find the node at which the intersection of two singly linked lists begins.

    Algorithm:
    - Start two pointers, ptrA and ptrB, at the heads of the lists headA and headB.
    - Move both pointers forward one node at a time. If a pointer reaches the end of its list, 
            redirect it to the head of the other list.
    - If the lists intersect, the pointers will meet at the intersection node. If they don't intersect, 
        the pointers will both reach NULL.
*/

// Function to get the intersection node
Node* getIntersectionNode(Node* headA, Node* headB) {
    if (headA == NULL || headB == NULL) {
        return NULL;
    }

    Node* ptrA = headA;
    Node* ptrB = headB;

    while (ptrA != ptrB) {
        ptrA = (ptrA == NULL) ? headB : ptrA->next;
        ptrB = (ptrB == NULL) ? headA : ptrB->next;
    }

    return ptrA;
}

/*
        MERGING TWO LINKED LIST
    Merge two sorted linked lists and return it as a new list. The new list should be made 
    by splicing together the nodes of the first two lists.

    EX: 
    Input: 1->2->4, 1->3->4
    Output: 1->1->2->3->4->4

    ALGORITHM:

    - Create a dummy node to serve as the starting point for the merged list.
    - Set the tail pointer to the dummy node.
    - Use a while loop to traverse both lists simultaneously.
    - Compare the current nodes of both lists.
    - Append the smaller node to the new list.
    - Move the tail pointer to the newly added node.
    - After the loop, check if any nodes remain in either list.
    - Append the remaining nodes to the end of the merged list.
    - Return the new merged list starting from the node next to the dummy node (i.e., dummy.next)
*/
Node* mergeTwoLists(Node* l1, Node* l2) {
    // Create a dummy node to form the new sorted list
    Node dummy;
    Node* tail = &dummy;  // The tail of the new sorted list
    dummy.next = NULL;

    // Traverse both lists
    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;  // Append the node from l1
            l1 = l1->next;    // Move l1 to the next node
        } else {
            tail->next = l2;  // Append the node from l2
            l2 = l2->next;    // Move l2 to the next node
        }
        tail = tail->next;  // Move the tail to the last node
    }

    // If there are remaining nodes in either list, append them
    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next;  // The merged list starts from dummy.next
}
