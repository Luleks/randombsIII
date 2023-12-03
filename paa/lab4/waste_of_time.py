from collections import defaultdict

class HeapNode:
    def __init__(self, key: int, degree: int, parent: "HeapNode", child: "HeapNode", right_sibling: "HeapNode", left_sibling: "HeapNode"):
        self.key = key
        self.degree = degree
        self.parent = parent
        self.child = child
        self.right_sibling = right_sibling
        self.left_sibling = left_sibling

    @staticmethod
    def binomial_link(node1:"HeapNode", node2: "HeapNode", new_node: "HeapNode"=None) -> "HeapNode":           
        if new_node:
            if new_node is node1:
                node1, node2 = node2, node1

            node1.key, node2.key = min(node1.key, node2.key), max(node1.key, node2.key)
            main = node1
            child = node2
        
        else:
            if node1.key < node2.key:
                main, child = node1, node2
            else:
                main, child = node2, node1

            if child.left_sibling:
                child.left_sibling.right_sibling = child.right_sibling
            if child.right_sibling:
                child.right_sibling.left_sibling = child.left_sibling

        child.parent = main
        child.left_sibling = None
        child.right_sibling = main.child
        main.child = child
        main.degree += 1
        return main, child
    
    def __repr__(self) -> str:
        return f'{self.key}'
    def __str__(self) -> str:
        return f'Key: {self.key} LeftSibling: {self.left_sibling.key if self.left_sibling is not None else None} RightSibling: {self.right_sibling.key if self.right_sibling is not None else None} Parent: {self.parent.key if self.parent is not None else None} Child: {self.child.key if self.child is not None else None} Degree: {self.degree}'

class BinomialHeap:
    def __init__(self):
        self.head = None
        self.degrees = defaultdict()

    def find_min(self) -> HeapNode | None:
        return self.head if self.head else None

    def swap_adjacent_nodes(self, node1: HeapNode, node2: HeapNode):
        if node1 is self.head:
            self.head = node2
            
        if node1.left_sibling:
            node1.left_sibling.right_sibling = node2
        if node2.right_sibling:
            node2.right_sibling.left_sibling = node1

        node1.right_sibling, node2.right_sibling = node2.right_sibling, node1
        node1.left_sibling, node2.left_sibling = node2, node1.left_sibling

    def insert(self, val):
        if not self.head:
            self.head = HeapNode(val, 0, None, None, None, None)
            self.degrees[self.head.degree] = self.head
            return

        if val < self.head.key:
            new_node = HeapNode(self.head.key, 0, None, None, None, None)
            self.head.key = val
        else:
            new_node = HeapNode(val, 0, None, None, None, None)
        
        root_list_node = self.degrees.get(new_node.degree)
        if root_list_node is None:
            self.degrees[new_node.degree] = new_node
            prev, temp = None, self.head
            while temp and temp.key <= val:
                prev = temp
                temp = temp.right_sibling
            if prev:
                prev.right_sibling = new_node
            new_node.right_sibling = temp
            if temp:
                temp.left_sibling = new_node
            new_node.left_sibling = prev
        else:
            self.degrees.pop(root_list_node.degree)
            new_node, root_list_node = HeapNode.binomial_link(root_list_node, new_node, new_node)
            while new_node.degree in self.degrees:
                root_list_node = self.degrees.get(new_node.degree)
                new_node, root_list_node = HeapNode.binomial_link(root_list_node, new_node)
                self.degrees.pop(root_list_node.degree)
            self.degrees[new_node.degree] = new_node
            while new_node.left_sibling and new_node.key < new_node.left_sibling.key:
                self.swap_adjacent_nodes(new_node.left_sibling, new_node)

    def extract_min(self):
        if self.head is None:
            return None

        min_node = self.head
        children_representative = min_node.child
        self.head = self.head.right_sibling
        if self.head:
            self.head.left_sibling = None
        else:
            self.head = children_representative
            if self.head is None:
                return min_node.key
            next_child = children_representative.right_sibling
            children_representative.right_sibling = None
            children_representative.parent = None
            self.degrees[children_representative.degree] = self.head
            children_representative = next_child
        self.degrees.pop(min_node.degree)

        while children_representative:
            next_child = children_representative.right_sibling
            children_representative.right_sibling = None
            children_representative.parent = None

            root_list_node = self.degrees.get(children_representative.degree)
            if root_list_node is None:
                self.degrees[children_representative.degree] = children_representative
                prev, temp = None, self.head
                while temp and temp.key <= children_representative.key:
                    prev = temp
                    temp = temp.right_sibling
                if prev:
                    prev.right_sibling = children_representative
                else:
                    self.head.left_sibling = children_representative
                    self.head = children_representative
                children_representative.right_sibling = temp
                children_representative.left_sibling = prev
                if temp:
                    temp.left_sibling = children_representative
            else:
                tmp = self.head.right_sibling
                self.degrees.pop(root_list_node.degree)
                children_representative, root_list_node = HeapNode.binomial_link(root_list_node, children_representative, children_representative)
                if root_list_node is self.head:
                    self.head = children_representative
                    if self.head.left_sibling:
                        self.head.left_sibling.right = self.head.right_sibling
                    self.head.right_sibling = tmp
                while children_representative.degree in self.degrees:
                    tmp = self.head.right_sibling
                    root_list_node = self.degrees.get(children_representative.degree)
                    children_representative, root_list_node = HeapNode.binomial_link(root_list_node, children_representative)
                    if root_list_node is self.head:
                        self.head = children_representative
                        if self.head.left_sibling:
                            self.head.left_sibling.right_sibling = self.head.right_sibling
                        self.head.right_sibling = tmp
                        self.head.left_sibling = None
                        if self.head.right_sibling:
                            self.head.right_sibling.left_sibling = self.head
                    self.degrees.pop(root_list_node.degree)
                self.degrees[children_representative.degree] = children_representative
                while children_representative.left_sibling and children_representative.key < children_representative.left_sibling.key:
                    self.swap_adjacent_nodes(children_representative.left_sibling, children_representative)

            children_representative = next_child
        
        return min_node.key

    def print_heap(self):

        def print_heap(node, depth=0):
            if node is None:
                return
            print(node)
            print_heap(node.child, depth + 1)
            print_heap(node.right_sibling, depth)
        
        return print_heap(self.head)



if __name__ == "__main__":
    import heapq
    import random
    import time

    # data = [16,11,10,15,13,9,2,3,12,14]

    # heap = BinomialHeap()

    # for i in range(10):
    #     heap.insert(data[i])
    #     heap.print_heap()

    # heap.print_heap()
    # print(heap.extract_min())

    # print('-' * 20)
    # heap.print_heap()
    # for i in range(10):
    #     if i == 9:
    #         pass
    #     print(heap.extract_min())
    #     heap.print_heap()
    #     print("-" * 20)

    Ns = [1000, 10_000, 100_000]
    Ks = [10, 100]


    size_space = 8
    binomial_heap_size = 14
    binary_heap_size = 12
    correctness_size = 13
    k_size = 7
    horizontal_line = " ____________________________________________________________________ \n"
    with open("report1.txt", "w") as f:
        f.write(
            horizontal_line
        )
        f.write(
            "|   size   |    K    |  BinomialHeap  |  BinaryHeap  |  Correctness  |\n"
        )

    for N in Ns:
        for k in Ks:
            skup = [random.randint(0, 10_000) for _ in range(N)]
            binomial_heap = BinomialHeap()
            start_time_binomial = time.perf_counter()

            for i, val in enumerate(skup):
                binomial_heap.insert(val)
                if i % k == 0:
                    binomial_heap.extract_min()
            
            end_time_binomial = time.perf_counter()

            start_time_binary = time.perf_counter()
            
            binary_heap = []
            for i, val in enumerate(skup):
                heapq.heappush(binary_heap, val)
                if i % k == 0:
                    heapq.heappop(binary_heap)

            end_time_binary = time.perf_counter()

            heap_correct = True
            while binary_heap and heap_correct:
                if heapq.heappop(binary_heap) != binomial_heap.extract_min():
                    heap_correct = False

            total_time_binomial = round(end_time_binomial - start_time_binomial, 2)
            total_time_binary = round(end_time_binary - start_time_binary, 2)

            with open("report1.txt", "a+") as f:
                f.write(horizontal_line)

                str_to_write = ""

                str_to_write += f'| {" " * ((size_space - len(str(N))) // 2)}{N}'\
                                f'{" " * (size_space - len(str(N)) - (size_space - len(str(N))) // 2)} '
                
                str_to_write += f'| {" " * ((k_size - len(str(k))) // 2)}{k}'\
                                f'{" " * (k_size - len(str(k)) - (k_size - len(str(k))) // 2)} '
                
                str_to_write += f'| {" " * ((binomial_heap_size - len(str(total_time_binomial))) // 2)}{total_time_binomial}'\
                                f'{" " * (binomial_heap_size - len(str(total_time_binomial)) - (binomial_heap_size - len(str(total_time_binomial))) // 2)} '
                
                str_to_write += f'| {" " * ((binary_heap_size - len(str(total_time_binary))) // 2)}{total_time_binary}'\
                                f'{" " * (binary_heap_size - len(str(total_time_binary)) - (binary_heap_size - len(str(total_time_binary))) // 2)} '

                correct = "Correct" if heap_correct else "Incorrect"
                str_to_write += f'| {" " * ((correctness_size - len(correct)) // 2)}{correct}'\
                                f'{" " * (correctness_size - len(correct) - (correctness_size - len(correct)) // 2)} '

                str_to_write += "|\n"

                f.write(str_to_write)
                
    with open("report1.txt", "a+") as f:
        f.write(horizontal_line)