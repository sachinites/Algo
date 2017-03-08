#include "aryltree.h"
#include <stdlib.h>
#include <memory.h>

aryl_node_t* init_aryl_node(int n_children){
	aryl_node_t *node = calloc(1, sizeof(aryl_node_t));
	if(n_children)
		node->child_list = calloc(n_children, sizeof(aryl_node_t));
	return node;
}

aryl_tree_t* init_aryl_tree(_compare comparefn){
	aryl_tree_t *tree = calloc(1, sizeof(aryl_tree_t));
	tree->compare = comparefn;
	return tree;
}

void free_aryl_node(aryl_node_t *aryl_node){
	//free(aryl_node->data);
	free(aryl_node->child_list);
	free(aryl_node);
}

aryl_node_t* aryl_tree_lookup(aryl_tree_t *ayrl_tree, void *key){
	

}
