from typing import Tuple


class BplusNode:

    d = 2

    def __init__(self, is_leaf: bool):
        self.keys: list[int] = []
        self.pointers: list["BplusNode"] = []
        self.is_leaf: bool = is_leaf
        self.next_leaf: BplusNode | None = None
        self.parent: BplusNode | None = None

    @staticmethod
    def append_key(node: "BplusNode", key: int, right_ptr: "BplusNode" = None):
        if node.is_leaf:
            i = 0
            while i < len(node.keys) and key > node.keys[i]:
                i += 1
            node.keys.insert(i, key)

            if len(node.keys) != 2 * BplusNode.d + 1:
                return None
            else:
                new_node = BplusNode(True)
                new_node.parent = node.parent
                node.next_leaf = new_node
                middle_key = node.keys[2 * BplusNode.d // 2]
                new_node.keys = node.keys[2 * BplusNode.d // 2: ]
                node.keys = node.keys[0: 2 * BplusNode.d // 2]
                node = node.parent
                return BplusNode.append_key(node, middle_key, new_node)
        else:
            i = 0
            while i < len(node.keys) and key > node.keys[i]:
                i += 1
            node.keys.insert(i, key)
            node.pointers.insert(i + 1, right_ptr)
            if i + 2 <= len(node.pointers) - 1:
                right_ptr.next_leaf = node.pointers[i + 2]
            if len(node.keys) != 2 * BplusNode.d + 1:
                return None
            else:
                new_node = BplusNode(False)
                new_node.parent = node.parent

                middle_key = node.keys[2 * BplusNode.d // 2]
                new_node.keys = node.keys[2 * BplusNode.d // 2 + 1: ]
                new_node.pointers = node.pointers[2 * BplusNode.d // 2 + 1:]
                node.keys = node.keys[0: 2 * BplusNode.d // 2]
                node.pointers = node.pointers[: 2 * BplusNode.d // 2 + 1]

                if node.parent is None:
                    node.parent = BplusNode(False)
                    new_node.parent = node.parent
                    node.parent.keys.append(middle_key)
                    node.parent.pointers.append(node)
                    node.parent.pointers.append(new_node)
                    return node.parent
                else:
                    node = node.parent
                    BplusNode.append_key(node, middle_key, node, new_node)
                    return None
    def __repr__(self):
        return f'{self.keys}'
                

class BplusTree:

    def __init__(self):
        self.root = BplusNode(False)

    def find(self, key) -> Tuple[BplusNode, bool] | Tuple[None, BplusNode]:
        prev = None
        temp = self.root
        while temp and not temp.is_leaf:
            prev = temp
            for i, node_key in enumerate(temp.keys):
                if key < node_key:
                    temp = temp.pointers[i]
                    break
            else:
                temp = temp.pointers[-1]
        if temp is None:
            return temp, prev 
        for node_key in temp.keys:
            if node_key == key:
                return temp, True
        return temp, False
            
    def insert(self, key) -> bool:
        if len(self.root.keys) == 0:
            self.root.keys.append(key + 1)
            self.root.pointers.append(BplusNode(True))
            self.root.pointers[0].keys.append(key)
            self.root.pointers[0].parent = self.root
            self.root.pointers.append(BplusNode(True))
            self.root.pointers[1].parent = self.root
            return

        leaf_node, exists = self.find(key)
        if leaf_node is None:
            exists.pointers.append(BplusNode(True))
            exists.pointers[-1].key = key
        
        if exists:
            return False

        new_root = leaf_node.append_key(leaf_node, key)
        if new_root is not None:
            self.root = new_root
        return True
    
    def print_tree(self):
        
        stack = []
        stack.append(self.root)
        while stack:
            temp = stack.pop()
            for key in temp.keys:
                print(key, end=' ')
            print('')
            for u in temp.pointers:
                stack.append(u)


if __name__ == "__main__":
    tree = BplusTree()

    tree.insert(24)
    tree.insert(17)
    tree.insert(16)
    tree.insert(12)
    tree.insert(25)
    tree.insert(35)
    
    tree.insert(5)
    tree.insert(40)
    tree.insert(55)
    tree.insert(62)
    tree.insert(65)
    tree.insert(80)

    tree.insert(85)

    tree.insert(88)

    temp, _ = tree.find(5)
    while temp:
        for key in temp.keys:
            print(key)
        temp = temp.next_leaf

