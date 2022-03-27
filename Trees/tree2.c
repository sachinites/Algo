#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "tree2.h"

tree_t* init_tree(void)
{
    tree_t *tree = calloc(1,sizeof(tree_t));
    if(!tree)
        return NULL;
    tree->root = NULL;
    return tree;
}

tree_node_t*
init_tree_node(int n)
{
    tree_node_t *node = calloc(1, sizeof(tree_node_t));
    if(!node)   return NULL;
    node->data = n;
    return node;
}

int
add_tree_node_by_value(tree_t *tree, int n)
{
    tree_node_t *root = NULL, *parent = NULL;;
    if(!tree) return FAILURE;
    tree_node_t *node = init_tree_node(n);
    if(!tree->root){
        tree->root = node;
        return SUCCESS;
    }

    root = tree->root;

    while(root){
            parent = root;
            root = (n <= root->data) ? root->left : root->right;
    } // while ends

    if(n <= parent->data)
        parent->left = node;
    else
        parent->right = node;

    return SUCCESS;
}

int
add_tree_node(tree_t *tree, tree_node_t *node)
{
    tree_node_t *root = NULL, *parent = NULL;;
    if(!tree) return FAILURE;
    if(!tree->root){
        tree->root = node;
        return SUCCESS;
    }

    root = tree->root;

    while(root){
            parent = root;
            root = (node->data <= root->data) ? root->left : root->right;
    } // while ends

    if(node->data <= parent->data)
        parent->left = node;
    else
        parent->right = node;

    return SUCCESS;
}


static void 
_printInorder(tree_node_t *root)
{
    if(!root)    return;
    _printInorder(root->left);
    printf("%-3d ", root->data);
    _printInorder(root->right);
}

void 
Inorder(tree_t *tree)
{
    if(!tree){
        printf("\n%s(): uninitialsed tree", __FUNCTION__);
        return;
    }
    if(!tree->root){
        printf("\n%s(): empty tree", __FUNCTION__);
        return;
    }
    
    printf("InOrder :\n");
    _printInorder(tree->root);
    printf("\n");
}

static void 
_printPreorder(tree_node_t *root)
{
    if(!root)    return;
    printf("%-3d ", root->data);
    _printPreorder(root->left);
    _printPreorder(root->right);
}

void 
Preorder(tree_t *tree)
{
    if(!tree){
        printf("\n%s(): uninitialsed tree", __FUNCTION__);
        return;
    }
    if(!tree->root){
        printf("\n%s(): empty tree", __FUNCTION__);
        return;
    }

    printf("PreOrder :\n");
    _printPreorder(tree->root);
    printf("\n");
}

static void 
_printPostorder(tree_node_t *root)
{
    if(!root)    return;
    _printPostorder(root->left);
    _printPostorder(root->right);
    printf("%-3d ", root->data);
}

void 
Postorder(tree_t *tree)
{
    if(!tree){
        printf("\n%s(): uninitialsed tree", __FUNCTION__);
        return;
    }
    if(!tree->root){
        printf("\n%s(): empty tree", __FUNCTION__);
        return;
    }
    printf("postOrder :\n");
    _printPostorder(tree->root);
    printf("\n");
}

void
printAllTraversals(tree_t *tree)
{
    Postorder(tree);
    Inorder(tree);
    Preorder(tree);
}


/* width of the tree :
*/
static void
_tree_width(tree_node_t *root, int dist, int *lmin, int *rmax) {

    if (root->left) {
        dist--;
        if (dist < *lmin) *lmin = dist;
        _tree_width(root->left, dist, lmin, rmax);
        dist++;
    }

    if (root->right) {
        dist++;
        if (dist > *rmax) *rmax = dist;
         _tree_width(root->right, dist, lmin, rmax);
         dist--;
    }
}

int
tree_width(tree_t *tree) {

    int dist = 0; int lmin = 0; int rmax = 0;

    _tree_width(tree->root, dist, &lmin, &rmax);
    return rmax - lmin;
}

static void
_remove_half_nodes(tree_node_t *curr_node, tree_node_t *parent, tree_t *tree) {

    if (!curr_node) return;

    _remove_half_nodes(curr_node->left, curr_node, tree);
    _remove_half_nodes(curr_node->right, curr_node, tree);

    if (!curr_node->left && !curr_node->right) return;

    if (curr_node->left && curr_node->right) return;

    if (!parent) {
        if (curr_node->left) {
            tree->root = curr_node->left;
        }
        else {
            tree->root = curr_node->right;
        }
        return;
    }

    if (curr_node == parent->left) {
        if (curr_node->left) {
            parent->left = curr_node->left;
        }
        else {
            parent->left = curr_node->right;
        }
    }
    else {
         if (curr_node->left) {
            parent->right = curr_node->left;
        }
        else {
            parent->right = curr_node->right;
        }
    }
    curr_node->left = NULL;
    curr_node->right = NULL;
}

/* Remove half nodes of the tree */
void
remove_half_nodes(tree_t *tree) {

    _remove_half_nodes(tree->root, NULL, tree);
}





/* Longest path in a tree */
typedef struct list_node_ {

    tree_node_t *tree_node;
    struct list_node_ *next;
} list_node_t;

typedef struct list_ {

    int count;
    list_node_t *head;
} list_t;  

static void
append_node_in_front(list_t *lst, tree_node_t *node) {

    list_node_t *lsnode = (list_node_t *)calloc(1, sizeof(list_node_t ));
    lsnode->tree_node = node;
    lsnode->next = lst->head;
    lst->head = lsnode;
    lst->count++;
}

static void
destroy_lst(list_t *lst) {

    list_node_t *curr, *next;

    for (curr = lst->head; curr; curr = next) {
        next = curr->next;
        free(curr);
        lst->count--;
    }
    assert(!lst->count);
}

static void
print_lst (list_t *lst) {

    list_node_t *curr, *next;

    for (curr = lst->head; curr; curr = next) {
        next = curr->next;
        printf ("%d ", curr->tree_node->data);
    }
}

static list_t 
_tree_longest_path(tree_node_t *node) {

    list_t lst1 = {0, 0};
    list_t lst2 = {0, 0};
    
    if (!node) return lst1;


    lst1 = _tree_longest_path (node->left);
    lst2 = _tree_longest_path (node->right);

    /* leaf node */
    if (lst1.count == 0 && lst2.count == 0) {
            append_node_in_front(&lst1, node);
            return lst1;
    }

    /* half node */
    if (lst1.count && lst2.count == 0) {
        append_node_in_front(&lst1, node);
        return lst1;
    }

    if (lst2.count && lst1.count == 0) {
        append_node_in_front(&lst2, node);
        return lst2;
    }

    list_t *max_lst = lst1.count > lst2.count ? &lst1 : &lst2;
    append_node_in_front(max_lst, node);
    return *max_lst;
}

void
tree_longest_path(tree_t *tree) {

    list_t lst  = _tree_longest_path(tree->root);
    print_lst(&lst);
    destroy_lst (&lst);
}


static void
_SumOfNodesAtDepth(tree_node_t *node, int currd, int depth, int *sum) {

    if (depth == 0) {
        *sum = node->data;
        return;
    }

    if (currd == depth) {

        *sum += node->data;
        return;
    }

    if (node->left) {
        _SumOfNodesAtDepth(node->left, currd + 1 , depth, sum);
    }

    if (node->right) {
        _SumOfNodesAtDepth(node->right, currd + 1 , depth, sum);
    }

}


int
SumOfNodesAtDepth(tree_t *tree, int depth) {

    int sum = 0;
    _SumOfNodesAtDepth(tree->root, 0, depth, &sum);
    return sum;
}



static tree_node_t **
_rightThreadedBST(tree_node_t *curr_node) {

    if (!curr_node) return NULL;

    tree_node_t **lres = _rightThreadedBST(curr_node->left);
    tree_node_t **rres = _rightThreadedBST(curr_node->right);

    /* if curr_node is a leaf node */
    if (curr_node->left == NULL && curr_node->right == NULL) {
       return &curr_node->right;
    }

    if (lres) *lres = curr_node;

    if (curr_node->right)
        return rres;
    else
        return &curr_node->right;
}

void
rightThreadedBST(tree_t *tree) {

    _rightThreadedBST(tree->root);
}



static tree_node_t **
_leftThreadedBST(tree_node_t *curr_node) {

    if (!curr_node) return NULL;

    tree_node_t **lres = _leftThreadedBST(curr_node->left);
    tree_node_t **rres = _leftThreadedBST(curr_node->right);

    /* if curr_node is a leaf node */
    if (curr_node->left == NULL && curr_node->right == NULL) {
       return &curr_node->left;
    }

    if (rres) *rres = curr_node;

    if (curr_node->left)
        return lres;
    else
        return &curr_node->left;
}

void
leftThreadedBST(tree_t *tree) {

    _leftThreadedBST(tree->root);
}



tree_node_t *
TreegetNthAncestor(tree_t *tree, int elem, int n) {

    tree_node_t *ances = NULL;
    tree_node_t *curr_node = tree->root;

    int k = 0;

    while (1) {

        if (elem < curr_node->data ) {
            if (curr_node->left) {
                curr_node = curr_node->left;
            }
            else return NULL;
        }
        else if (elem > curr_node->data){
            if (curr_node->right) {
                curr_node = curr_node->right;
            }
            else return NULL;
        }
        else {
            break;
        }

        k++;
        if (k == n) ances = tree->root;
        else if (k > n) ances = elem < ances->data ? ances->left : ances->right;
    }

    return ances;
}

static void
_TreeMirrorImage(tree_node_t *node) {

    if (!node) return;
    _TreeMirrorImage(node->left);
    _TreeMirrorImage(node->right);

    tree_node_t *temp;
    temp = node->left;
    node->left = node->right;
    node->right = temp;
}

void
TreeMirrorImage(tree_t *tree) {

    _TreeMirrorImage(tree->root);
}


static int
_TreeHeight (tree_node_t *node) {


    if (!node) return 0;

    int lres = _TreeHeight (node->left);
    int rres = _TreeHeight (node->right);

    /* leaf node */
    if (!node->left && !node->right) {
        return 0;
    }

    /* half node */
    if (!node->left && node->right) {
        return rres + 1;
    }
    if (node->left && !node->right) {
        return lres + 1;
    }

    /* Full node */
    if (lres < rres) return rres + 1;
    return lres + 1;
}

int 
TreeHeight (tree_t *tree) {

    return _TreeHeight(tree->root);
}

static int 
tree_lmin(tree_t *tree) {

    int dist = 0; int lmin = 0; int rmax = 0;
    _tree_width(tree->root, dist, &lmin, &rmax);
    return lmin;
}

static void
_verticalTraversal(tree_node_t *node, int row, int col, int **arr, int S, const int height, const int width) {

    if (!node) return;

    if (node->left) {
        _verticalTraversal(node->left, row + 1, col -1 , arr, S, height, width);
    }

    if (node->right) {
        _verticalTraversal(node->right, row + 1, col +1 , arr, S, height, width);
    }

    **(arr + ((row -1) * width) + col + S) = node->data;
    //arr[row][col + S] = node->data;
}

/* Return a pointer to 2D Array */
void
verticalTraversal(tree_t* tree) {

    /* Step 1 :
        1. find the height of the tree H
        2. Find the diameter of the tree D
        3. Find the distance of left most element in a tree - S
        4. malloc an array of size H + 1, D
    */

   int height = TreeHeight (tree);
   int dia = tree_width(tree);
   int S = tree_lmin(tree) * (-1);

   int **arr = (int **)calloc ((height + 1) * dia, sizeof(int));

    _verticalTraversal(tree->root, 0, 0, arr, S, height, dia);

    int i , j;

    for (j = 0; j < dia; j++) {

         printf ("elements in Vertical column :%d\n", j);

        for (i = 0; i <= height; i++) {

           printf ("[%d][%d] = %d\n", i, j, arr[i][j]);
        }
    }
}



int 
main(int argc, char **argv){

    tree_t *tree = init_tree();

#if 0
    add_tree_node_by_value(tree,  100);
    add_tree_node_by_value(tree,  50);
    add_tree_node_by_value(tree,  10);
    add_tree_node_by_value(tree,  90);
    add_tree_node_by_value(tree,  95);
    add_tree_node_by_value(tree,  99);
#endif
#if 1
    add_tree_node_by_value(tree,  50);
    add_tree_node_by_value(tree,  30);
    add_tree_node_by_value(tree,  10);
    add_tree_node_by_value(tree,  3);
    add_tree_node_by_value(tree,  4);
    add_tree_node_by_value(tree,  34);
    add_tree_node_by_value(tree,  32);
    add_tree_node_by_value(tree,  45);
    add_tree_node_by_value(tree,  38);
    add_tree_node_by_value(tree,  100);
    add_tree_node_by_value(tree,  75);
    add_tree_node_by_value(tree,  200);
    add_tree_node_by_value(tree,  150);
    add_tree_node_by_value(tree,  120);
    add_tree_node_by_value(tree,  37);
#endif   

#if 1
    {
        //printf ("tree width = %d\n", tree_width(tree));
        
        //remove_half_nodes(tree);
        //Inorder(tree);

        //tree_longest_path(tree);

        //printf ("SumOfNodesAtDepth = %d\n", SumOfNodesAtDepth(tree, 4));

        //rightThreadedBST(tree);

        //tree_node_t *node = NULL;
        //node = TreegetNthAncestor(tree, 3, 4);
        //printf ("TreegetNthAncestor = %d\n", node ? node->data : 0);

        //Inorder(tree);
        //TreeMirrorImage(tree);
        //Inorder(tree);

        verticalTraversal(tree);
    }
#endif

    return 0;
}
