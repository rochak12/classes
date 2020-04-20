#stringg = "hcbhbf,dhbd,hbdjbd,dbj"
stringg = input("Enter a string")
for strr in reversed(range(len(stringg))):
    print(stringg[strr] , end="")

print()


list = stringg.split(",")
for bit in reversed(range(len(list))):
    print ((list[bit]) , end=" ")
print(list)