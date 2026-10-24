This page gives a short introduction to the Minimax algorithm and Alpha–Beta pruning.

## Minimax algorithm

The Minimax algorithm is an algorithm that minimizes the possible loss in the worst case (that is, the maximum loss).

### Process

In two-player zero-sum games with fully determined positions, we often need adversarial search: we build a search tree where each node is a definite game state. On odd levels it is our turn to move, and on even levels it is the opponent's turn. Each leaf of the search tree is given an evaluation; the larger the value, the better our chances of winning. We want our winning chances to be as large as possible, while the opponent tries to lower them. On the search tree this means that nodes on odd levels (our nodes) always choose the child state with the largest winning chance, and nodes on even levels (the opponent's nodes) always choose the child state with the smallest winning chance (for us).

The Minimax algorithm traverses the search tree from top to bottom, uses subtree information to update the answer while backtracking, and finally gets the value of the root. This is the maximum score we can get when both sides play optimally.

### Example

Let's look at a simple example.

Call us MAX and the opponent MIN, as shown below:

![](images/minimax-1.svg)

For example, consider the following position. Assume we search from left to right, and the numbers on the nodes are our winning chances:

![](images/minimax-2.svg)

We should choose the middle route. If we choose the left route, the worst winning chance is $3$; if we choose the middle route, the worst is $15$; if we choose the right route, the worst is $1$. Although the right route might give a winning chance of $22$, a sufficiently rational opponent will leave us with only $1$. Weighing these options, the middle route is clearly better.

![](images/minimax-3.svg)

In fact, when looking at the right route, once we find that the winning chance may be $1$, we no longer need to look at the branches with winning chances $12$, $20$ and $22$. Compared with the winning chances of the two routes on the left, we can already be sure the right route is not the best.

The naive Minimax algorithm often has to build a huge search tree, with unbearable time and space complexity. Alpha–Beta pruning is a way to prune Minimax by using upper and lower bounds on both players' scores at each node of the search tree.

Note that in different problems, the values on the nodes of the search tree mean different things: they can be evaluations, scores, winning probabilities, and so on. For convenience, we call them all scores below.

## Alpha–Beta pruning

Alpha–Beta pruning is a pruning technique for the Minimax algorithm.

### Process

In the Minimax algorithm, if we know the scores of all children of a node, we can compute the score of that node: for a MAX node, take the maximum score; for a MIN node, take the minimum score.

When the search has reached a node but has not finished it, we cannot compute the node's score yet, but we can compute the range of scores for both players **among the nodes searched so far**. During the search, we maintain two variables $\alpha$ and $\beta$. When the game reaches this node, **taking into account all nodes already searched**, they are the lower bound and upper bound of the score that the Alpha player (the side seeking the maximum score) and the Beta player (the side seeking the minimum score), respectively, can guarantee.

The pruning rule of Alpha–Beta depends on the values of $\alpha$ and $\beta$ when the current node is searched. If the current node is a MAX node, the Alpha player can keep searching its children to raise the lower bound $\alpha$. But if after some search we already have $\alpha\ge\beta$, then searching this node further cannot affect the outcome of the game: once the game reaches this node, the Alpha player can guarantee a score of at least $\alpha$; but the Beta player already knows a strategy (that leaves the current path) which guarantees a score of at most $\beta\le\alpha$, so the Beta player has no reason to let the game reach **the current node**. Likewise, if the current node is a MIN node, and after searching one of its children we find $\beta\le\alpha$ at this node, there is also no need to search the other children, because the Alpha player has no reason to let the game enter **the current node**. Putting the two cases together: when $\alpha \geq \beta$, the remaining branches of the node need not be searched (that is, they can be pruned). Note that we can also prune when $\alpha = \beta$, because the other side already has an alternative that guarantees a score no worse for them than $\alpha$ (that is, $\beta$), and searching the remaining branches will not change the result at higher nodes.

During the search, we do not need to keep node scores; we only need to maintain $\alpha$ and $\beta$. Initially, let $\alpha=-\infty,~\beta=+\infty$. When searching downward, we pass $\alpha$ and $\beta$ down as well, to record both players' alternatives.

After a child has been searched, we update the information at the current node. Suppose the current node $X$ is a MAX node and we have just finished searching its child $Y$. Then the $\beta$ value at $X$ does not change; only the $\alpha$ value needs to be updated by taking the maximum with the score of child $Y$. If child $Y$ is a leaf, we update the $\alpha$ value at $X$ directly with the score of $Y$; otherwise, we just update the $\alpha$ value of $X$ with the $\beta$ value of child $Y$. There are three possibilities here:

1.  The $\beta$ value of child $Y$ lies strictly between the $\alpha$ and $\beta$ values of node $X$. Child $Y$ inherits the $\alpha$ value of $X$ and does not update it, so if $\beta > \alpha$ still holds after searching $Y$, no pruning happened while searching $Y$. The final $\beta$ value of $Y$ equals the smallest of the $\beta$ value it inherited from $X$ and the scores of all of its (that is, $Y$'s) children. Since this minimum is strictly less than the $\beta$ value of $X$, it must be the minimum score among $Y$'s children. Therefore, since $Y$ is a MIN node, its score is exactly this $\beta$ value, and using it to update the $\alpha$ value of $X$ is correct.
2.  The $\beta$ value of child $Y$ equals the $\beta$ value of node $X$. As explained above, this means that the scores of all children of $Y$ are at least the $\beta$ value of $X$. This further means the Beta player has no reason to let the game enter node $X$: as long as the Alpha player picks child $Y$, the Beta player cannot get a score lower than $\beta$. So here, updating the $\alpha$ value of $X$ with the $\beta$ value of $Y$ serves to make $\alpha=\beta$ at $X$, which triggers the pruning condition. The effect is the same as updating the $\alpha$ value of $X$ with the actual score at $Y$, a number at least the $\beta$ value of $X$.
3.  The $\beta$ value of child $Y$ is less than or equal to the $\alpha$ value of node $X$. In this case child $Y$ triggered the pruning condition. Its actual score is at most the $\beta$ value of $Y$, and so at most the $\alpha$ value of $X$. Updating the $\alpha$ value of $X$ with the actual score of $Y$ would not change $\alpha$. This has the same effect as updating the $\alpha$ value of $X$ with the $\beta$ value of $Y$.

This analysis shows that after a child has been fully searched, only in the first case does $\alpha$ (or $\beta$) record exactly the actual score of the child as a MAX node (or MIN node). In the other cases, it may not be the exact score, but the information it gives is enough to make the pruning correct, so the score recorded at the root is not affected.

### Example

In this section we walk through an example to show how the $\alpha$ and $\beta$ values at each node are updated during the search. Along the way we also compute the scores of the nodes involved, so we can see how the actual score at each node relates to the recorded $\alpha$ and $\beta$ values. Note, however, that an implementation of this algorithm does not compute these actual scores.

Consider the following position, and assume we search from left to right:

![](images/alpha-beta-1.svg)

At initialization, let $\alpha = -\infty,~\beta = +\infty$, and pass this information down along the search path.

![](images/alpha-beta-2.svg)

When the search reaches node A: its left child has score $3$, and node A is a MIN node that looks for low-score moves, so we change $\beta$ to $3$, because $3$ is less than the current $\beta$ value ($\beta = +\infty$). Then the right child of node A has score $17$; we do not change node A's $\beta$ value, because $17$ is greater than the current $\beta$ value ($\beta = 3$). Now all children of node A have been searched, so the score of node A is $3$, which matches the $\beta$ value recorded at this node (case 1 above).

![](images/alpha-beta-3.svg)

Node A is a child of node B. After computing the score of node A, we can update the $\alpha$ and $\beta$ values of node B. Node B is a MAX node that looks for high-score moves, so we change $\alpha$ to $3$, because the $\beta$ value at child A ($\beta=3$) is greater than the current $\alpha$ value ($\alpha = -\infty$). Next, we search node B's right child C, passing node B's $\alpha$ and $\beta$ values to node C.

![](images/alpha-beta-4.svg)

For node C, the left child has score $2$, and node C is a MIN node, so we change $\beta$ to $2$. Now $\alpha \geq \beta$, so the remaining children of node C need not be searched: we can be sure the Alpha player will not let the game reach node C. Node C is a MIN node, and its score is $2$, which does not exceed the recorded $\beta$ value (case 3 above). All children of node B have now been searched, so the score of node B is $3$, the same as the recorded $\alpha$ value (case 1 above).

![](images/alpha-beta-5.svg)

After computing the score of node B: node B is a child of node D, so we can update the $\alpha$ and $\beta$ values of node D. Node D is a MIN node, so we change $\beta$ to $3$. Then node D passes its $\alpha$ and $\beta$ values to node E, and node E passes them on to node F. Node F has only one child, with score $15$. Since $15$ is greater than the current $\beta$ value and node F is a MIN node, we do not update its $\beta$ value. The score of node F is then $15$, greater than the recorded $\beta$ value (case 2 above).

![](images/alpha-beta-6.svg)

After computing the score of node F: node F is a child of node E, so we can update the $\alpha$ and $\beta$ values of node E. Node E is a MAX node, so we update $\alpha$. Now $\alpha \geq \beta$, so the remaining branch of node E (that is, node G) can be pruned. Node E is a MAX node, and its score is set to $15$, strictly greater than the recorded $\alpha$ value (case 3 above). We use node E's $\alpha$ value to update node D's $\beta$ value, which stays $3$. All children of node D have now been searched, so the score of node D is $3$, equal to the recorded $\beta$ value (case 1 above).

![](images/alpha-beta-7.svg)

After computing the score of node D: node D is a child of node H, so we can update the $\alpha$ and $\beta$ values of node H. Node H is a MAX node, so we update $\alpha$. Then, following the search order, node H's $\alpha$ and $\beta$ values are passed down to nodes I, J and K in turn. For node K, its left child has score $2$, and node K is a MIN node, so we update $\beta$. Now $\alpha \geq \beta$, so the remaining branches of node K can be pruned. The score of node K is set to $2$, less than or equal to the recorded $\beta$ value (case 3 above).

![](images/alpha-beta-8.svg)

After computing the score of node K: node K is a child of node J, so we can update the $\alpha$ and $\beta$ values of node J. Node J is a MAX node, so we update $\alpha$; but since the score of node K is less than $\alpha$, node J's $\alpha$ value stays at $3$. Then node J's $\alpha$ and $\beta$ values are passed to node L. Node L is a MIN node, so we update $\beta = 3$. Now $\alpha \geq \beta$, so the remaining branches of node L can be pruned. Node L has no remaining branches, so no actual pruning happens here. The score of node L is set to $3$, which is less than or equal to the recorded $\beta$ value (case 3 above).

![](images/alpha-beta-9.svg)

After computing the score of node L: node L is a child of node J, so we can update the $\alpha$ and $\beta$ values of node J. Node J is a MAX node, so we update $\alpha$; but since the score of node L is less than or equal to $\alpha$, node J's $\alpha$ value stays at $3$. All children of node J have now been searched, so the score of node J is $3$, which equals the recorded $\alpha$ value (case 2 above).

After computing the score of node J: node J is a child of node I, so we can update the $\alpha$ and $\beta$ values of node I. Node I is a MIN node, so we update $\beta$. Now $\alpha \geq \beta$, so the remaining branches of node I can be pruned. Note that because of the right child, the actual score of node I is $2$, less than the recorded $\beta$ value (case 3 above).

After computing the score of node I: node I is a child of node H, so we can update the $\alpha$ and $\beta$ values of node H. Node H is a MAX node, so we update $\alpha$; but since the score of node I is less than or equal to $\alpha$, node H's $\alpha$ value stays at $3$. All children of node H have now been searched, so the score of node H is $3$, which equals the recorded $\alpha$ value (case 1 above).

![](images/alpha-beta-10.svg)

This is the final result.

### Implementation

???+ example "Reference code"
    ```cpp
    int alpha_beta(int u, int alph, int beta, bool is_max) {
      if (!son_num[u]) return val[u];
      if (is_max) {
        for (int i = 0; i < son_num[u]; ++i) {
          int d = son[u][i];
          alph = max(alph, alpha_beta(d, alph, beta, !is_max));
          if (alph >= beta) break;
        }
        return alph;
      } else {
        for (int i = 0; i < son_num[u]; ++i) {
          int d = son[u][i];
          beta = min(beta, alpha_beta(d, alph, beta, !is_max));
          if (alph >= beta) break;
        }
        return beta;
      }
    }
    ```

## References and notes

-   [Minimax Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Minimax#Minimax_algorithm_with_alternate_moves)
-   [Alpha–beta pruning - Wikipedia](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

**Parts of this article are quoted from the blog post [A detailed explanation of the Minimax algorithm and α-β pruning, by Wenjianmuran](https://blog.csdn.net/wenjianmuran/article/details/90633418), under the CC 4.0 BY-SA license. The content has been modified.**
