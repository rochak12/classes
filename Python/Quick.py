"""Implement quick sort in Python.
Input a list.
Output a sorted list."""
def quicksort(array):
    pivot = len(array) - 1

    if len(array) == 1 or len(array) == 0: return array
    i = 0
    t = True
    while True: #i <= pivot:
        if array[i] > array[pivot]:
            temp = array[pivot]
            array[pivot] = array[i]
            array[i] = array[pivot-1]
            array[pivot-1] = temp
            pivot -= 1

        elif array[i] < array[pivot]:
            i += 1
        elif array[i] == array[pivot]:
            return quicksort(array[0:pivot]) + [array[pivot]] + quicksort((array[pivot + 1:len(array)]))


test = [21, 4, 1, 3, 9, 20, 25, 6, 21, 14]
print (quicksort(test))


