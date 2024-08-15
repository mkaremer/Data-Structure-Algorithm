/* Binary search in C language*/

+
//recursive

int binary_search_recu(int* nums, int left, int right, int target){
    //base case
    if(left > right){
        return -1;
    }
    
    int mid = left + right / 2;

    if (nums[mid] == target){
        return mid;
    }

    if(nums[mid] < target){
        return binary_search_recu(nums, mid + 1, right);
    } else{
        return binary_search_recu(nums, left, mid - 1);
    }
}

//iterative
int binary_search_iter(int* nums, int numSize, int target){
    int left = 0;
    int right = numSize - 1;

    while(left <= right){
        int mid = left + right / 2;

        if(nums[mid] == target){
            return mid;
        }

        if(nums[mid] < target){
            left = mid + 1;
        } else{
            right = mid - 1;
        }
    }

    return -1;
}