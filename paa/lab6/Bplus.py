from typing import Tuple
import os


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
                for pointer in new_node.pointers:
                    pointer.parent = new_node
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
                    return BplusNode.append_key(node, middle_key, new_node)
    
    @staticmethod
    def remove_key(node: "BplusNode", key: int, deleted_node: "BplusNode" = None):
        if node.is_leaf:
            node.keys.remove(key)
            if len(node.keys) < BplusNode.d:
                if node.next_leaf and node.prev_leaf and node.next_leaf.parent == node.prev_leaf.parent:
                    sibling_node = node.next_leaf if len(node.next_leaf.keys) > len(node.prev_leaf.keys) else node.prev_leaf
                else:
                    sibling_node = node.next_leaf if node.next_leaf and node.next_leaf.parent is node.parent else node.prev_leaf
                node1 = node if node.next_leaf is sibling_node else sibling_node
                node2 = node if node.prev_leaf is sibling_node else sibling_node
                if len(sibling_node.keys) == BplusNode.d:
                    node2.keys = node1.keys + node2.keys
                    if node1.prev_leaf:
                        node1.prev_leaf.next_leaf = node2
                    node2.prev_leaf = node1.prev_leaf
                    return BplusNode.remove_key(node2.parent, 0, node1)

                else:
                    keys = node1.keys + node2.keys
                    node1.keys = keys[:len(keys) // 2] 
                    node2.keys = keys[len(keys) // 2:]
                    node2.parent.keys[node2.parent.pointers.index(node1)] = node2.keys[0]
            return None
        else:
            if node.parent is None:
                if len(node.keys) == 1:
                    node.pointers.remove(deleted_node)
                    node.pointers[0].parent = None
                    return node.pointers[0]
                else:
                    idx = node.pointers.index(deleted_node)
                    if idx == len(node.pointers) - 1:
                        node.keys.pop(idx - 1)
                    elif idx == 0:
                        node.keys.pop(idx)
                    elif node.pointers[idx - 1].keys[-1] > node.keys[idx - 1]:
                        node.keys.pop(idx - 1)
                    else:
                        node.keys.pop(idx)
                    node.pointers.remove(deleted_node)   
                    return None 
            idx = node.pointers.index(deleted_node)
            if idx == len(node.pointers) - 1:
                node.keys.pop(idx - 1)
            elif idx == 0:
                node.keys.pop(idx)
            elif node.pointers[idx - 1].keys[-1] > node.keys[idx - 1]:
                node.keys.pop(idx - 1)
            else:
                node.keys.pop(idx)
            node.pointers.remove(deleted_node)
            if len(node.keys) < BplusNode.d and node.parent:
                par_idx = node.parent.pointers.index(node)
                sibling_node1 = node.parent.pointers[par_idx - 1] if par_idx > 0 else None
                sibling_node2 = node.parent.pointers[par_idx + 1] if par_idx < len(node.parent.pointers) - 1 else None
                if (sibling_node1 and len(sibling_node1.keys) > BplusNode.d):
                    # if len(sibling_node1.keys) == BplusNode.d + 1:
                    keys = sibling_node1.keys + [node.parent.keys[par_idx - 1] + 1] + node.keys
                    node.keys = keys[-BplusNode.d:]
                    node.parent.keys[par_idx - 1] = keys[-BplusNode.d - 1]
                    sibling_node1.keys = keys[:-BplusNode.d - 1]
                    node.pointers.insert(0, sibling_node1.pointers[-1])
                    node.pointers[0].parent = node
                    sibling_node1.pointers.pop()
                    # else:
                    #     keys = sibling_node1.keys + node.keys
                    #     node.keys = keys[-BplusNode.d:]
                    #     sibling_node1.keys = keys[:-BplusNode.d]
                    #     node.pointers.insert(0, sibling_node1.pointers[-1])
                    #     node.pointers[0].parent = node
                    #     sibling_node1.pointers.pop()                        

                elif (sibling_node2 and len(sibling_node2.keys) > BplusNode.d):
                    keys = node.keys + [node.parent.keys[par_idx] + 1] + sibling_node2.keys
                    node.keys = keys[:BplusNode.d]
                    node.parent.keys[par_idx] = keys[BplusNode.d]
                    sibling_node2.keys = keys[BplusNode.d + 1:]
                    node.pointers.append(sibling_node2.pointers[0])
                    node.pointers[-1].parent = node
                    sibling_node2.pointers.pop(0)
                else:
                    if sibling_node1:
                        sibling_node1.keys.extend([node.parent.keys[par_idx - 1]] + node.keys)
                        sibling_node1.pointers.extend(node.pointers)
                        for pointer in node.pointers:
                            pointer.parent = sibling_node1
                        return BplusNode.remove_key(node.parent, 0, node)
                    else:
                        node.keys.extend([node.parent.keys[par_idx]] + sibling_node2.keys)
                        node.pointers.extend(sibling_node2.pointers)
                        for pointer in sibling_node2.pointers:
                            pointer.parent = node
                        return BplusNode.remove_key(node.parent, 0, sibling_node2)
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
        
        if len(self.root.pointers[0].keys) + len(self.root.pointers[1].keys) == 2 * BplusNode.d and self.root.pointers[0].is_leaf and len(self.root.pointers[0].keys) == 1:
            self.root.pointers[0].keys.extend(self.root.pointers[1].keys[0:BplusNode.d])
            self.root.pointers[1].keys = self.root.pointers[1].keys[BplusNode.d:]
            self.root.keys[0] = self.root.pointers[1].keys[0]

        return True
    
    def remove(self, key) -> bool:
        leaf_node, exists = self.find(key)
        if not exists:
            return False
        
        new_root = BplusNode.remove_key(leaf_node, key)
        if new_root:
            self.root = new_root
        return True


def tabelar_view(N, d, time1, time2):
    N_space = 9
    D_space = 9
    time_space = 10
    time1 = str(time1)[:7]
    time2 = str(time2)[:7]
    horizontal_line = " _________________________________________________\n"
    if not os.path.exists("report.txt"):
        with open("report.txt", "w") as f:
            f.write(horizontal_line)
            f.write("|     N     |     K     | Add/Remove |    Find    |\n")
        return 
    
    with open("report.txt", "a") as f:
        f.write(horizontal_line)

        str_to_write = ""

        str_to_write += f'| {" " * ((N_space - len(str(N))) // 2)}{N}'\
                        f'{" " * (N_space - len(str(N)) - (N_space - len(str(N))) // 2)} '
        
        str_to_write += f'| {" " * ((D_space - len(str(d))) // 2)}{d}'\
                        f'{" " * (D_space - len(str(d)) - (D_space - len(str(d))) // 2)} '

        str_to_write += f'| {" " * ((time_space - len(time1)) // 2)}{time1}'\
                        f'{" " * (time_space - len(time1) - (time_space - len(time1)) // 2)} '
        
        str_to_write += f'| {" " * ((time_space - len(time2)) // 2)}{time2}'\
                        f'{" " * (time_space - len(time2) - (time_space - len(time2)) // 2)} '            

        str_to_write += "|\n"

        f.write(str_to_write)


if __name__ == "__main__":
    import time
    import random
    from BinomialHeap import BinomialHeap


    Ns = [100, 1000, 10_000, 100_000, 1_000_000]
    Ds = [3, 5, 10, 33, 101, 333, 1001] 

    for N in Ns:
        for d in Ds:
            try:
                BplusNode.d = d
                tree = BplusTree()
                hip = BinomialHeap()

                start_time = time.perf_counter()
                for i in range(N):
                    tree.insert(i)
                
                removed = 0
                while removed < N // 10:
                    rem_success = tree.remove(random.randint(0, N - 1))
                    removed += 1
                end_time = time.perf_counter()

                for i in range(N):
                    hip.insert(i)

                X = 3 * N // 5
                razlika = []
                
                start = time.perf_counter()
                for i in range(X):
                    maxi = hip.extract_max()
                    found = tree.find(maxi)
                    if found[1] == False:
                        razlika.append(maxi)
                end = time.perf_counter()

                tabelar_view(N, d, end_time - start_time, end - start)
            except:
                tabelar_view(N, d, 000.00, 000.00)
