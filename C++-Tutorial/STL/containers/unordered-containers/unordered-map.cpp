/*
            UNORDERED MAP
    - KEY FEATURES
        - Unique Keys: Each key in an unordered_map is unique. If you try to add a key that already exists, 
            it will replace the old value with the new one. 
        - Hash Table: The unordered_map uses a hash table, so the keys are not stored in any specific order. 
            This makes finding, adding, and deleting items very fast.
        - Time Complexity: In most cases, adding, removing, or finding elements takes constant time O(1).
              But in rare cases, when there are many hash collisions, it can take longer O(n)  

    - OPERATIONS ON UMAP
        insert(): Inserts key-value pairs.
        find(): Searches for an element by key.
        at(): Accesses the value associated with a key, with bounds checking.
        erase(): Removes an element by key or iterator.
        count(): Returns the number of occurrences of a key (always 0 or 1).
        size(): Returns the number of elements in the unordered_map.
        empty(): Checks if the unordered_map is empty.
        clear(): Removes all elements from the unordered_map.
        begin() and end(): Returns iterators to the beginning and end of the unordered_map.   
*/
#include <unordered_map>
#include <iostream>

using namespace std;

int main(){
    unordered_map<string, int> student_scores;


    //insert key-value pairs
    student_scores["Alice"] = 85;
    student_scores["Bob"] = 90;
    student_scores["Charlie"] = 75;

    //accessing values
    cout << "Alice's score: " << student_scores["Alice"] << endl;

    //checking if a key exists
    if(student_scores.count("Bob") > 0){
        cout << "Bob's score: " << student_scores["Moses"] << endl;
    }



    return 0;
}