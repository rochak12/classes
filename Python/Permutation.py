def permutation(word, low, high):
    if low == high:
        print( " ".join(word))
    else:
        for i in range(low, high + 1):
            word[i], word[low] = word[low], word[i]
            permutation(word, low + 1, high)
            word[i], word[low] = word[low], word[i]


a = "ABC"
a = list(a)
permutation(a, 0, len(a) - 1)
