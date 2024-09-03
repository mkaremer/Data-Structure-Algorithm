#merge sort in python
# Written by Moses K.
# l   m   r
# 1 2 3 4 6 

def merge(array, left, mid, right):
    sizeA = mid - left + 1
    sizeB = right - mid

    A = [sizeA]
    B = [sizeB]

    for i in range(sizeA):
        A[i] = array[left + i]
    
    for j in range(sizeB):
        B[j] = array[mid + 1 + j]
    
    i = 0
    j = 0
    k = left

    while i < sizeA and j < sizeB:
        if A[i] <= B[j]:
            array[k] = A[i]
            i += 1
        else:
            array[k] = B[j]
            j += 1
        k += 1
    
    while i < sizeA:
        array[k] = A[i]
        i += 1
        k += 1

    while j < sizeB:
        array[k] = B[j]
        j += 1
        k += 1


def mergeSort(array, left, right):
    if left < right:
        mid = left + right // 2
        mergeSort(array, left, mid)
        mergeSort(array, mid + 1, right)
        merge(array, left, mid, right)


# test the function
res = [23,2,45,0,12,5,6]
size = len(res)
print(mergeSort(res, 0, size - 1))