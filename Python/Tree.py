class Node(object):
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class BinaryTree(object):
    def __init__(self, root):
        self.root = Node(root)

    def search(self, find_val):
        return self.preorder_search(self.root, find_val)


    def print_tree(self):
        return self.preorder_print(tree.root, "")

    def preorder_search(self, start, find_val):
        current_node = start
        if start.value == find_val: return True
        if current_node.left:
            current_node = current_node.left
            return (self.preorder_search(current_node, find_val))
        if current_node.right:
            return (self.preorder_search(current_node.right, find_val))
        else:
            return False
        # if start:
        #     if start.value == find_val:
        #         return True
        #     else:
        #         return self.preorder_search(start.left, find_val) or self.preorder_search(start.right, find_val)
        # return False


    def preorder_print(self, start, traversal):
        if start:
            if len(traversal): traversal += "-"
            traversal = self.preorder_print(start.left, traversal)
            traversal = self.preorder_print(start.right, traversal)
        return traversal


# Set up tree
tree = BinaryTree(1)
tree.root.left = Node(2)
tree.root.right = Node(3)
tree.root.left.left = Node(4)
tree.root.left.right = Node(5)

# Test search
# Should be True
print (tree.search(4))
# Should be False
print (tree.search(6))

# Test print_tree
# Should be 1-2-4-5-3
print (tree.print_tree())