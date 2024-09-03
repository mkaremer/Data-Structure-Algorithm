#include <stdio.h>

// merge sort algorithm
/*
            How it workds
    - The array is recursively divided into 2 halves
    - Each half is then sorted recursively
    - the sorted halves are then merged back together

    Time & Space complexity:
        time: O(n log n)
        space: 
*/

//merge two subarrays 
void merge(int arr[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //create temp arrays
    int L[n1], R[n2];

    //copy data to temp arrays
    for(int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }

    for(int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    //merge them back int arr[left...righ]
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //copy the raiming elements of L[] if any
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    //copy the raiming elements of R[] if any
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right){
    if(left < right){
        //find the mid point
        int mid = left + (right - left) / 2;

        //sort the first and second half
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //merge the sorted halves
        merge(arr, left, mid, right);

    }
}
void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[] = {12,11,13,5,6,7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}