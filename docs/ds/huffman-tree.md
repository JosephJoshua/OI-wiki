author: Alex-McAvoy, lingkerio, LvCGame

## Weighted path length of a tree

Suppose a binary tree has $n$ weighted leaves. For each leaf, multiply the length of the path from the root to that leaf by the leaf's weight. The sum of these products is called the **weighted path length of the tree (WPL)**.

Let $w_i$ be the weight of the $i$-th leaf of the binary tree, and let $l_i$ be the length of the path from the root to the $i$-th leaf. Then WPL is computed as:

$$
WPL=\sum_{i=1}^nw_il_i
$$

![](./images/huffman-tree-1.svg)

For the tree shown above, the WPL is computed as follows:

$$
WPL=2*2+3*2+4*2+7*2=4+6+8+14=32
$$

## Structure

Given a set of leaves with fixed weights, you can build many different binary trees. Among them, the **binary tree with the smallest WPL** is called a **Huffman tree**.

In a Huffman tree, leaves with smaller weights are farther from the root, and leaves with larger weights are closer to the root. Also, only the leaves have degree $0$; every other node has degree $2$.

## Huffman's algorithm

Huffman's algorithm builds a Huffman tree. The steps are:

1.  **Initialize**: from the given $n$ weights, build $n$ binary trees that each have only a root node. This gives a set $F$ of binary trees.
2.  **Select and merge**: from the set $F$, pick the **two** binary trees whose roots have the **smallest** weights. Use them as the left and right subtrees of a new binary tree. The weight of the new tree's root is the sum of the weights of the roots of its left and right subtrees.
3.  **Remove and add**: remove the two trees used as left and right subtrees from $F$, and add the newly built tree to $F$.
4.  Repeat steps 2 and 3. When only one binary tree is left in the set, that tree is the Huffman tree.

![](./images/huffman-tree-2.svg)

### Proof of correctness

???+ note "Lemma"
    In an optimal prefix code tree (Huffman tree), the two leaves with the smallest weights are always the deepest leaves, and making these two nodes siblings does not break the optimality of the code tree.

??? note "Proof"
    We prove this by contradiction. Suppose that in an optimal prefix code tree, the two leaves with the smallest weights are not the deepest leaves. Call these two nodes $a$ and $b$, and suppose their depth is less than that of some deepest leaf. For this deepest leaf $c$, we can swap $a$ and $c$, or swap $b$ and $c$. Since the Huffman algorithm guarantees that each level of the tree is merged by the leaves with the smallest weights, the weighted path length (WPL) of the tree decreases after the swap. This is a contradiction, so the assumption is false. Therefore, the two leaves with the smallest weights must be the deepest leaves.
    
    Next, suppose the two leaves with the smallest weights are $a$ and $b$, and they have the same depth. Suppose that in some optimal prefix code tree these two nodes are not siblings, and there are other nodes $c$ and $d$ that are siblings of $a$ and $b$ respectively (say $a$ and $c$ are siblings, and $b$ and $d$ are siblings). We can merge $a$ and $b$ into one subtree.
    
    -   If the total weight of $a$ and $b$ after merging is less than the weight of $c$ or $d$, then we can merge this subtree with the node of larger weight (such as $c$ or $d$) to form a new subtree, and the WPL decreases.
    -   If the total weight of $a$ and $b$ is not less than the weights of $c$ and $d$, we can simply make $a$ and $b$ siblings, and make $c$ and $d$ another pair of siblings. The WPL does not increase.
    
    So after this adjustment, optimality is not broken. This completes the proof.

???+ note "Theorem"
    The prefix code tree produced by the Huffman algorithm is an optimal prefix code tree.

??? note "Proof"
    We prove this theorem by mathematical induction.
    
    -   **Base case**: when the number of letters is $n = 2$, clearly merging the two letters into one tree gives the optimal code tree.
    -   **Inductive hypothesis**: assume that when the number of letters is $n = k$ ($k \geq 2$), the Huffman algorithm produces an optimal prefix code tree.
    -   **Inductive step**: for $n = k + 1$ letters, pick the two letters with the smallest weights out of the $k+1$ letters and merge them into a subtree. The root of the subtree acts as a virtual letter (virtual node). By the lemma, this step does not break the optimality of the prefix code tree. Now the virtual letter and the remaining $k$ letters together form $k + 1$ letters, and by the inductive hypothesis, the Huffman algorithm produces an optimal prefix code tree when the number of letters is $k$.
    
    So by mathematical induction, the Huffman algorithm produces an optimal prefix code tree for any number of letters $n$. This completes the proof.

## Huffman coding

In programming, we usually represent a set of characters by giving each character its own code. This is called **encoding**.

In binary encoding, if all codes have the same length, then representing $n$ different characters needs $\left \lceil \log_2 n \right \rceil$ bits. This is called **fixed-length encoding**.

If every character is **used equally often**, fixed-length encoding is clearly the most space-efficient method. But if characters appear with different frequencies, we can give frequent characters codes that are as short as possible and rare characters longer codes. This builds a **variable-length encoding**, which gives better space efficiency.

When designing a variable-length encoding, decoding must be unique. If no code in a set is a prefix of any other code, the set is called a **prefix code**. A prefix code guarantees that decoding is unique.

A Huffman tree can be used to build the **shortest prefix code**, called the **Huffman code**. The steps are:

1.  Let the set of characters to encode be $d_1,d_2,\dots,d_n$, and let their frequencies in the string be $w_1,w_2,\dots,w_n$.
2.  Using $d_1,d_2,\dots,d_n$ as leaves and $w_1,w_2,\dots,w_n$ as the leaf weights, build a Huffman tree.
3.  Let each left branch of the Huffman tree mean $0$ and each right branch mean $1$. Then the sequence of $0$s and $1$s along the path from the root to a leaf is the code for that leaf's character.

![](./images/huffman-tree-3.svg)

## Example code

??? note "Building a Huffman tree"
    ```cpp
    struct HNode {
      int weight;
      HNode *lchild, *rchild;
    };
    
    using Htree = HNode *;
    
    Htree createHuffmanTree(int arr[], int n) {
      Htree forest[N];
      Htree root = NULL;
      for (int i = 0; i < n; i++) {  // Put all nodes into the forest
        Htree temp;
        temp = (Htree)malloc(sizeof(HNode));
        temp->weight = arr[i];
        temp->lchild = temp->rchild = NULL;
        forest[i] = temp;
      }
    
      for (int i = 1; i < n; i++) {  // n-1 rounds to build the Huffman tree
        int minn = -1, minnSub;  // minn: index of the root with the smallest value; minnSub: index of the root with the second smallest value
        for (int j = 0; j < n; j++) {
          if (forest[j] != NULL && minn == -1) {
            minn = j;
            continue;
          }
          if (forest[j] != NULL) {
            minnSub = j;
            break;
          }
        }
    
        for (int j = minnSub; j < n; j++) {  // Set minn and minnSub
          if (forest[j] != NULL) {
            if (forest[j]->weight < forest[minn]->weight) {
              minnSub = minn;
              minn = j;
            } else if (forest[j]->weight < forest[minnSub]->weight) {
              minnSub = j;
            }
          }
        }
    
        // Build the new tree
        root = (Htree)malloc(sizeof(HNode));
        root->weight = forest[minn]->weight + forest[minnSub]->weight;
        root->lchild = forest[minn];
        root->rchild = forest[minnSub];
    
        forest[minn] = root;     // Store the pointer to the new tree at position minn
        forest[minnSub] = NULL;  // Clear position minnSub
      }
      return root;
    }
    ```

??? note "Computing the WPL of a Huffman tree"
    ```cpp
    struct HNode {
      int weight;
      HNode *lchild, *rchild;
    };
    
    using Htree = HNode *;
    
    int getWPL(Htree root, int len) {  // Recursively compute the WPL of an already built Huffman tree
      if (root == NULL)
        return 0;
      else {
        if (root->lchild == NULL && root->rchild == NULL)  // Leaf node
          return root->weight * len;
        else {
          int left = getWPL(root->lchild, len + 1);
          int right = getWPL(root->rchild, len + 1);
          return left + right;
        }
      }
    }
    ```

??? note "Computing the WPL directly without building the Huffman tree"
    ```cpp
    int getWPL(int arr[], int n) {  // Compute the WPL directly without building the Huffman tree
      priority_queue<int, vector<int>, greater<int>> huffman;  // Min-heap
      for (int i = 0; i < n; i++) huffman.push(arr[i]);
    
      int res = 0;
      for (int i = 0; i < n - 1; i++) {
        int x = huffman.top();
        huffman.pop();
        int y = huffman.top();
        huffman.pop();
        int temp = x + y;
        res += temp;
        huffman.push(temp);
      }
      return res;
    }
    ```

??? note "Computing the Huffman code for a given sequence"
    ```cpp
    struct HNode {
      int weight;
      HNode *lchild, *rchild;
    };
    
    using Htree = HNode *;
    
    void huffmanCoding(Htree root, int len, int arr[]) {  // Compute the Huffman code
      if (root != NULL) {
        if (root->lchild == NULL && root->rchild == NULL) {
          printf("The code of the character with node %d is: ", root->weight);
          for (int i = 0; i < len; i++) printf("%d", arr[i]);
          printf("\n");
        } else {
          arr[len] = 0;
          huffmanCoding(root->lchild, len + 1, arr);
          arr[len] = 1;
          huffmanCoding(root->rchild, len + 1, arr);
        }
      }
    }
    ```
