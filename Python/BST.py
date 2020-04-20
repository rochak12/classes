class Node(object):
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


class BST(object):
    def __init__(self, root):
        self.root = Node(root)

    def insert(self, new_val):
        self.insert_help(self.root, new_val)

    def search(self, find_val):
        return self.search_help(self.root, find_val)

    def insert_help(self, current_node, new_val):
        if current_node.value  == new_val: pass
        if current_node.value > new_val:
            if not current_node.left: current_node.left = Node(new_val)
            else:
                self.insert_help(current_node.left, new_val)
        else:
            if not current_node.right: current_node.right = Node(new_val)
            else:self.insert_help(current_node.right, new_val)

    def search_help(self, current_node, find_val):
        if current_node:
            if current_node.value == find_val:
                return True
            elif current_node.value > find_val:
                return self.search_help(current_node.left, find_val)
            else:
                return self.search_help(current_node.right, find_val)
        return False


# Set up tree
tree = BST(4)

# Insert elements
tree.insert(2)
tree.insert(1)
tree.insert(3)
tree.insert(5)


# Check search
# Should be True
print(tree.search(4))
# Should be False
print(tree.search(6))