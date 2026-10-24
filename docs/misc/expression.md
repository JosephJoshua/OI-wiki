author: Ir1d, Anguei, hsfzLZH1, siger-young, HeRaNO, c8ef

Expression evaluation usually means: given an expression as a string, output its value. There are also variants, such as whether the expression contains parentheses or exponentiation, how many variables it has, or deciding whether several expressions are equivalent, and so on.

An expression usually needs grammar parsing first and evaluation afterwards, though you can also evaluate while parsing. Parsing checks whether the input string is a valid expression, and is usually done with a parser.

An expression contains two kinds of symbols: operands and operators. For an expression of length $n$, with a suitable parsing method, parsing and evaluation can be done in $O(n)$ time.

## Expression trees and reverse Polish notation

One way to parse an expression recursively is to treat the expression like ordinary grammar rules, split it into an expression tree as shown in the figure, and then evaluate bottom-up on the tree.![](./images/bet.png)

Doing a [tree traversal](../graph/tree-basic.md#tree-traversal) on the expression tree gives different kinds of expressions. Arithmetic expressions come in three forms: prefix, infix and postfix. Infix expressions are the ones used most in daily life; postfix expressions are the ones easiest for computers to understand.

-   Preorder traversal gives the prefix expression (Polish notation)
-   Inorder traversal gives the infix expression
-   Postorder traversal gives the postfix expression (reverse Polish notation)

Reverse Polish notation (postfix notation) is a way of writing mathematical expressions in which each operator comes after its operands. For example, the expression

$$
a+b*c*d+(e-f)*(g*h+i)
$$

can be written in reverse Polish notation as:

$$
abc*d*+ef-gh*i+*+
$$

So reverse Polish expressions correspond one-to-one to expression trees. Reverse Polish notation needs no parentheses, and its order of evaluation is uniquely determined.

The nice thing about reverse Polish notation is that it is easy to evaluate in linear time. For example, in the reverse Polish expression $3~2~*~1~-$, we first compute $3 \times 2 = 6$ (using the most recent operator, i.e. the operator on top of the stack), then compute $6 - 1 = 5$. As you can see, for a reverse Polish expression we only need to **maintain a stack of numbers; whenever we meet an operator, pop the top two elements and push the result back onto the stack**. At the end, the single element left on the stack is the value of the expression. This algorithm runs in $O(n)$ time.

Whether parsing an expression recursively succeeds depends on whether the grammar rules are well designed, that is, whether they produce the intended expression tree. For example:

$$
a+b*c
$$

Since addition and multiplication have different precedence, this infix expression could be turned into two different expression trees. So the design of the grammar rules depends heavily on operator precedence. Designing recursive grammar rules that respect operator precedence is actually not easy.

The method below treats each operator and its precedence as a whole. It is non-recursive, and parses and evaluates the expression directly based on operator precedence.

## Parenthesized expressions with only left-associative binary operators

Let us look at a simplified problem. Assume all operators are binary, meaning every operator takes two arguments. Also assume all operators are left-associative: if operators have equal precedence, they are applied from left to right. Parentheses are allowed.

To evaluate this kind of infix expression, we can convert it into a postfix expression and then evaluate it. Use two [stacks](../ds/stack.md), one for operators and one for operands. Whenever we meet a number, push it straight onto the operand stack. Each operator block corresponds to a pair of parentheses, and the operator stack is monotonic only within an operator block. Whenever we meet an operator, we look at the elements in the topmost operator block of the operator stack, and pop operators as needed so that operators inside the block stay in decreasing order of precedence. While popping, we compute the value of the corresponding subexpression.

Below, "output" means output to the postfix expression: either push the number onto the operand stack, or pop an operator and two operands, compute, and push the result back onto the operand stack. Scan the infix expression from left to right:

1.  If you meet a number, output it directly.
2.  If you meet a left parenthesis, push it onto the operator stack.
3.  If you meet a right parenthesis, keep outputting the top element of the stack until you reach a left parenthesis, then pop the left parenthesis. In other words, apply all operators inside the pair of parentheses.
4.  If you meet any other operator, keep outputting every operator on the stack whose precedence is greater than or equal to that of the current operator. Finally, push the new operator onto the operator stack.
5.  After the whole string is processed, some operators may still be on the stack, so output the remaining symbols one by one. The conversion is then complete.

Here is an implementation of this method for the four operators $+$, $-$, $*$, $/$:

??? note "Example code"
    ```cpp
    
    bool delim(char c) { return c == ' '; }
    
    bool is_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
    
    int priority(char op) {
      if (op == '+' || op == '-') return 1;
      if (op == '*' || op == '/') return 2;
      return -1;
    }
    
    void process_op(stack<int>& st, char op) {  // can also be used to evaluate postfix expressions
      int r = st.top();                         // take the top elements; mind the order
      st.pop();
      int l = st.top();
      st.pop();
      switch (op) {
        case '+':
          st.push(l + r);
          break;
        case '-':
          st.push(l - r);
          break;
        case '*':
          st.push(l * r);
          break;
        case '/':
          st.push(l / r);
          break;
      }
    }
    
    int evaluate(string& s) {  // can also be adapted to convert infix to postfix
      stack<int> st;
      stack<char> op;
      for (int i = 0; i < (int)s.size(); i++) {
        if (delim(s[i])) continue;
    
        if (s[i] == '(') {
          op.push('(');  // 2. if we meet a left parenthesis, push it onto the operator stack
        } else if (s[i] == ')') {  // 3. if we meet a right parenthesis, apply all operators inside the parentheses
          while (op.top() != '(') {
            process_op(st, op.top());
            op.pop();  // keep outputting the top element until we reach a left parenthesis
          }
          op.pop();                // pop the left parenthesis
        } else if (is_op(s[i])) {  // 4. if we meet any other operator
          char cur_op = s[i];
          while (!op.empty() && priority(op.top()) >= priority(cur_op)) {
            process_op(st, op.top());
            op.pop();  // keep outputting every operator with precedence >= the current operator
          }
          op.push(cur_op);  // push the new operator onto the operator stack
        } else {            // 1. if we meet a number, output it directly
          int number = 0;
          while (i < (int)s.size() && isalnum(s[i]))
            number = number * 10 + s[i++] - '0';
          --i;
          st.push(number);
        }
      }
    
      while (!op.empty()) {
        process_op(st, op.top());
        op.pop();
      }
      return st.top();
    }
    
    ```

This algorithm, which implicitly uses reverse Polish notation to evaluate the expression, runs in $O(n)$ time. With a small change to the implementation above, you can also get the reverse Polish expression explicitly.

### Unary operators and right-associative operators

Now suppose the expression also contains unary operators, i.e. operators with only one argument. Unary plus and unary minus are common examples.

One difference in this case is that we must decide whether the current operator is unary or binary.

Notice that a unary operator is usually preceded by another operator or an opening parenthesis, or by nothing if it is at the very start of the expression. A binary operator is always preceded by an operand or a closing parenthesis. So we can keep a flag saying whether the next operator may be unary.

Also, unary and binary operators must be applied differently, and unary operators get higher precedence than all binary operators. Note that some unary operators, such as unary plus and unary minus, are actually right-associative.

Right-associative means that whenever precedences are equal, the operators must be applied from right to left.

As mentioned above, unary operators are usually right-associative. Another example of a right-associative operator is exponentiation: $a \wedge b \wedge c$ is usually read as $a^{b^c}$, not $(a^b)^c$.

To handle such operators correctly, the change is: when precedences are equal, delay popping the operator from the stack.

The code to change is as follows. Replace:

```cpp

while (!op.empty() && priority(op.top()) >= priority(cur_op)) 
```

with

```cpp

while (!op.empty() &&
       ((left_assoc(cur_op) && priority(op.top()) >= priority(cur_op)) ||
        (!left_assoc(cur_op) && priority(op.top()) > priority(cur_op))))

```

where left\_assoc is a function that decides whether an operator is left-associative.

Here is an implementation for the binary operators $+$, $-$, $*$, $/$ and the unary operators $+$ and $-$:

??? note "Example code"
    ```cpp
    
    bool delim(char c) { return c == ' '; }
    
    bool is_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }
    
    bool is_unary(char c) { return c == '+' || c == '-'; }
    
    int priority(char op) {
      if (op < 0)  // unary operator
        return 3;
      if (op == '+' || op == '-') return 1;
      if (op == '*' || op == '/') return 2;
      return -1;
    }
    
    void process_op(stack<int>& st, char op) {
      if (op < 0) {
        int l = st.top();
        st.pop();
        switch (-op) {
          case '+':
            st.push(l);
            break;
          case '-':
            st.push(-l);
            break;
        }
      } else {  // take the top elements; mind the order
        int r = st.top();
        st.pop();
        int l = st.top();
        st.pop();
        switch (op) {
          case '+':
            st.push(l + r);
            break;
          case '-':
            st.push(l - r);
            break;
          case '*':
            st.push(l * r);
            break;
          case '/':
            st.push(l / r);
            break;
        }
      }
    }
    
    int evaluate(string& s) {
      stack<int> st;
      stack<char> op;
      bool may_be_unary = true;
      for (int i = 0; i < (int)s.size(); i++) {
        if (delim(s[i])) continue;
    
        if (s[i] == '(') {
          op.push('(');  // 2. if we meet a left parenthesis, push it onto the operator stack
          may_be_unary = true;
        } else if (s[i] == ')') {  // 3. if we meet a right parenthesis, apply all operators inside the parentheses
          while (op.top() != '(') {
            process_op(st, op.top());
            op.pop();  // keep outputting the top element until we reach a left parenthesis
          }
          op.pop();  // pop the left parenthesis
          may_be_unary = false;
        } else if (is_op(s[i])) {  // 4. if we meet any other operator
          char cur_op = s[i];
          if (may_be_unary && is_unary(cur_op)) cur_op = -cur_op;
          while (!op.empty() &&
                 ((cur_op >= 0 && priority(op.top()) >= priority(cur_op)) ||
                  (cur_op < 0 && priority(op.top()) > priority(cur_op)))) {
            process_op(st, op.top());
            op.pop();  // keep outputting every operator with precedence >= the current operator
          }
          op.push(cur_op);  // push the new operator onto the operator stack
          may_be_unary = true;
        } else {  // 1. if we meet a number, output it directly
          int number = 0;
          while (i < (int)s.size() && isalnum(s[i]))
            number = number * 10 + s[i++] - '0';
          --i;
          st.push(number);
          may_be_unary = false;
        }
      }
    
      while (!op.empty()) {
        process_op(st, op.top());
        op.pop();
      }
      return st.top();
    }
    
    ```

## References

**This page is mainly translated from the blog post [Разбор выражений. Обратная польская нотация](https://e-maxx.ru/algo/expressions_parsing) and its English translation [Expression parsing](https://cp-algorithms.com/string/expression_parsing.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

## Further reading

1.  [Operator-precedence\_parser](https://en.wikipedia.org/wiki/Operator-precedence_parser)
2.  [Shunting yard algorithm](https://en.wikipedia.org/wiki/Shunting_yard_algorithm)

## Exercises

1.  [NOIP2013 Junior Group: Expression Evaluation](https://www.luogu.com.cn/problem/P1981)
2.  [Postfix Expression](https://www.luogu.com.cn/problem/P1449)
3.  [Transform the Expression](https://www.spoj.com/problems/ONP/)
