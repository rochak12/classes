class Palindrome:
    bigsofar = 0
    bigword = 0, 0

    def __init__(self, a):
        self.a = a

    def checkPalindrome(self, i, j):
        str = ""
        for k in reversed(self.a[i: j]):
            str = str + k
            if self.a[i: j] == str:
                # print(self.a[i: j])
                if j - i > self.bigsofar:
                    self.bigsofar = j - i
                    self.bigword = i, j

    def palindrome(self):
        for i in range(0, len(self.a)):
            for j in range(0, len(self.a)):
                self.checkPalindrome (i, j)


a = Palindrome("palpaisnunsi")
a.palindrome()
print(str(a.a)[a.bigword[0]: a.bigword[1]])


