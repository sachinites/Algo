#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "tree.h"
#include "../common.h"
#include "../Queue/Queue.h"

char enableLogging = TREE_FALSE;
tree_t* 
init_tree(void)
{
    tree_t *tree = calloc(1,sizeof(tree_t));
    if(!tree)
        return NULL;
    tree->root = NULL;
    tree->stack = get_new_stack();
    return tree;
}


void
_all_branch_sum(tree_node_t *node, int sum){

	if(!node) return;

	_all_branch_sum (node->left,  sum + node->data);
	_all_branch_sum (node->right, sum + node->data);

	if(!node->left && !node->right)
		printf("%d\n", sum + node->data);
}

void
all_branch_sum(tree_t *tree){
	if(!tree || !tree->root) return ;
	_all_branch_sum(tree->root, 0);
}


tree_node_t*
getNodePtrBST(tree_t *tree, int elem){
    if(!tree || !tree->root) return NULL;
    if(tree->root->data == elem) return tree->root;
    tree_node_t *root = tree->root;
    do{
        if(elem > root->data)
            root = root->right;
        else
            root = root->left;
    } while(root && root->data!= elem);
    return root;
}

char isNodeVisited(tree_node_t *node)
{
    return node->isVisited;
}

void markNodeVisited(tree_node_t *node)
{
    node->isVisited = TREE_TRUE;
}


void markNodeNotVisited(tree_node_t *node)
{
    node->isVisited = TREE_FALSE;
}

tree_node_t* init_tree_node(int n)
{
    tree_node_t *node = calloc(1, sizeof(tree_node_t));
    if(!node)   return NULL;
    node->data = n;
    node->isVisited = TREE_FALSE;
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


void PostorderNR(tree_t *tree)
{

/*This is Non-Recursive method of post-order traversal of a tree using stack
1. use of flag is used in the tree node to keep the track if the node is visited
2. if you dont want to change the tree node data structure, may be use some other method, like use 2 stacks.
3. The use of "isVisited" flag is to decide the follow up action to be taken when the new element is exposed to the top of the stack after popping out its children:
    * whether we need to push the right child of the element because its left child has been processed
    * whenther we need to process the element itself (pop-out) because its right child has been processed.
*/

    if(!tree)
        return;
    if(!tree->root)
        return;

    int output[MAX_STACK_SIZE], index = 0, i =0;
    tree_node_t *root = tree->root, *curr_node = NULL;
    stack_t *stack = get_new_stack();

    if(enableLogging) printf("%s() trace BEGIN \n", __FUNCTION__);
    PUSH(stack, tree->root);

    while(!isStackEmpty(stack))
    {

        if(root->left){
            PUSH(stack, root->left);
            root->isVisited = TREE_FALSE;
            root=root->left;
            continue;
        }

        if(root->right){
            PUSH(stack, root->right);
            root->isVisited = TREE_TRUE;
            root=root->right;
            continue;
        }

        curr_node = pop(stack);
        if(enableLogging) {
            printf("element %d pop-out of the stack, line : %d, %s()\n", 
                       curr_node->data, __LINE__, __FUNCTION__);
            printStack(stack);
        }
        output[index] = curr_node->data;
        index++;

        ITERATE:
            root = getTopElem(stack);
            if(!root)
                break;

            if(isNodeVisited(root) == TREE_FALSE){
                markNodeVisited(root);
                if(root->right)
                {
                    PUSH(stack, root->right);
                    root = root->right;
                    continue;
                }
                else
                {
                   curr_node = pop(stack);
                   if(enableLogging) {
                       printf("element %d pop-out of the stack, line : %d, %s()\n",curr_node->data, __LINE__,
                       __FUNCTION__);
                       printStack(stack);
                   }
                   output[index] = curr_node->data;
                   index++;
                   goto ITERATE;
                }
            }
            else 
            {
                   curr_node = pop(stack);
                   if(enableLogging){
                       printf("element %d pop-out of the stack, line : %d, %s()\n",curr_node->data,
                       __LINE__, __FUNCTION__);
                       printStack(stack);
                   }
                   output[index] = curr_node->data;
                   index++;
                   goto ITERATE;
            }

            } // while ends

    free_stack(stack);
    stack = NULL;
    printf("%s :\n", __FUNCTION__);
    for(i = 0 ; i < index; i++)
        printf("%-3d ", output[i]); 
    printf("\n");
    if(enableLogging) printf("%s() trace END \n", __FUNCTION__);
    return;
}

void InorderNR(tree_t *tree)
{

/*Thsi is Non-Recursive method of In-order traversal of a tree using stack
1. use of flag is used in the tree node to keep the track if the node is visited
2. if you dont want to change the tree node data structure, may be use some other method, like use 2 stacks.
3. The use of "isVisited" flag is to decide the follow up action to be taken when the new element is exposed to the top of the stack after popping out its children:
    * whether we need to push the right child of the element because its left child has been processed
    * whenther we need to process the element itself (pop-out) because its right child has been processed.
*/

    if(!tree)
        return;
    if(!tree->root)
        return;

    int output[MAX_STACK_SIZE], index = 0, i =0;
    tree_node_t *root = tree->root, *curr_node = NULL;
    stack_t *stack = get_new_stack();

    if(enableLogging) printf("%s() trace BEGIN \n", __FUNCTION__);
    PUSH(stack, tree->root);

    while(!isStackEmpty(stack))
    {

        if(root->left){
            PUSH(stack, root->left);
            root->isVisited = TREE_FALSE; // node above me in the stack is my left child
            root=root->left; 
            continue;
        }

        curr_node = getTopElem(stack);
        output[index] = curr_node->data;
        index++;

        markNodeVisited(curr_node);

        if(root->right){
            PUSH(stack, root->right);
            root->isVisited = TREE_TRUE; // node above me in the stack is my right child
            root=root->right;
            continue;
        }

        curr_node = pop(stack); // its a leaf
        if(enableLogging) {
            printf("element %d pop-out of the stack, line : %d\n",curr_node->data, __LINE__);
            printStack(stack);
        }

ITERATE:
        root = getTopElem(stack);
        if(!root)
            break;

        if(isNodeVisited(root) == TREE_FALSE){
            markNodeVisited(root);
            output[index] = root->data;
            index++;
            if(root->right)
            {
                PUSH(stack, root->right);
                root = root->right;
                continue;
            }
            else
            {
                POP(stack); 
                goto ITERATE;
            }
        }

        POP(stack);
        goto ITERATE;
    } // while ends

    free_stack(stack);
    stack = NULL;
    printf("%s :\n", __FUNCTION__);
    for(i = 0 ; i < index; i++)
        printf("%-3d ", output[i]); 
    printf("\n");
    if(enableLogging) printf("%s() trace END \n", __FUNCTION__);
    return;
}
        
void PreorderNR(tree_t *tree)
{

/*Thsi is Non-Recursive method of In-order traversal of a tree using stack
1. use of flag is used in the tree node to keep the track if the node is visited
2. if you dont want to change the tree node data structure, may be use some other method, like use 2 stacks.
3. The use of "isVisited" flag is to decide the follow up action to be taken when the new element is exposed to the top of the stack after popping out its children:
    * whether we need to push the right child of the element because its left child has been processed
    * whenther we need to process the element itself (pop-out) because its right child has been processed.
*/

    if(!tree)
        return;
    if(!tree->root)
        return;

    int output[MAX_STACK_SIZE], index = 0, i =0;
    tree_node_t *root = tree->root;
    stack_t *stack = get_new_stack();

    if(enableLogging) printf("%s() trace BEGIN \n", __FUNCTION__);
    PUSH(stack, tree->root);

    while(!isStackEmpty(stack))
    {
        root = getTopElem(stack);
        output[index] = root->data;
        index++;

        if(root->left){
            PUSH(stack, root->left);
            root->isVisited = TREE_FALSE;
            root=root->left;
            continue;
        }

        if(root->right){
            PUSH(stack, root->right);
            root->isVisited = TREE_TRUE;
            root=root->right;
            continue;
        }

        POP(stack); // its a leaf

ITERATE:
        root = getTopElem(stack);
        if(!root)
            break;

        if(isNodeVisited(root) == TREE_FALSE){
            markNodeVisited(root);
            if(root->right)
            {
                PUSH(stack, root->right);
                root = root->right;
                continue;
            }
            else
            {
                POP(stack); 
                goto ITERATE;
            }
        }

        POP(stack);
        goto ITERATE;
    } // while ends

    free_stack(stack);
    stack = NULL;
    printf("%s :\n", __FUNCTION__);
    for(i = 0 ; i < index; i++)
        printf("%-3d ", output[i]); 
    printf("\n");
    if(enableLogging) printf("%s() trace END \n", __FUNCTION__);
    return;
}

void swapchilds(tree_node_t *node)
{
    if (!node) return;
    tree_node_t *temp = NULL;
    temp = node->left;
    node->left = node->right;
    node->right = temp;
    return;
}

static void 
_MirrorImageByInorder(tree_node_t *root)
{
    if(!root) return;
    _MirrorImageByInorder(root->left);
    swapchilds(root);
    _MirrorImageByInorder(root->right);
    return;
}

void MirrorImageByInorder(tree_t *tree)
{
    if(!tree || !tree->root) return;
    _MirrorImageByInorder(tree->root);
    return;
}


static void 
_MirrorImageByPreorder(tree_node_t *root)
{
    if(!root) return;
    swapchilds(root);
    _MirrorImageByPreorder(root->left);
    _MirrorImageByPreorder(root->right);
    return;
}

void MirrorImageByPreorder(tree_t *tree)
{
    if(!tree || !tree->root) return;
    _MirrorImageByPreorder(tree->root);
    return;
}


static void 
_MirrorImageByPostorder(tree_node_t *root)
{
    if(!root) return;
    _MirrorImageByPostorder(root->left);
    _MirrorImageByPostorder(root->right);
    swapchilds(root);
    return;
}

void MirrorImageByPostorder(tree_t *tree)
{
    if(!tree || !tree->root) return;
    _MirrorImageByPostorder(tree->root);
    return;
}


typedef struct _max_sum_res{
	int cum_sum;
	int recycle_sum;
} max_sum_res_t;


static max_sum_res_t 
_MaxSumPath(tree_node_t *root){

	max_sum_res_t res, lchild, rchild;
	memset(&res,    0, sizeof(max_sum_res_t));
	memset(&lchild, 0, sizeof(max_sum_res_t));
	memset(&rchild, 0, sizeof(max_sum_res_t));

	if(!root)
		return res;

	lchild = _MaxSumPath(root->left);
	rchild = _MaxSumPath(root->right);

	// case 1 : if i am leaf

	if(!root->left && !root->right){
		res.cum_sum = root->data;
		res.recycle_sum = root->data;
		return res;	
	}

	// case 2: if half node
	if(!root->left && root->right){
		res.recycle_sum = 0 + rchild.cum_sum + root->data;
		res.cum_sum = MAX(0 + root->data, rchild.cum_sum + root->data);
		if(res.recycle_sum >= rchild.recycle_sum){

		}
		else
		{
			res.recycle_sum = rchild.recycle_sum;
		}
		return res;
	}
	if(root->left && !root->right){
		res.recycle_sum = lchild.cum_sum + 0 + root->data;
		res.cum_sum = MAX(lchild.cum_sum + root->data, 0 + root->data);
		if(res.recycle_sum >= lchild.recycle_sum){

		}
		else
		{
			res.recycle_sum = lchild.recycle_sum;
		}
		return res;
	}

	// case 3: if internal node
	if(root->left && root->right){
		res.recycle_sum = lchild.cum_sum + rchild.cum_sum + root->data;
		res.cum_sum  =  MAX(lchild.cum_sum + root->data, rchild.cum_sum + root->data); 
		if(res.recycle_sum >= lchild.recycle_sum){
			if(res.recycle_sum >= rchild.recycle_sum){
				return res;	
			}
			// rchild has greatest recycle_sum
			res.recycle_sum = rchild.recycle_sum;
			return res;
		}
		if(lchild.recycle_sum >= rchild.recycle_sum){
			res.recycle_sum = lchild.recycle_sum;
			return res;
		}

		// rchild has greatest recycle_sum
		res.recycle_sum = rchild.recycle_sum;
		return res;
	}
}

static int
_MaxSumPath2(tree_node_t *root) {

	int temp;
	if(!root) return 0;

	int left_sum  = _MaxSumPath2(root->left);
	printf("left_sum returned = %d\n", left_sum);

	int right_sum = _MaxSumPath2(root->right);
	printf("right_sum returned = %d\n", right_sum);	

	if(!left_sum && !right_sum) {

		temp = root->data;
		printf("temp = %d\n", temp);
		return temp;
	}

	if(!left_sum && right_sum){

		temp = (root->data + MAX(right_sum, left_sum));
		printf("temp = %d\n", temp);
		return temp;
	}
	
	if(left_sum && !right_sum){

		temp = (root->data + MAX(right_sum, left_sum));
		printf("temp = %d\n", temp);
		return temp;
	}

	temp = (root->data + MAX(left_sum, right_sum));
	printf("temp = %d\n", temp);
	return temp;
}


int MaxSumPath(tree_t *tree){
   if(!tree || !tree->root) 
      	return 0;
#if 1
    max_sum_res_t res =  _MaxSumPath(tree->root);
    return res.recycle_sum;
#else
	int res2 = _MaxSumPath2(tree->root);
	return res2;
#endif
}

static 
tree_node_t* _removeHalfNodes(tree_node_t *root){
    if(!root) return NULL;
    tree_node_t *lchild = _removeHalfNodes(root->left);
    root->left = lchild;
    tree_node_t *rchild = _removeHalfNodes(root->right);
    root->right = rchild;
    // case 1 : if my both childs are NULL, i will return my pointer to my parent
    if(!lchild && !rchild) return root;
    //case 2 : if my both children are not NULL, i will return my pointer to my parent
    else if(lchild && rchild) return root;
    //case 3 : now i am a half node, i am return my only kid
    else if(lchild && !rchild) 
        return lchild;
    else
        return rchild;
}

tree_t* removeHalfNodes(tree_t *tree){
    if(!tree)
        return NULL;
    if(!tree->root)
        return tree;
#define DUMMY_TREE_NODE_VAL 0
     tree_node_t *dummy = init_tree_node(DUMMY_TREE_NODE_VAL);
     dummy->right = tree->root;
    _removeHalfNodes(dummy);
     tree->root = dummy->right;
     return tree;
}

int frameno = 0;
tree_node_t* constructAllBST(int arr[], int index1, int index2)
{
     frameno++;
    if(enableLogging) 
        printf("%s():frame:%d called for index1 = %d, index2 = %d\n", __FUNCTION__, frameno, index1, index2);
     
     int i = 0;
     tree_node_t *root = NULL;

     if(index1 == index2 && index1 > -1){
         if(enableLogging)
             printf("   returning node with value %d for loop [%d,%d] from frame = %d\n", arr[index1], index1, index2, frameno);
         frameno--;
         return init_tree_node(arr[index1]);
    }

    if(index2 <= index1 ) {
        if(enableLogging)
            printf("returning NULL\n");
        frameno--;
        return NULL;
    }

    if(index1 >= index2) {
        if(enableLogging)
            printf("returning NULL\n");
        frameno--;
        return NULL;
    }
    
    for(i = index1 ; i <= index2; i++){
        root = init_tree_node(arr[i]);
        if(enableLogging)
            printf("root selected is : i = %d, value = %d for loop [%d,%d], frameno = %d\n", 
                i, arr[i], index1, index2, frameno);

            root->left = constructAllBST(arr, index1, i-1);
            root->right = constructAllBST(arr, i+1, index2);
            if(frameno == 1)
            {
                tree_t *tree = init_tree();
                tree->root = root;
                Inorder(tree);
            }
            else
            {
                    if(enableLogging)
                        printf("returning from frame %d with root node = %d\n", frameno, root->data);
                    frameno--;
            }
    }
}


static void
apply_gdb(tree_t *tree)
{
    return;
}

static tree_node_t*
_LowestCommonAncestor(tree_node_t *root, int n1, int n2)
{
    if(!root) return NULL;
    tree_node_t *lchild = _LowestCommonAncestor(root->left, n1, n2);
    tree_node_t *rchild = _LowestCommonAncestor(root->right, n1, n2);

    // processinf leaf node
    if(!lchild && !rchild){
        if(root->data == n1 || root->data ==n2)
            return root;
        else
            return NULL;
    }

    else if(!lchild && rchild){
            if(root->data == n1 || root->data == n2)
                return root;
            else
                return rchild;
    }

    else if(lchild && !rchild){
        if(root->data == n1 || root->data == n2)
            return root;
        else
            return lchild;
    }

    else if(lchild && rchild)
            return root;
}

static tree_node_t*
_LowestCommonAncestor2(tree_node_t *root, int n1, int n2)
{
	if(!root) return NULL;

	tree_node_t *leftc  = _LowestCommonAncestor(root->left, n1, n2);
	tree_node_t *rightc = _LowestCommonAncestor(root->right, n1, n2);	

	/* if root is a leaf node */
	if(!leftc && !rightc) {

		if(root->data == n1 || root->data == n2) return root;
	}

	/* handling half nodes */
	if((leftc && !rightc) || (!leftc && rightc)) {

		if(root->data == n1 || root->data == n2)
			return root;
		else
			return leftc ? leftc : rightc;
	}

	/* handling full nodes */
	return root;
}

/*Given values of two nodes in a Binary Search Tree, write a c program to find the Lowest Common Ancestor (LCA).*/
tree_node_t* LowestCommonAncestor(tree_t *tree, int n1, int n2)
{
    if(!tree || !tree->root)
        return NULL;
    tree_node_t *ancestor = _LowestCommonAncestor(tree->root, n1, n2);
    return ancestor;
}

static tree_node_t*
_rightThreadedBST(tree_node_t *root)
{
    tree_node_t* lchild = NULL;
    tree_node_t* rchild = NULL;

    if(!root) return NULL;
    lchild = _rightThreadedBST(root->left);
    rchild = _rightThreadedBST(root->right);

    // processinf leaf
    if(!lchild & !rchild) return root;

    else if(!lchild && rchild)
        return rchild;
        
    else if(lchild && !rchild){
        if(!lchild->right){
        lchild->right = root;
        return root;
        }
    }

    else if(lchild && rchild)
    {
        if(!lchild->right)
            lchild->right = root;
        return rchild;
    }

}

tree_node_t* 
rightThreadedBST(tree_t *tree)
{
    if(!tree || !tree->root)
        return NULL;
    return _rightThreadedBST(tree->root);
}


static tree_node_t*
_leftThreadedBST(tree_node_t *root)
{
    tree_node_t* lchild = NULL;
    tree_node_t* rchild = NULL;

    if(!root) return NULL;
    lchild = _leftThreadedBST(root->left);
    rchild = _leftThreadedBST(root->right);

    // processinf leaf
    if(!lchild & !rchild) return root;

    else if(!lchild && rchild){
        if(!rchild->left)
            rchild->left = root;
        return root;
    }

    else if(lchild && !rchild)
        return lchild;

    else if(lchild && rchild)
    {
        if(!rchild->left)
            rchild->left = root;
        return lchild;
    }

}

tree_node_t* 
leftThreadedBST(tree_t *tree)
{
    if(!tree || !tree->root)
        return NULL;
    return _leftThreadedBST(tree->root);
}

int
getFirstNodebyPostOrder(tree_t *tree)
{
    stack_t *stack = tree->stack;
    if(isStackEmpty(stack) == TREE_FALSE) assert(0);
    if(!tree || !tree->root) return -1;
    tree_node_t *root = tree->root;

    do{
        PUSH(stack, root);
        if(root->left){
            markNodeNotVisited(root);
            root = root->left;
            continue;
        }

        if(root->right){
            markNodeVisited(root);
            root = root->right;
            continue;
        }

        root = pop(stack);
        if(enableLogging) 
            printf("element %d pop-out of the stack, line : %d, %s()\n", root->data, __LINE__, __FUNCTION__);

        return root->data;

    }while(1);

}

int
getNextNodebyPostOrder(stack_t *stack)
{
    if(!stack) assert(0);
    if(isStackEmpty(stack)) return -1;
    tree_node_t *root = NULL;

    PROCESS_STACK_TOP:
        root = getTopElem(stack);
        if(isNodeVisited(root) == TREE_FALSE){
            markNodeVisited(root);
            if(root->right){
                root = root->right;
                if(enableLogging)
                    printf("unconditional jump from %s():%d to label PUSH_INTO_STACK\n", __FUNCTION__, __LINE__);
                goto PUSH_INTO_STACK;
            }

            root = pop(stack);
            if(enableLogging)
                printf("element %d pop-out of the stack, line : %d, %s()\n", root->data, __LINE__, __FUNCTION__);
            return root->data;
        }

        if(isNodeVisited(root) == TREE_TRUE){
            root = pop(stack);
            if(enableLogging)
                printf("element %d pop-out of the stack, line : %d, %s()\n", root->data, __LINE__, __FUNCTION__);
            return root->data;
        }

        PUSH_INTO_STACK:
        do{
            PUSH(stack, root);
            if(root->left){
                markNodeNotVisited(root);
                root = root->left;
                continue;
            }

            markNodeVisited(root);

            if(root->right){
                root = root->right;
                continue;
            }

            break;
        } while(1);
        
        if(enableLogging)
            printf("unconditional jump from %s():%d to label PROCESS_STACK_TOP\n", __FUNCTION__, __LINE__);
        goto PROCESS_STACK_TOP;
        return 0;
}

static void
_undoRightThreadedBST(tree_t *tree)
{
    stack_t *stack = tree->stack;
    tree_node_t *root = tree->root, *curr = NULL;
    PUSH(stack, root);

    PUSH_INTO_STACK:

    while(root->left){
        root = root->left;
        PUSH(stack,root);
    }

    STACK_CHECK:
    if(root->right){
        if(isPresentinStack(stack, root->right) == TREE_FALSE){
            root = root->right;
            PUSH(stack, root);
            goto PUSH_INTO_STACK;
        }

        root->right = NULL;

        POP:
        curr = pop(stack);
        if(enableLogging)
            printf("element %d pop-out of the stack, line : %d, %s()\n", curr->data, __LINE__, __FUNCTION__);
            root = getTopElem(stack);
            if(!root) return;

            if(root->right == curr){
                goto POP;
            }

            else if (root->left == curr){
                goto STACK_CHECK;
            }
    }
    // stack may be left with some nodes after last element in inorder traversal is processed
    reset_stack(stack);
 }

void undoRightThreadedBST(tree_t *tree)
{
    if(!tree) return;
    if(!tree->root) return;
    reset_stack(tree->stack);
    _undoRightThreadedBST(tree);
    }


static void
_undoLeftThreadedBST(tree_t *tree)
{
    stack_t *stack = tree->stack;
    tree_node_t *root = tree->root, *curr = NULL;
    PUSH(stack, root);

    STACK_CHECK:
        if(root->left){
        if(isPresentinStack(stack, root->left) == TREE_FALSE){
            root = root->left;
            PUSH(stack,root);
            goto STACK_CHECK;
        }
        else
        {
            root->left = NULL;
            
            POP:
            curr =  pop(stack);
            if(enableLogging)
                printf("element %d pop-out of the stack, line : %d, %s()\n", curr->data, __LINE__, __FUNCTION__);
            root = getTopElem(stack);
            if(!root) return;

            if(root->right == curr){
                goto POP;
            }
            else if(root->left == curr){
                goto PUSH_INTO_STACK;
            }

         }
    }

        PUSH_INTO_STACK:
        if(root->right){
            root = root->right;
            PUSH(stack, root);
            goto STACK_CHECK; 
        }
        goto POP;
}

void undoLeftThreadedBST(tree_t *tree)
{
    if(!tree) return;
    if(!tree->root) return;
    reset_stack(tree->stack);
    _undoLeftThreadedBST(tree);
}

/*Used when recursive calls needs to return two nodes to its ancestors
instead of one */

typedef struct pack{
    tree_node_t *successor_node; // node whose successor is to be found
    tree_node_t *predecessor_node; // node whose predecessor is to be found
} pack_t;

static int
_isPackEmpty(pack_t *pack)
{
    if(pack->successor_node || pack->predecessor_node)
        return TREE_FALSE;
     return TREE_TRUE;
}

static pack_t 
_constuctCompleteThreadedBST(tree_node_t *root)
{
      pack_t pack;
      pack.successor_node = NULL;
      pack.predecessor_node = NULL;
      
      if(!root){
          /* return empty pack*/
        return pack;
      }

      pack_t lchild_pack = _constuctCompleteThreadedBST(root->left);
      pack_t rchild_pack = _constuctCompleteThreadedBST(root->right);

      /*Examining the pack returned from left and right child*/
      
      // cas 1 : if i am leaf, that is both packs are empty

      if(_isPackEmpty(&lchild_pack) && _isPackEmpty(&rchild_pack)){
          pack.successor_node = root;
          pack.predecessor_node = root;
          return pack;
      }
      
      // case 2 : if left pack is empty, but right pack is not

      else if(_isPackEmpty(&lchild_pack) && !_isPackEmpty(&rchild_pack)){
         rchild_pack.predecessor_node->left = root;
         pack.successor_node = rchild_pack.successor_node;
         pack.predecessor_node = root;
         return pack;
      }

      // case 3 : if right pack is empty, but left pack is not

      else if(!_isPackEmpty(&lchild_pack) && _isPackEmpty(&rchild_pack)){
          lchild_pack.successor_node->right = root;
          pack.successor_node = root;
          pack.predecessor_node = lchild_pack.predecessor_node;
          return pack;
      }

    // case 4 : if right pack and left both are not empty

    else if(!_isPackEmpty(&lchild_pack) && !_isPackEmpty(&rchild_pack)){
         lchild_pack.successor_node->right = root;
         pack.predecessor_node = lchild_pack.predecessor_node;
         rchild_pack.predecessor_node->left = root;
         pack.successor_node = rchild_pack.successor_node;
         return pack;
    }
}
void* constuctCompleteThreadedBST(tree_t *tree)
{
    if(!tree) return NULL;
    if(!tree->root) return NULL;
    _constuctCompleteThreadedBST(tree->root); 
    return NULL;
}


static pack_t
_BSTtreeToDoublyLinkedList(tree_node_t* root)
{
      pack_t pack;
      pack.successor_node = NULL;
      pack.predecessor_node = NULL;
      
      if(!root)
        return pack; /* return empty pack*/

    pack_t lchild_pack = _BSTtreeToDoublyLinkedList(root->left);
    pack_t rchild_pack = _BSTtreeToDoublyLinkedList(root->right);

   /*case 1 : i am a leaf node, then my lchild_pack and rchild_pack will be empty, then
   my successor and predecessor both will exist in the tree above me*/
   if(_isPackEmpty(&lchild_pack) && _isPackEmpty(&rchild_pack)){
        pack.successor_node = root; // find successor_node of root (that is myself)
        pack.predecessor_node = root; // find predecessor_node of root (that is myself)
        return pack;
   }

   /*case 2 : If i am a node with only left child, left pack will not be empty but right pack will be*/
   else if(!_isPackEmpty(&lchild_pack) && _isPackEmpty(&rchild_pack)){
       /*Do the Double Bonding because i am the successor node of lchild_pack.successor_node*/
       lchild_pack.successor_node->right = root;
       root->left = lchild_pack.successor_node;

       pack.successor_node = root; // my right child is NULL, definitely my successor would exist above me
       pack.predecessor_node = lchild_pack.predecessor_node; //  predecessor of predecessor_node would exist in tree above me
       return pack;
   }

   /*case 3 : If i am a node with only right child, right pack will not be empty but left will be */
   else if(_isPackEmpty(&lchild_pack) && !_isPackEmpty(&rchild_pack)){
       /*Do the Double Bonding because i am the predecessor node of rchild_pack.predecessor_node*/
       rchild_pack.predecessor_node->left = root;
       root->right = rchild_pack.predecessor_node;

       pack.successor_node = rchild_pack.successor_node;// successor of successor_node would exist in tree above me
       pack.predecessor_node = root;// my left child is NULL, definitely my predecessor would exist above me
       return pack;
   }

   /*case 4 : If i am the node with both my left and right child, i will recieve packs from both the children*/
   else if(!_isPackEmpty(&lchild_pack) && !_isPackEmpty(&rchild_pack)){
       /*Do the double bonding with lchild_pack.successor_node because i am the successor of it*/
       lchild_pack.successor_node->right = root;
       root->left = lchild_pack.successor_node;

       /*Do the double bonding with rchild_pack.predecessor_node because i am the predecessor of it*/
       rchild_pack.predecessor_node->left = root;
       root->right = rchild_pack.predecessor_node;

       /* Still the successor of rchild_pack.successor_node is not known, so pass to the ancestor*/
       pack.successor_node = rchild_pack.successor_node;

       /* Still the predecessor of lchild_pack.predecessor_node is not known, so pass to the ancestor*/
       pack.predecessor_node = lchild_pack.predecessor_node;
       return pack;
   }
}


tree_node_t* 
BSTtreeToDoublyLinkedList (tree_t *tree)
{
    if(!tree) return NULL;
    if(!tree->root) return NULL;
    _BSTtreeToDoublyLinkedList(tree->root);
    // returning node of the doubly linked list which was the root of the tree before tree was converted to doubly LL
    return tree->root; 
}

int
DepthOfTreeNode(tree_t *tree, int elem)
{
    if(!tree || !tree->root) return -1;
    int depth = 0;
    tree_node_t *root = tree->root;
    if(root->data == elem) return depth;

    do
    {
        if(elem > root->data){
            depth++;
            root = root->right;
        }
        else{
             depth++;
             root = root->left;
        }
    } while(root && root->data != elem);

    if(!root)
        return -1;
    return depth;
}


void 
gotoEndOfList(tree_node_t **node)
{
    if(!node || !*node) assert(0);
    while((*node)->right){
        *node = (*node)->right;
    }
}

static tree_node_t*
_allDescendantNodesAtDistance(const tree_node_t *root, tree_node_t *elem, const int D, int d)
{
    if(!elem) return NULL;

    if(d < D){
        tree_node_t* lchild = _allDescendantNodesAtDistance(root, elem->left, D, d+1);
        tree_node_t* rchild = _allDescendantNodesAtDistance(root, elem->right, D, d+1);

        /* create linked list of nodes, This will temper original tree*/

        /* case 1 , if lchild and rchild both are not null*/
        if(lchild && rchild){
            tree_node_t* Istnode = lchild;
            gotoEndOfList(&lchild);
            lchild->right = rchild;
            rchild->left = lchild;
            return Istnode;
        }

        /*case 2 : when lchild is NULL but rchild is not*/

        else if(!lchild && rchild){
            return rchild;
        }

        /*case 3 : when rchild is NULL but lchild is not*/

        else if(lchild && !rchild){
            return lchild;
        }
        
        /*case 4, both are NULL*/
        else
            return NULL;
    }
    else if(d == D){
        elem->left = NULL;
        elem->right = NULL;
        return elem;
    }
}


tree_node_t*
allDescendantNodesAtDistance(tree_t *tree, int elem, int distance){
    if(!tree || !tree->root) return NULL;
    tree_node_t *node_elem = getNodePtrBST(tree, elem); // O(log n)
    if(!node_elem) return NULL;
    if(distance == 0) return node_elem;
    return _allDescendantNodesAtDistance(tree->root, node_elem, distance, 0);
}

static tree_node_t*
_getNthAncestor(tree_node_t *root, const int elem, int *level)
{
    tree_node_t *node_ptr = NULL;
    if(!root) return NULL;

    if(elem < root->data){
        node_ptr = _getNthAncestor(root->left, elem, level);
        if(*level == 0){
            if(node_ptr) 
                return node_ptr;
            else
                return root;
        }
        (*level)--;
        return NULL;
    }

    else if (elem > root->data){
        node_ptr = _getNthAncestor(root->right, elem, level);
        if(*level == 0){
            if(node_ptr) 
                return node_ptr;
            else
                return root;
        }
        (*level)--;
        return NULL;
    }

    else
        node_ptr = root;

    if(node_ptr->data == elem){
        if(*level == 0)
            return node_ptr;
         (*level)--;
          return NULL;
    }
}


tree_node_t*
getNthAncestor(tree_t *tree, int elem, int distance)
{
    if(!tree || !tree->root) return NULL;
    tree_node_t *node_elem = getNodePtrBST(tree, elem); // O(log n)
    if(!node_elem) return NULL;
    if(distance == 0) return node_elem;
    int level = distance;
    return _getNthAncestor(tree->root, elem, &level);
 }


static int
_SumOfNodesAtDepth(tree_node_t *root, int depth, int frameno){
    int lsum = 0, rsum = 0;
    if(frameno < depth){
        if(root->left){
            lsum = _SumOfNodesAtDepth(root->left, depth, frameno + 1);
        }

        if(root->right){
            rsum = _SumOfNodesAtDepth(root->right, depth, frameno + 1);
        }
    }
    
    if(frameno == depth)
        return root->data;

    return lsum + rsum;
}

int
SumOfNodesAtDepth(tree_t *tree, int depth){
    if(!tree || !tree->root) return 0;
    if(depth == 0) return tree->root->data;
    return _SumOfNodesAtDepth(tree->root, depth, 0);
}


static void
_getWidthBT_increment(int *currentD, int *lmax){
    *currentD += 1;
    if(*currentD > *lmax)
        *lmax = *currentD;
    return;
}


static void
_getWidthBT_decrement(int *currentD, int *rmin){
    *currentD -= 1;
    if(*currentD < *rmin)
        *rmin = *currentD;
    return;
}

static tree_node_t*
_getWidthBT(tree_node_t *root, int *lmax, int *rmin, int *currentD){

   if(root->left){
        _getWidthBT_increment(currentD, lmax);
        _getWidthBT(root->left, lmax, rmin, currentD);
        _getWidthBT_decrement(currentD, rmin);
   }

   if(root->right){
       _getWidthBT_decrement(currentD, rmin);
       _getWidthBT(root->right, lmax, rmin, currentD);
       _getWidthBT_increment(currentD, lmax);
   }

   return root;
}

int
getWidthBT(tree_t *tree){
    if(!tree || !tree->root) return 0;
    if(!tree->root->left && !tree->root->right) return 0;
    int lmax = 0, rmin = 0, currentD = 0;
    _getWidthBT(tree->root, &lmax, &rmin, &currentD);
    return (lmax - rmin);
}


int
_getHeightBT(tree_node_t *root){
	// if i am leaf
	if(root->left == NULL && root->right == NULL)
		return 0;
	
	// if my left child is NULL but not right child
	if(root->left == NULL && root->right)
		return _getHeightBT(root->right) + 1;

	// if my left child is NULL but not right child
	if(root->left && root->right == NULL)
		return _getHeightBT(root->left) + 1;

	// if both childen are present
	if(root->left && root->right)
		return MAX(_getHeightBT(root->left), _getHeightBT(root->right)) + 1; 
}

int
getHeightBT(tree_t *tree){
	if(!tree || !tree->root) return 0;
	return _getHeightBT(tree->root);
}

void
computeLD(tree_node_t *root, int d, int *lmax){
	memcpy(root + 1, &d, sizeof(int));
	if(*lmax < d)
		*lmax = d;

	if(root->left)
		computeLD(root->left, d + 1, lmax);

	if(root->right)
		computeLD(root->right, d - 1, lmax);
}


void
BFS(tree_t *tree, int lmax){
	if(!tree || !tree->root) return ;
	tree_node_t *node = NULL;
	Queue_t *q = initQ();
	int iter = 1 << 1;	
	int j = 0;
	
	printf("%d\n", tree->root->data);
        enqueue(q, (void *)tree->root);	
	while(is_queue_empty(q) == FALSE){
		node = (tree_node_t *)deque(q);
		if(!node) {
			j++;
			continue;
		}

		if(node->left){
			printf("%d   ", node->left->data);
			enqueue(q, (void *)node->left);
		}
		else
			enqueue(q, NULL);

		if(node->right){
			printf("%d   ", node->right->data);
			enqueue(q, (void *)node->right);
		}
		else
			enqueue(q, NULL);

		j+=2;
		if(j  == iter){
			printf("\n");
			iter = iter << 1;
			j = 0;
		}
	}
	printf("\n");
}


typedef struct dia_res {
	int diam;
	int height;
	tree_node_t *left_end;
	tree_node_t *right_end;
} dia_res_t;

dia_res_t
_getDiameterBT(tree_node_t *root){

	dia_res_t lchild, rchild, res;
	memset(&lchild,   0, sizeof(dia_res_t));
	memset(&rchild,   0, sizeof(dia_res_t));
	memset(&res,  	  0, sizeof(dia_res_t));

	//case 1: if NULL

	if(!root)
		return res;	

	lchild = _getDiameterBT(root->left);
	rchild = _getDiameterBT(root->right);

	//case 2: leaf node
	if(!root->left && !root->right){
		res.diam = 1;
		res.height = 0;
		res.left_end  = root;
		res.right_end = root;
		return res;
	}

	//case 3 : half node
	if(root->left && !root->right){
		res.diam = lchild.diam;
		res.height = lchild.height + 1;
		res.left_end = lchild.left_end;
		res.right_end = lchild.right_end;
		return res;	
	}

	if(!root->left && root->right){
		res.diam = rchild.diam;
		res.height = rchild.height + 1;
		res.left_end = rchild.left_end;
		res.right_end = rchild.right_end;
		return res;	
	}

	//case 4: full internal node
	int curr_diam = lchild.height + rchild.height + 2;
	int current_height = (lchild.height >= rchild.height) ? lchild.height + 1 : rchild.height + 1;

	//if(a >= b)
	if(curr_diam >= lchild.diam){
		if(curr_diam >= rchild.diam){
			res.diam = curr_diam;
			res.height = current_height;
			res.left_end = lchild.left_end;
			res.right_end = rchild.right_end;
			return res;
		}
		// rchild is max
		res.diam = rchild.diam;
		res.height = current_height;
		res.left_end = rchild.left_end;
		res.right_end = rchild.right_end;
		return res;
	}

	if(lchild.diam >= rchild.diam){
		res.diam = lchild.diam;
		res.height = current_height;
		res.left_end = lchild.left_end;
		res.right_end = lchild.right_end;
		return res;
	}

	res.diam = rchild.diam;
	res.height = current_height;
	res.left_end = rchild.left_end;
	res.right_end = rchild.right_end;
	return res;
}


dia_res_t
getDiameterBT(tree_t *tree){
	dia_res_t res;
	memset(&res, 0, sizeof(dia_res_t));
	if(!tree) return res;
	if(!tree->root) return res;
	res = _getDiameterBT(tree->root);
	return res;
}



void
printTree(tree_t *tree){
	if(!tree || !tree->root) return ;
	int lmax = 0, d = 0;
	computeLD(tree->root, d, &lmax);
	BFS(tree, lmax);
}


typedef struct _ans_t{
	tree_node_t *succ;
	char is_search_on;
} ans_t;



#define is_ans_empty(ans) (ans.succ == NULL && ans.is_search_on ==0)

static ans_t
_InorderSucc(tree_node_t *root, int n){
	ans_t lres,rres;
	memset(&lres, 0, sizeof(ans_t));
	memset(&rres, 0, sizeof(ans_t));		

	if(!root)	return lres;

	if(root->data == n){
		lres.succ = root;
		lres.is_search_on = 1;
		return lres;
	}

	lres = _InorderSucc(root->left, n);
	rres = _InorderSucc(root->right, n);

	// case 1 : if i am leaf
	if(root->left == NULL && root->right == NULL){
		return lres;
	}

	// case 2 : if i have only left child
	if(root->left && root->right == NULL){
		if(lres.is_search_on == 1){
			lres.succ = root;
			lres.is_search_on = 0;
			return lres;
		}
		return lres;
	}

	// case 3 : if i have only right child
	if(root->left == NULL && root->right){
		return rres;
	}

	// cae 4 : if i am internal node with both children
	if(is_ans_empty(lres) && !is_ans_empty(rres))
		return rres;

	if(!is_ans_empty(lres) && is_ans_empty(rres)){
		if(lres.is_search_on == 1){
			lres.succ = root;
			lres.is_search_on = 0;
			return lres;
		}
		return lres;
	}

	// if both ans are empty
	return lres;

	// if both ans are not empty
	// impossible case	
}


tree_node_t *
InorderSucc(tree_t *tree, int n){
	if(!tree || !tree->root)
		return NULL;
	return _InorderSucc(tree->root, n).succ;
}



#if 1
int 
main(int argc, char **argv){
    int rc = SUCCESS;
    if(argc > 1)
        enableLogging = TREE_TRUE;
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
    add_tree_node_by_value(tree,  36);
    add_tree_node_by_value(tree,  35);
#endif

#if 0

	tree_node_t *node = InorderSucc(tree, 10);
	printf("Inorder successor = %d\n", node->data);
#endif

#if 0
   all_branch_sum(tree);
#endif

#if 0

    printf("Diameter of the tree = %d\n", getWidthBT(tree));

#endif
#if 0
    tree->root = init_tree_node(-10);
    tree->root->left = init_tree_node(-2);
    tree->root->right = init_tree_node(-10);
    tree->root->left->left = init_tree_node(-20);
    tree->root->left->right = init_tree_node(-1);
    tree->root->right->right = init_tree_node(2500);
    tree->root->right->right->left = init_tree_node(-3);
    tree->root->right->right->right = init_tree_node(-4);
#endif

#if 0
    /*Testing Non-Recursive Traversals*/
    printAllTraversals(tree);
    PostorderNR(tree);
    InorderNR(tree);
    PreorderNR(tree);
#endif

#if 0
    /*Testing Mirror images*/
    printAllTraversals(tree);
    MirrorImageByPostorder(tree);
    MirrorImageByPostorder(tree);
    printAllTraversals(tree);
#endif

    /*Testing Maximum Sum path*/
#if 1
    printf("MaxSumPath = %d\n",  MaxSumPath(tree));
#endif

    /*Testing halfnode removal*/
#if 0
    removeHalfNodes(tree);
    printAllTraversals(tree);
#endif

#if 0
    /*Testing constructAllBST*/
    int arr[] = {0,1,2,3,4,5};
    constructAllBST(arr, 0, 5);
#endif

#if 0
/*Testing Lowest Common Ancestor*/
    printf("LowestCommonAncestor = %d\n", (LowestCommonAncestor(tree, 1,   38))->data);
    printf("LowestCommonAncestor = %d\n", (LowestCommonAncestor(tree, 1,  120))->data);
    printf("LowestCommonAncestor = %d\n", (LowestCommonAncestor(tree, 35,  30))->data);
    printf("LowestCommonAncestor = %d\n", (LowestCommonAncestor(tree, 100,100))->data);
    printf("LowestCommonAncestor = %d\n", (LowestCommonAncestor(tree, 75,  75))->data);
#endif

#if 0
    Postorder(tree);
    printf("node#1 = %d\n", getFirstNodebyPostOrder(tree));
    int i = 2, N = 8;
    for(i = 2; i <= N; i++){
        printf("node#%d = %d\n", i, getNextNodebyPostOrder(tree->stack));
    }
#endif

#if 0
    /*Testing threaded Biary tree*/
    /*Either execute rightThreadedBST Or leftThreadedBT*/
    rightThreadedBST(tree);
    //leftThreadedBST(tree);
    apply_gdb(tree); 
#endif

/* Checking undoRightThreadedBST */
#if 0
    rightThreadedBST(tree);
    undoRightThreadedBST(tree);
    printAllTraversals(tree);
#endif

/* Checking undoiLeftThreadedBST */
#if 0
    leftThreadedBST(tree);
    undoLeftThreadedBST(tree);
    printAllTraversals(tree);
#endif

/*Testing constuctCompleteThreadedBST*/
#if 0
    constuctCompleteThreadedBST(tree);
    apply_gdb(tree);
#endif

    /*Testing BSTtreeToDoublyLinkedList*/
#if 0
    tree_node_t *start_node = BSTtreeToDoublyLinkedList(tree);
    Queue_t *q = initQ();
    // bring the start_node to first node of the doubly linked list
     while(start_node->left){
        start_node = start_node->left;
    }
    printf("printing forward:\n");
    while(start_node->right){
        printf("%d ", start_node->data);
	enqueue(q, (void *)start_node);
        start_node = start_node->right;
    }

    enqueue(q, (void *)start_node);
    printf("%d\n", start_node->data);

    printf("printing backwards:\n");
    while(start_node->left){
        printf("%d ", start_node->data);
        start_node = start_node->left;
    }

   printf("%d\n", start_node->data);

   printf("printing Queue\n");
   print_Queue(q);
   void *elem = NULL;
   while(!is_queue_empty(q)){
   	elem = deque(q);
	if(elem)
		printf("node %d is Dequeued\n", ((tree_node_t *)elem)->data);
	print_Queue(q);
   }

   
    
#endif

/* Tesintg DepthOfTreeNode() */
#if 0
    printf("depth of node %d  = %d\n", 233, depthoftreenode(tree, 233));
    printf("depth of node %d  = %d\n", 38, depthoftreenode(tree, 38));
    printf("depth of node %d  = %d\n", 120, depthoftreenode(tree, 120));
#endif

    /* Tesintg getNodePtrBST() */
#if 0
    //printf("elem = %d, node_ptr_value = %d\n", 233, getNodePtrBST(tree, 233)->data);
    printf("elem = %d, node_ptr_value = %d\n", 38, getNodePtrBST (tree,   38)->data);
    printf("elem = %d, node_ptr_value = %d\n", 120, getNodePtrBST(tree, 120)->data);
#endif

    /* Testing allDescendantNodesAtDistance */
#if 0
    tree_node_t* list = allDescendantNodesAtDistance(tree, 50, 0);
    if(!list){
        printf("NO such elements\n");
        return rc;
    }

    while(list->right){
        printf("%d -> ", list->data);
        list = list->right;
    }
        printf("%d\n", list->data);

        printf("Sum = %d\n", SumOfNodesAtDepth(tree, 0));
#endif

/* Testing getNthAncestor()*/
#if 0
    tree_node_t *ancestor = getNthAncestor(tree, 38, 4);
    if(ancestor)
        printf("Ancestor node of 38 at height 4  = %d\n", ancestor->data);
    else
         printf("Ancestor node is NULL\n");
    ancestor = getNthAncestor(tree, 38, 3);
    if(ancestor)
        printf("Ancestor node of 38 at height 3  = %d\n", ancestor->data);
    else
         printf("Ancestor node is NULL\n");
#endif

#if 0
	// testing height of tree
	printf(" Height = %d\n", getHeightBT(tree));
#endif

#if 0
	printTree(tree);
#endif

#if 0
	dia_res_t res;
	memset(&res, 0 , sizeof(dia_res_t));
	res = getDiameterBT(tree);
	printf("Diameter = %d\n", res.diam);
	printf("left  end = %d\n", res.left_end->data);
	printf("right end = %d\n", res.right_end->data);
#endif
    
    return rc;
}
#endif
