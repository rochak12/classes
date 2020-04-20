class Node:
    def __init__(self, value):
        self.value = value
        self.pNext = None
        self.pBefore = None


class LinkedList:
    def __init__(self, node):
        self.pHead = node
        self.pNode = node
        self.pHead.pNext = None
        self.pHead.pBefore = None

    def add(self, value):
        node = Node(value)
        temp = self.pNode
        self.pNode.pNext = node
        self.pNode = node
        self.pNode.pBefore = temp

    def reverse(self):
        current = self.pHead
        prev = None
        next = current.pNext
        while current.pNext:
            current.pNext = prev
            prev = current
            current = next
            next = current.pNext
        current.pNext = prev
        self.pHead = current


node = Node(5)
lkst = LinkedList(node)
lkst.add(6)
lkst.add(7)
lkst.add(8)
lkst.add(9)
lkst.add(11)
lkst.add(12)
lkst.add(13)

'''Reversing single linked list'''
lkst.reverse()



'''reversing a linked list using doubly linked list. But it is not how we do'''
# last = lkst.pNode
# last2 = Node(last.value)
#
# new = LinkedList(last2)
# while last.pBefore:
#     print("adding ", last.pBefore.value)
#     new.add(last.pBefore.value)
#     last = last.pBefore
#

itr = lkst.pHead
while itr:
    print(itr.value)
    itr = itr.pNext


