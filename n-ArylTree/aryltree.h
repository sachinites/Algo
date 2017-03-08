#ifndef __ARYLTREE__
#define __ARYLTREE__


typedef struct _aryltreenode_t{
	void *data;
	int n_children;
	void *child_list;
} aryl_node_t;

typedef int (*_compare)(void *key1, void *key2);

typedef struct _aryl_tree_t{
	int count;
	aryl_node_t *root;
	_compare compare;
} aryl_tree_t;

aryl_node_t* init_aryl_node(int n_children);
void free_aryl_node(aryl_node_t *aryl_node);
void free_aryl_tree(aryl_tree_t *ayrl_tree);
aryl_tree_t* init_aryl_tree();
aryl_node_t* aryl_tree_lookup(aryl_tree_t *ayrl_tree, void *key);


#endif
