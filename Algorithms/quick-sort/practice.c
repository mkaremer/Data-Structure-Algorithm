//quick sort
/*
    3 2 4 1 2
*/
void swap(int* a, int* b){
    int tmp = *a;
    a* = *b;
    *b = tmp;
}
int partition(int* nums, int left, int right){
    int pivot = nums[right];
    int low = left - 1;

    for(int i = low; i < right){
        if(nums[i] <= pivot){
            low++;
            swap(&nums[low], &nums[i]);
        }
    }
    swap(&nums[right], &nums[low + 1]);

    return low + 1;
}

void quickSort(int* nums, int left, int right){
    if(left < right){
        int pi = partition(nums, left, right);

        quickSort(nums, left, pi - 1);
        quickSort(nums, pi + 1, right);
    }  

}