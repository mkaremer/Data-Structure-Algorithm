/* quick sort in c*/
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int* nums, int low, int high){
    int i = low - 1;
    int pivot = nums[high];

    for(int j = low; j < high; j++){
        if(nums[j] <= pivot){
            i++;
            swap(&nums[i], &nums[j]);
        }
    }
    swap(&nums[high], &nums[i + 1]);
    
    return i + 1;
}

void quickSort(int* nums, int low, int high){
    if(low < high){
        int pi = partition(nums, low, high);
        quickSort(nums, low, pi - 1);
        quickSort(nums, pi + 1, high);
    }
}