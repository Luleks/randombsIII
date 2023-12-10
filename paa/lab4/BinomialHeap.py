class HeapNode:
    def __init__(self, key: int, degree: int, parent: "HeapNode", child: "HeapNode", sibling: "HeapNode"):
        self.key = key
        self.degree = degree
        self.parent = parent
        self.child = child
        self.sibling = sibling

    @staticmethod
    def binomial_link(node1:"HeapNode", node2: "HeapNode") -> bool:
        if node1 is None or node2 is None:
            return False
        node1.parent = node2
        node1.sibling = node2.child
        node2.child = node1
        node2.degree += 1
        return True
    
    def __repr__(self) -> str:
        return str(self.key)


class BinomialHeap:
    def __init__(self):
        self.head: HeapNode | None = None

    def find_max(self) -> HeapNode | None:
        if self.head is None:
            return None
        elif self.head.sibling is None:
            return self.head
        min_node = self.head
        temp = self.head.sibling
        while temp:
            if temp.key > min_node.key:
                min_node = temp
            temp = temp.sibling
        return min_node
    
    @staticmethod
    def merge(heap1: "BinomialHeap", heap2: "BinomialHeap") -> "BinomialHeap":
        if heap1.head is None:
            return heap2
        elif heap2.head is None:
            return heap1
        elif heap1.head.degree > heap2.head.degree:
            heap1, heap2 = heap2, heap1
    
        heap = BinomialHeap()
        temp1, temp2 = heap1.head.sibling, heap2.head
        heap.head = heap1.head
        heap_temp = heap.head
        while temp1 and temp2:
            if temp1.degree <= temp2.degree:
                heap_temp.sibling = temp1
                temp1 = temp1.sibling
            else:
                heap_temp.sibling = temp2
                temp2 = temp2.sibling
            heap_temp = heap_temp.sibling
        heap_temp.sibling = temp1 or temp2
        return heap

    @staticmethod
    def union(heap1: "BinomialHeap", heap2: "BinomialHeap"):
        heap = BinomialHeap.merge(heap1, heap2)
        if heap.head is None:
            return heap
        BinomialHeap.unite(heap, None, heap.head, heap.head.sibling)

        return heap
    
    @staticmethod
    def unite(heap: "BinomialHeap", prev: HeapNode, temp: HeapNode, next: HeapNode):
        while next:
            if temp.degree != next.degree or (next.sibling is not None and next.sibling.degree == temp.degree):
                prev, temp = temp, next
            elif temp.key >= next.key:
                temp.sibling = next.sibling
                HeapNode.binomial_link(next, temp)
            else:
                if prev:
                    prev.sibling = next
                else:
                    heap.head = next    
                HeapNode.binomial_link(temp, next)
                temp = next
            next = temp.sibling      
    
    def insert(self, val):
        self.head = HeapNode(val, 0, None, None, self.head)
        BinomialHeap.unite(self, None, self.head, self.head.sibling)

    def print_heap(self):

        def print_heap(node, depth=0):
            if node is None:
                return
            print("  " * depth, f"Key: {node.key}, Degree: {node.degree}")
            print_heap(node.child, depth + 1)
            print_heap(node.sibling, depth)
        
        return print_heap(self.head)
    
    def extract_max(self):
        if self.head is None:
            return None
        prev_min, min_node = None, self.head
        prev, temp = self.head, self.head.sibling

        while temp != None:
            if temp.key > min_node.key:
                min_node = temp
                prev_min = prev
            prev = temp
            temp = temp.sibling
        
        if prev_min is None:
            self.head = min_node.sibling
        else:
            prev_min.sibling = min_node.sibling
        min_node.sibling = None

        heap = BinomialHeap()
        prev, child, next = None, min_node.child, None
        while child:
            child.parent = None
            next = child.sibling
            child.sibling = prev
            prev = child
            child = next
        heap.head = prev
        new_heap = BinomialHeap.union(self, heap)
        self.head = new_heap.head
        return min_node.key

    def find_node(self, key: int) -> HeapNode | None:
        if self.head is None:
            return None
        
        temp = self.head
        stack = [temp]
        while stack:
            temp = stack.pop()
            if temp.key == key:
                return temp
            if temp.sibling:
                stack.append(temp.sibling)
            if temp.child is not None:
                stack.append(temp.child)

        if temp and temp.key == key:
            return temp
        return None

    def increase_key(self, node: HeapNode, k: int) -> bool:
        if k < node.key:
            return False
        node.key = k
        temp, par = node, node.parent
        while par and temp.key > par.key:
            temp.key, par.key = par.key, temp.key
            temp, par = par, par.parent
        return True

    def delete_key(self, key: int) -> bool:
        if node := self.find_node(key):
            self.increase_key(node, float("infinity"))
            self.extract_max()
            return True
        return False


if __name__ == "__main__":
    import heapq
    import random
    import time
    
    Ns = [1000, 10_000, 100_000, 1_000_000, 10_000_000]
    Ks = [10, 100]


    size_space = 8
    binomial_heap_size = 14
    binary_heap_size = 12
    correctness_size = 13
    k_size = 7
    horizontal_line = " ____________________________________________________________________ \n"
    with open("report.txt", "w") as f:
        f.write(
            horizontal_line
        )
        f.write(
            "|   size   |    K    |  BinomialHeap  |  BinaryHeap  |  Correctness  |\n"
        )

    for N in Ns:
        a = 0
        b = N // 2
        for k in Ks:
            skup = [random.randint(a, b) for _ in range(N)]
            binomial_heap = BinomialHeap()
            start_time_binomial = time.perf_counter()

            for i, val in enumerate(skup):
                binomial_heap.insert(val)
                if i % k == 0:
                    binomial_heap.extract_max()
            
            end_time_binomial = time.perf_counter()

            start_time_binary = time.perf_counter()
            
            binary_heap = []
            for i, val in enumerate(skup):
                heapq.heappush(binary_heap, -val)
                if i % k == 0:
                    heapq.heappop(binary_heap)

            end_time_binary = time.perf_counter()

            p = random.randint(0.75 * (a + b), b)
            with open(f"{N}_{k}.txt", "w+") as f:
                f.write(f'p={p}\n')
                while binomial_heap.find_max().key > p:
                    heapq.heappop(binary_heap)
                    f.write(f'{binomial_heap.extract_max()}\n')

            heap_correct = True
            while binary_heap and heap_correct:
                if -heapq.heappop(binary_heap) != binomial_heap.extract_max():
                    heap_correct = False

            total_time_binomial = round(end_time_binomial - start_time_binomial, 2)
            total_time_binary = round(end_time_binary - start_time_binary, 2)

            with open("report.txt", "a+") as f:
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
                
    with open("report.txt", "a+") as f:
        f.write(horizontal_line)
