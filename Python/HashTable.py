class HashTable(object):
    def __init__(self):
        self.table = [None] * 10000
        #print(self.table)

    def store(self, string):
        index = self.calculate_hash_value(string)
        self.table[index] = string


    def lookup(self, string):
        index = self.calculate_hash_value(string)
        if self.table[index]:
            return index
        else:
            return -1

    def calculate_hash_value(self, string):
        self.string = string
        #i = f'{ord(string[0])}{ord(string[1])}'
        j = '%i%i' %(ord(string[0]), ord(string[1]))
        #print(type(j))
        return int(j)


# Setup
hash_table = HashTable()

# Test calculate_hash_value
# Should be 8568
print(hash_table.calculate_hash_value('UDACITY'))

# Test lookup edge case
# Should be -1
print(hash_table.lookup('UDACITY'))

# Test store
hash_table.store('UDACITY')
# Should be 8568
print(hash_table.lookup('UDACITY'))

# Test store edge case
hash_table.store('UDACIOUS')
# Should be 8568
print(hash_table.lookup('UDACIOUS'))
