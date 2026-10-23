#include "divide-and-conquer_2.h"

// Count downward paths that start at node and have total value sum.
int count(TreeNode *node, int sum) {
  if (node == nullptr) return 0;
  return (node->val == sum) + count(node->left, sum - node->val) +
         count(node->right, sum - node->val);
}

// Count paths starting at the current node, paths fully in the left subtree, and paths fully in the right subtree.
int pathSum(TreeNode *root, int sum) {
  if (root == nullptr) return 0;
  return count(root, sum) + pathSum(root->left, sum) +
         pathSum(root->right, sum);
}
