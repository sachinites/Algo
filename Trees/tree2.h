#include <assert.h>

#define SUCCESS 0
#define FAILURE -1
#define TREE_TRUE 1
#define TREE_FALSE 0

typedef struct tree_node{
  struct tree_node *left;
  struct tree_node *right;
  int data;
} tree_node_t;

typedef struct tree{
    tree_node_t *root;
} tree_t;

tree_t* init_tree(void);
tree_node_t* init_tree_node(int n);

int add_tree_node_by_value(tree_t *tree, int n);
int add_tree_node(tree_t *tree, tree_node_t *node);

void Inorder(tree_t *tree);
void Preorder(tree_t *tree);
void printTree(tree_t *tree);
void Postorder(tree_t *tree);
void printAllTraversals(tree_t *tree);

 int tree_width(tree_t *tree);
void remove_half_nodes(tree_t *tree) ;

void tree_longest_path(tree_t *tree) ;
int SumOfNodesAtDepth(tree_t *tree, int depth);
void rightThreadedBST(tree_t *tree);
void leftThreadedBST(tree_t *tree) ;
tree_node_t * getNthAncestor(tree_t *tree, int elem);
void TreeMirrorImage(tree_t *tree);
void verticalTraversal(tree_t* tree) ;