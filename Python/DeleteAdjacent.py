a = "geeeeekeeeektthshvshhhsvss"
b = list(a)
for i, j in enumerate(b):
    if i != len(b)-1 and j == b[i+1]:
            k = i+1
            while k != len(b)-1 and b[k] == b[k+1]:
                 k = k+1
            del b[i:k+1]
print ("".join(b))





