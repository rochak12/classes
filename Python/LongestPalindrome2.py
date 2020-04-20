def checkPalindrome(a, table=None):
    table = [['' for i in range(len(a))] for i in range(len(a))]
    maxLength = 0

    for i in (range(len(a))):
        table[i][i] = True

    for i in range(len(a) - 1):
        if a[i] == a[i + 1]:
            table[i][i + 1] = True

    k = 3
    while k <= len(a):
        for j in range(0, len(a) - k):
            if a[j] == a[j + k - 1] and table[j + 1][j + k - 1 - 1]:
                table[j][j + k - 1] = True

                if k > maxLength:
                    maxLength = k
                    print(str(a[j:j + k]))

        k += 1


a = "Iammapalindromeemordnila"
checkPalindrome(a)
