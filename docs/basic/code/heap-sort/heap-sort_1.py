# --8<-- [start:sort]
def sift_down(arr, start, end):
    # Compute the indices of the parent and child
    parent = int(start)
    child = int(parent * 2 + 1)
    while child <= end:  # compare only while the child index is in range
        # First compare the two children and pick the larger one
        if child + 1 <= end and arr[child] < arr[child + 1]:
            child += 1
        # If the parent is larger than the child, we are done; return
        if arr[parent] >= arr[child]:
            return
        else:  # otherwise swap parent and child, then compare the child with its children
            arr[parent], arr[child] = arr[child], arr[parent]
            parent = child
            child = int(parent * 2 + 1)


def heap_sort(arr, len):
    # Sift down from the parent of the last node to build the heap (heapify)
    i = (len - 2) // 2
    while i >= 0:
        sift_down(arr, i, len - 1)
        i -= 1
    # Swap the first element with the one just before the sorted part, then re-adjust the elements before it, until sorted
    i = len - 1
    while i > 0:
        arr[0], arr[i] = arr[i], arr[0]
        sift_down(arr, 0, i - 1)
        i -= 1


# --8<-- [end:sort]

if __name__ == "__main__":
    import sys

    data = list(map(int, sys.stdin.buffer.read().split()))
    a = data[1 : data[0] + 1]
    heap_sort(a, len(a))
    print(*a)
