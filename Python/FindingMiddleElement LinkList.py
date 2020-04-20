class Node:
    def __init__(self, value):
        self.value = value
        self.pNext = None


class LinkedList:
    def __init__(self, node):
        self.pHead = node
        self.pNode = node
        self.pHead.pNext = None

    def add(self, value):
        node = Node(value)
        self.pNode.pNext = node
        self.pNode = node


node = Node(5)
lkst = LinkedList(node)
lkst.add(6)
lkst.add(7)
lkst.add(8)
lkst.add(9)
lkst.add(11)
lkst.add(12)
lkst.add(8)


Big = lkst.pHead
small = lkst.pHead
while Big.pNext and Big.pNext.pNext:
    if Big.pNext.pNext:
        Big = Big.pNext.pNext
    if small.pNext:
        small = small.pNext

if Big.pNext:
    print(small.pNext.value)
else:
    print(small.value)