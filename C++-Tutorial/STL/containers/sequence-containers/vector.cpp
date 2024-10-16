/*
                        VECTORS
   - vector is a dynamic array that can grow and shrink in size
   - unlike arrays which are of a fixed size, vectors can automatically
            resize when elements are added or removed
   - The elements are stored in contigous memory just like an array to allow random access
   - when the size limit is reached, typically capacity doubles
   - Vectors have efficient insertion and deletion at the end. This operations takes constant time
   - deletion and insertion at other position takes linear time
   

   VECTOR OPERATIONS
   1. push_back(): adds element at the end of a vector
   2. pop_back(): remove last element from the vector
   3. size(): returns number of elements in a vector
   4. empty(): checks whether vector is empty
   5. front(): returns ref to first element
   6. back(): returns ref to last element
   7. capacity(): returns total amount of allocated storage. it could be greater than the current size. 
   8. resize(): resizes vector to the specified number of elements
   9. clear(): removes
    all elements from the vector

   ACCESSING ELEMENTS

   - you can access elements just like arrays using [] operator
        - int num = numbers[1]
   - alternatively, you can also use at(), which performas bounds checking and throws an exception if the index is out of range.
        - int num = numbers.at(1) // safe access with bounds checking

    ITERATORS

    - iterators are used to traverse the vectors. there two ways for this:
        - Elemets in a range-based.
        - loop-based 
    
    - Begin and End: begin(), returns iterator to first element
                     end(), returns iterator to the position past the last element
    - range-based loop(C++11 and later): This simplifies the syntax and is much more readable

    for(int num: numbers){
        std::cout << num << endl;
    }

    CAPACITY AND MEMEORY MANAGEMENT
    
    - vectors manage memory dynamically. here are important memory related functions:
        - capacity(): returns amount of memory that has been allocated
        - reserve(): if you know number of elements in advance, you can use reserve() to pre-allocate memory, reducing
                        the need for frequent reallocations
                ex: numbers.reverse(100) // reserve space for 100 elements
        - shrink_to_fit(): this reduces the capacity of the match size, releasing unused memory
            ex: numbers.shrink_to_fit() //resuces capacity to size
    
    INSERTION AND DELETION AT ARBITRARY POSITIONS

    - use insert() and erase() functions to insert or delete elements at specific positions
        - insert(): inserts an element or multiple at a specified position
            ex: auto it = numbers.begin();
                numbers.insert(it + 1, 15);
        - erase(): removes an element from a specified pos or range of elements
            ex: numbers.erase(it + 1);
    
    PERFORMANCE AND CONSIDERATIONS

    - time complexity:
        - accessing elements: O(1) due to contigous storate
        - inserting or removing at the end: O(1)
        - inserting or removing elements at arbitrary positons: O(n) becuase all subsequent elements need to be shifted
    - Memory usage: vectord dynamically grown and shrink. however it is important to manage the capacity efficiently using:
        - reverve() or shring_to_fit() if memory is a concern.

*/
#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<int> vec = {1,2,3,4};

    //push_back() adds element at the back
    vec.push_back(90); 
    //pop_back() removes the last element
    vec.pop_back();
    //back() accesses the last element
    int bck = vec.back();
    cout << "Back element: " << bck << endl;
    //front() accesses the first element
    int frt = vec.front();
    cout << "Front element: " << frt << endl;
    //size()
    int len = vec.size();
    cout << "Size of the vector: " << len << endl;
    //clear()
    // vec.clear();
    //capacity()
    int cap = vec.capacity();
    cout << "vector capacity: " << cap << endl;

    //accessing elements: use [] or at(). at() checks outbounds and throws an exception if the index is out of range
    cout << " Access using [] " << vec[0] << endl;
    cout << " Access using at() " << vec.at(0) << endl;

    //checking out of bounds
    // cout << " Check outbounds: Access using [] " << vec[-1] << endl;
    // cout << " Check outbounds: Access using at() " << vec.at(-1) << endl;

    //iterators
    // use c for loop
    // for(int i = 0; i < len; i++){
    //     cout << vec[i] << " ";
    // }
    // cout << endl;

    //using begin() and end(): begin(): returns iterator to first element. end(): returns iterator to the pos past the last element
    // for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
    //     cout << *it << " ";
    // }
    // cout << endl;

    //using auto keyword
    // for(auto it = vec.begin(); it != vec.end(); ++it){
    //     cout << *it << " ";
    //     // cout << vec[it] << endl; this is wrong
    // }
    // cout << endl;

    //range-based loop c++11 and later
    // for(int num : vec){
    //     cout << num << endl;
    // }
    

    //insert(): insert element or multiple at a specified position
    auto it = vec.begin();
    vec.insert(it + 1, 78); //insert at pos 1
    // vec.insert(it + 2, {200, 800, 900}); //insert multiple elements
    vector<int> newNums = {200, 800, 900};
    vec.insert(it + 2, newNums.begin(), newNums.end());


    //erase(): removes an element from a specified position
    vec.erase(it + 1);
    
    for(int items: vec){
        cout << items << " ";
    }
    cout << "\n";

    return 0;
}
