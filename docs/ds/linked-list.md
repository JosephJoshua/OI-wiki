This page gives a short introduction to linked lists.

## Introduction

A linked list is a data structure for storing data, where elements are connected by pointers like links in a chain. Inserting and deleting data is very convenient, but finding and reading data is slow.

## Differences from arrays

Both linked lists and arrays can store data. Unlike a linked list, an array stores all its elements one after another in order. These different storage layouts give them different strengths:

Because of its chain-like structure, a linked list makes deleting and inserting data easy, taking $O(1)$ operations. But for the same reason, finding and reading data is less efficient than in an array: random access takes $O(n)$ operations.

An array makes finding and reading data easy: random access takes $O(1)$ operations. But deletion and insertion take $O(n)$ operations.

## Building a linked list

???+ tip "Tip"
    The pointer parts of building a linked list are fairly abstract and may be hard to follow from text and code alone. It helps to draw diagrams as you go.

### Singly linked list

A singly linked list contains a data field and a pointer field. The data field stores the data, and the pointer field connects the current node to the next node.

![](images/list.svg)

???+ note "Implementation"
    === "C++"
        ```cpp
        struct Node {
          int value;
          Node *next;
        };
        ```
    
    === "Python"
        ```python
        class Node:
            def __init__(self, value=None, next=None):
                self.value = value
                self.next = next
        ```

### Doubly linked list

A doubly linked list also has a data field and a pointer field. The difference is that the pointer field has a left and a right pointer (or previous and next), connecting the previous node, the current node and the next node.

![](images/double-list.svg)

???+ note "Implementation"
    === "C++"
        ```cpp
        struct Node {
          int value;
          Node *left;
          Node *right;
        };
        ```
    
    === "Python"
        ```python
        class Node:
            def __init__(self, value=None, left=None, right=None):
                self.value = value
                self.left = left
                self.right = right
        ```

## Inserting (writing) data into a linked list

### Singly linked list

The process is roughly:

1.  Initialize the data to insert, `node`;
2.  Point the `next` pointer of `node` to the node after `p`;
3.  Point the `next` pointer of `p` to `node`.

The figures below show the process:

1.  ![](./images/list-insert-1.svg)
2.  ![](./images/list-insert-2.svg)
3.  ![](./images/list-insert-3.svg)

The code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void insertNode(int i, Node *p) {
          Node *node = new Node;
          node->value = i;
          node->next = p->next;
          p->next = node;
        }
        ```
    
    === "Python"
        ```python
        def insertNode(i, p):
            node = Node()
            node.value = i
            node.next = p.next
            p.next = node
        ```

### Singly linked circular list

If you connect the head and tail of a linked list, it becomes a circular linked list. Since the head and tail are connected, when inserting data you need to check whether the original list is empty: if it is, the new node loops to itself; otherwise, insert the data normally.

The process is roughly:

1.  Initialize the data to insert, `node`;
2.  Check whether the given list `p` is empty;
3.  If it is empty, point both the `next` pointer of `node` and `p` to `node` itself;
4.  Otherwise, point the `next` pointer of `node` to the node after `p`;
5.  Point the `next` pointer of `p` to `node`.

The figures below show the process:

1.  ![](./images/list-insert-cyclic-1.svg)
2.  ![](./images/list-insert-cyclic-2.svg)
3.  ![](./images/list-insert-cyclic-3.svg)

The code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void insertNode(int i, Node *p) {
          Node *node = new Node;
          node->value = i;
          node->next = NULL;
          if (p == NULL) {
            p = node;
            node->next = node;
          } else {
            node->next = p->next;
            p->next = node;
          }
        }
        ```
    
    === "Python"
        ```python
        def insertNode(i, p):
            node = Node()
            node.value = i
            node.next = None
            if p == None:
                p = node
                node.next = node
            else:
                node.next = p.next
                p.next = node
        ```

### Doubly linked circular list

When inserting into a doubly linked circular list, besides checking whether the given list is empty, you also need to update both the left and right pointers.

The process is roughly:

1.  Initialize the data to insert, `node`;
2.  Check whether the given list `p` is empty;
3.  If it is empty, point the `left` and `right` pointers of `node`, as well as `p`, to `node` itself;
4.  Otherwise, point the `left` pointer of `node` to `p`;
5.  Point the `right` pointer of `node` to the right node of `p`;
6.  Point the `left` pointer of the right node of `p` to `node`;
7.  Point the `right` pointer of `p` to `node`.

The code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void insertNode(int i, Node *p) {
          Node *node = new Node;
          node->value = i;
          if (p == NULL) {
            p = node;
            node->left = node;
            node->right = node;
          } else {
            node->left = p;
            node->right = p->right;
            p->right->left = node;
            p->right = node;
          }
        }
        ```
    
    === "Python"
        ```python
        def insertNode(i, p):
            node = Node()
            node.value = i
            if p == None:
                p = node
                node.left = node
                node.right = node
            else:
                node.left = p
                node.right = p.right
                p.right.left = node
                p.right = node
        ```

## Deleting data from a linked list

### Singly linked (circular) list

Let the node to delete be `p`. To remove it from the list, copy the value of the next node `p->next` into `p`, and at the same time update the link to the node two steps after `p`.

The process is roughly:

1.  Copy the value of the node after `p` into `p`, overwriting `p->value`;
2.  Create a temporary node `t` that stores the address of `p->next`;
3.  Point the `next` pointer of `p` to the node two steps after `p`, removing `p->next`;
4.  Delete `t`. Although the address of the original node `p` is still in use and what gets deleted is the address of the original node `p->next`, the data of `p` has been overwritten by `p->next`, so `p` exists in name only.

The figures below show the process:

1.  ![](./images/list-delete-1.svg)
2.  ![](./images/list-delete-2.svg)
3.  ![](./images/list-delete-3.svg)

The code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void deleteNode(Node *p) {
          p->value = p->next->value;
          Node *t = p->next;
          p->next = p->next->next;
          delete t;
        }
        ```
    
    === "Python"
        ```python
        def deleteNode(p):
            p.value = p.next.value
            p.next = p.next.next
        ```

### Doubly linked circular list

The process is roughly:

1.  Point the right pointer of the left node of `p` to the right node of `p`;
2.  Point the left pointer of the right node of `p` to the left node of `p`;
3.  Create a temporary node `t` that stores the address of `p`;
4.  Assign the address of the right node of `p` to `p`, so that `p` does not become a dangling pointer;
5.  Delete `t`.

The code is as follows:

???+ note "Implementation"
    === "C++"
        ```cpp
        void deleteNode(Node *&p) {
          p->left->right = p->right;
          p->right->left = p->left;
          Node *t = p;
          p = p->right;
          delete t;
        }
        ```
    
    === "Python"
        ```python
        def deleteNode(p):
            p.left.right = p.right
            p.right.left = p.left
            p = p.right
        ```

## Tricks

### XOR linked list

An XOR linked list is still essentially a **doubly linked list**, but by using bitwise XOR it provides the functionality of a doubly linked list with the memory of only one pointer.

In the structure `Node`, we define `lr = left ^ right`, the **bitwise XOR** of the addresses of the previous and next elements. When traversing forward, XOR the address of the previous element
with the current node's `lr` to get the address of the next element. When traversing backward, XOR the address of the next element with the current node's `lr` to get the address of the previous element.
This way, a doubly linked list's functionality can be achieved with half the memory.
