
    # tree = BplusTree()
    # BplusNode.d = 3
    # for i in range(100):
    #     tree.insert(i)
    # [14, 69, 43, 20, 3, 11, 84, 56, 69, 67, 71, 65]
    # tree.remove(14)
    # tree.remove(69)
    # tree.remove(43)
    # tree.remove(20)
    # tree.remove(3)
    # tree.remove(11)
    # tree.remove(84)
    # tree.remove(56)
    # tree.remove(69)
    # tree.remove(71)
    # tree.remove(65)

    # tree.print_tree()



    # prev = None
    # temp = tree.find(0)[0]
    # while temp:
    #     prev = temp
    #     for key in temp.keys:
    #         print(key, end=' ')
    #     print(end='|')
    #     temp = temp.next_leaf
    # print()
    # while prev:
    #     for key in prev.keys[::-1]:
    #         print(key, end=' ')
    #     print(end='|')
    #     prev = prev.prev_leaf


'''
            removing = []
            removed = 0
            try:
                
                while removed < N // 10:
                    torem = random.randint(0, N - 1)
                    removing.append(torem)
                    rem_success = tree.remove(torem)
                    if rem_success:
                        removed += 1
                end_time = time.perf_counter()
                print(N, d, end_time - start_time)
            except:
                print(removing)


'''


'''
    
    def print_tree(self):
        from collections import deque
        stack = deque()
        stack.append(self.root)
        while stack:
            temp = stack.popleft()
            if temp.is_leaf:
                break
            for key in temp.keys:
                print(key, end=' ')
            print(len(temp.pointers))
            for u in temp.pointers:
                stack.append(u)

'''