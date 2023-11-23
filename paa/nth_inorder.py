class BSTNode:

    def __init__(self, val, left=None, right=None, parent=None):
        self.val = val
        self.left = left
        self.right = right
        self.parent = parent
        self.left_subtree = 0


class BSTTree:
    def __init__(self):
        self.root = None

    def insert(self, val):
        prev, temp = None, self.root
        while temp is not None:
            prev = temp
            if val < temp.val:
                temp.left_subtree += 1
                temp = temp.left
            else:
                temp = temp.right
        
        if prev is None:
            self.root = BSTNode(val)
        elif val < prev.val:
            prev.left = BSTNode(val)
            prev.left.parent = prev
        else:
            prev.right = BSTNode(val)
            prev.right.parent = prev


    def inorder(self):

        def inorder_(root):
            if root is None:
                return

            inorder_(root.left)
            print(root.val, end=' ')
            inorder_(root.right)

        inorder_(self.root)
        print()
    

    def nth_inorder(self, n):
        
        def nth_inorder_(root, n):
            if root is None:
                return None
            
            elif root.left_subtree == n - 1:
                return root.val
            
            elif root.left_subtree >= n:
                return nth_inorder_(root.left, n)
            
            else:
                return nth_inorder_(root.right, n - root.left_subtree - 1)
            
        return nth_inorder_(self.root, n)

        
    def __str__(self) -> str:
        if self.root is None: return '<empty tree>'
        def recurse(node):
            if node is None: return [], 0, 0
            label = f'{node.val}'
            left_lines, left_pos, left_width = recurse(node.left)
            right_lines, right_pos, right_width = recurse(node.right)
            middle = max(right_pos + left_width - left_pos + 1, len(label), 2)
            pos = left_pos + middle // 2
            width = left_pos + middle + right_width - right_pos
            while len(left_lines) < len(right_lines):
                left_lines.append(' ' * left_width)
            while len(right_lines) < len(left_lines):
                right_lines.append(' ' * right_width)
            if (middle - len(label)) % 2 == 1 and node.parent is not None and \
               node is node.parent.left and len(label) < middle:
                label += '.'
            label = label.center(middle, '.')
            if label[0] == '.': label = ' ' + label[1:]
            if label[-1] == '.': label = label[:-1] + ' '
            lines = [' ' * left_pos + label + ' ' * (right_width - right_pos),
                     ' ' * left_pos + '/' + ' ' * (middle-2) +
                     '\\' + ' ' * (right_width - right_pos)] + \
              [left_line + ' ' * (width - left_width - right_width) +
               right_line
               for left_line, right_line in zip(left_lines, right_lines)]
            return lines, pos, width
        return '\n'.join(recurse(self.root) [0])



if __name__ == '__main__':
    tree = BSTTree()

    tree.insert(7)
    tree.insert(4)
    tree.insert(8)
    tree.insert(2)
    tree.insert(6)
    tree.insert(12)
    tree.insert(1)
    tree.insert(3)
    tree.insert(5)
    tree.insert(10)
    tree.insert(15)
    tree.insert(9)

    print(tree)

    tree.inorder()
    print(tree.nth_inorder(5))
    