import  numpy as np

a = np.array([[2, 3, 4],
             [5, 6, 0],
             [0, 2, 4]])
print(a)


c = np.array([20, 17, 16])
b = np.dot(np.linalg.inv(a), c.transpose())
#b = np.linalg.inv(a)*c.transpose()
print(b, "done")

