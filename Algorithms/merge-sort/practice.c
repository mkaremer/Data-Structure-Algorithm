/* merge sort
    23  1  4  5   0 2 90
    1 23 4 5      0 2 90
    1 3 5 23
    l     m      r
    0 1 3 5 23 90
*/
void mergeLists(int* array, int left, int right, int mid){
    int sizeA = mid - left + 1;
    int sizeB = right - mid;

    int A[sizeA];
    int B[sizeB];

    for(int i = 0; i < sizeA; i++){
        A[i] = array[left + i];
    }

    for(int j = 0; j < sizeB; j++){
        B[j] = array[mid + 1 + j];
    }

    int j = 0;
    int i = 0;
    int k = left;

    while(i < sizeA && j < sizeB){
        if(A[i] <= B[j]){
            array[k] = A[i];
            i++;
        } else{
            A[k] = B[j];
            j++;
        }
        k++;
    }

    //any nums remaining
    while(i < sizeA){
        array[k] = A[i];
        i++;
        k++;
    }

     while(j < sizeB){
        arry[k] = B[j];
        j++;
        k++;
    }
}

void mergeSortRecur(int* array, int left, int right){
    if(left < right){
        int mid = left + (right - left) / 2;

        mergeSortRecur(&array, left, mid);
        mergeSortRecur(&array, mid + 1, right);
        mergeLists(&arry, left, right, mid);
    }
}

void mergeSort(int* arry, int size){
    mergeSortRecur(&array, 0, size - 1);
}

