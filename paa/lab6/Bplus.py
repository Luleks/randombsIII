from typing import Tuple


class BplusNode:

    d = 2

    def __init__(self, is_leaf: bool):
        self.keys: list[int] = []
        self.pointers: list["BplusNode"] = []
        self.is_leaf: bool = is_leaf
        self.next_leaf: BplusNode | None = None
        self.prev_leaf: BplusNode | None = None
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
                if node.next_leaf:
                    node.next_leaf.prev_leaf = new_node
                node.next_leaf = new_node
                new_node.prev_leaf = node
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
    
    @staticmethod
    def remove_key(node: "BplusNode", key: int, deleted_node: "BplusNode" = None):
        if node.is_leaf:
            node.keys.remove(key)
            if len(node.keys) < BplusNode.d:
                sibling_node = node.next_leaf if node.next_leaf and node.next_leaf.parent is node.parent else node.prev_leaf
                node1 = node if node.next_leaf is sibling_node else sibling_node
                node2 = node if node.prev_leaf is sibling_node else sibling_node
                if len(sibling_node) == BplusNode.d:
                    node2.keys = node1.keys + node2.keys
                    node2.prev_leaf = node1.prev_leaf
                    return BplusNode.remove_key(node2.parent, 0, node1)

                else:
                    keys = node.keys + sibling_node.keys
                    node1.keys = keys[:len(keys) // 2] 
                    node2.keys = keys[len(keys) // 2:]
            return None
        else:
            idx = node.pointers.index(deleted_node)
            keys.pop(idx)
            node.pointers.remove(deleted_node)
            if len(node.keys) < BplusNode.d and node.parent:
                par_idx = node.parent.pointers.index(node)
                sibling_node1 = node.parent.pointers[par_idx - 1] if par_idx > 0 else None
                sibling_node2 = node.parent.pointers[par_idx + 1] if par_idx < len(node.parent.pointers) - 1 else None
                if (sibling_node1 and len(sibling_node1.keys) > BplusNode.d):
                    keys = sibling_node1.keys + [node.parent.keys[idx - 1]] + node.keys
                    node.keys = keys[-BplusNode.d:]
                    node.parent.keys[idx - 1] = keys[-BplusNode.d - 1]
                    sibling_node1.keys[:-BplusNode.d - 1]
                    node.pointers.insert(0, sibling_node1.pointers[-1])
                    sibling_node1.pointers.pop()
                elif (sibling_node2 and len(sibling_node2.keys) > BplusNode.d):
                    keys = node.keys + [node.parent.keys[idx]] + sibling_node2.keys
                    node.keys = keys[:BplusNode.d]
                    node.parent.keys[idx] = keys[BplusNode.d]
                    sibling_node2.keys = keys[BplusNode.d + 1:]
                    node.pointers.append(sibling_node2.pointers[0])
                    sibling_node2.pointers.pop(0)
                else:
                    if sibling_node1:
                        pass
                    else:
                        pass

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
            self.root.pointers[0].next_leaf = self.root.pointers[1]
            self.root.pointers[1].prev_leaf = self.root.pointers[0]
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
    
    def remove(self, key) -> bool:
        leaf_node, exists = self.find(key)
        if not exists:
            return False
        
        BplusNode.remove_key(leaf_node, key)


    
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

    prev = None
    temp, _ = tree.find(5)
    while temp:
        prev = temp
        for key in temp.keys:
            print(key, end = ' ')
        print("|", end=' ')
        temp = temp.next_leaf
    print()
    while prev:
        for key in prev.keys:
            print(key, end=' ')
        print("|", end=' ')
        prev = prev.prev_leaf
    print()
