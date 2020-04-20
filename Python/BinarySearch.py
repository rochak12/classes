
def binary_search(input_array, value):
    high = len(input_array)-1
    low = 0
    return try_recursive(input_array, value, high, low)


def try_recursive(input_array, value, high, low):
    global index
    central_index = int((low + high) / 2)
    centeral_value = input_array[central_index]
    # print(value, centeral_value)
    if value == centeral_value:
        return central_index
    elif high == low:
        return -1
    elif value > centeral_value:
        low = central_index + 1
    elif value < centeral_value:
        high = central_index - 1
    return try_recursive(input_array, value, high, low)

  # // when we have to return something from recursive function
  # // we have to return the value we get from recursive function
  # otherwise it will never know what value was return






test_list = [1,3,9,11,15,19,29]
test_val1 = 25
test_val2 = 15
print (binary_search(test_list, test_val1))
print (binary_search(test_list, test_val2))