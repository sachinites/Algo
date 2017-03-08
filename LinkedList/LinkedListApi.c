#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "LinkedListApi.h"
#include <assert.h>

ll_t* init_singly_ll(){
    return calloc(1, sizeof(ll_t));
}

singly_ll_node_t* singly_ll_init_node(int data){
    singly_ll_node_t* node = calloc(1, sizeof(singly_ll_node_t));
    node->data = data;
    return node;
}

rc_t 
singly_ll_add_node(ll_t* ll, singly_ll_node_t *node){
    if(!ll) return FAILURE;
    if(!node) return FAILURE;
    if(!GET_HEAD_SINGLY_LL(ll)){
        GET_HEAD_SINGLY_LL(ll) = node;
        INC_NODE_COUNT_SINGLY_LL(ll);
        return SUCCESS;
    }

    node->next = GET_HEAD_SINGLY_LL(ll);
    GET_HEAD_SINGLY_LL(ll) = node;
    INC_NODE_COUNT_SINGLY_LL(ll);
    return SUCCESS;
}

rc_t 
singly_ll_add_node_by_val(ll_t *ll, int data){
    singly_ll_node_t* node = singly_ll_init_node(data);
    return singly_ll_add_node(ll, node);
}

rc_t
singly_ll_remove_node(ll_t *ll, singly_ll_node_t *node){
    if(!ll) return FAILURE;
    if(!GET_HEAD_SINGLY_LL(ll) || !node) return SUCCESS;
    singly_ll_node_t *trav = NULL;
    /*if node is not the last node*/
    if(node->next){
        singly_ll_node_t *temp = NULL;
        node->data = node->next->data;
        temp = node->next;
        node->next = node->next->next;
        free(temp);
        DEC_NODE_COUNT_SINGLY_LL(ll);
        return SUCCESS;
    }

    /* if node is the only node in LL*/
    if(ll->node_count == 1 && GET_HEAD_SINGLY_LL(ll) == node){
        free(node);
        GET_HEAD_SINGLY_LL(ll) = NULL;
        DEC_NODE_COUNT_SINGLY_LL(ll);
        return SUCCESS;
    }

    /*if node is the last node of the LL*/
    trav = GET_HEAD_SINGLY_LL(ll);
    while(trav->next != node){
        trav = trav->next;
        continue;
    }
    
    trav->next = NULL;
    free(node);
    DEC_NODE_COUNT_SINGLY_LL(ll);
    return SUCCESS;
}

uint32_t
singly_ll_remove_node_by_value(ll_t *ll, int data){
    if(!ll || !GET_HEAD_SINGLY_LL(ll)) return 0;
    uint32_t curren_node_count = GET_NODE_COUNT_SINGLY_LL(ll);
    singly_ll_node_t* trav = GET_HEAD_SINGLY_LL(ll);
    while(trav != NULL){
        if(trav->data == data){
            singly_ll_remove_node(ll, trav);
	    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
        }
        trav = trav->next;
    }
    return curren_node_count - GET_NODE_COUNT_SINGLY_LL(ll);
}

void print_singly_LL(ll_t *ll){
    if(!ll) {
        printf("Invalid Linked List\n"); 
        return;
    }
    if(is_singly_ll_empty(ll)){
        printf("Empty Linked List\n");
        return;
    }
    
    singly_ll_node_t* trav = GET_HEAD_SINGLY_LL(ll);
    uint32_t i = 0;
    printf("node count = %d\n", GET_NODE_COUNT_SINGLY_LL(ll));
    while(trav){
        printf("%d. Data = %d\n", i, trav->data);
        i++;
        trav = trav->next;
    }
}

bool_t 
is_singly_ll_empty(ll_t *ll){
    if(!ll) assert(0);
    if(ll->node_count == 0)
        return TRUE;
    return FALSE;
}

void 
reverse_singly_ll(ll_t *ll){
   if(!ll) assert(0) ;
   if(is_singly_ll_empty(ll)) return;
   if(GET_NODE_COUNT_SINGLY_LL(ll) == 1) return;
   singly_ll_node_t *p1 = GET_HEAD_SINGLY_LL(ll), 
                    *p2 = ll->head->next, *p3 = NULL;
   p1->next = NULL;
   do{
        p3 = p2->next;
        p2->next = p1;
        p1 = p2;
        p2 = p3;
   }while(p3);
   ll->head = p1;
   return;
}

void _reverse_singly_ll2(singly_ll_node_t *head){

	if(head->next->next)
		_reverse_singly_ll2(head->next);

	head->next->next = head;	
}



void
reverse_singly_ll2(ll_t *ll){
	if(!ll) assert(0) ;
	if(is_singly_ll_empty(ll)) return;

	if(GET_NODE_COUNT_SINGLY_LL(ll) == 1) return;

	singly_ll_node_t *last_node = GET_HEAD_SINGLY_LL(ll);

	while(last_node->next)
		last_node = last_node->next;

	_reverse_singly_ll2(GET_HEAD_SINGLY_LL(ll));

	(GET_HEAD_SINGLY_LL(ll))->next = NULL;

	GET_HEAD_SINGLY_LL(ll) = last_node;
}


void
_reverse_singly_ll3(singly_ll_node_t *prev, singly_ll_node_t *next){

	if(next->next)
		_reverse_singly_ll3(next, next->next);
	
	next->next = prev;
}

void
reverse_singly_ll3(ll_t *ll){
	if(!ll) assert(0) ;
	if(is_singly_ll_empty(ll)) return;

	if(GET_NODE_COUNT_SINGLY_LL(ll) == 1) return;
	
	singly_ll_node_t *last_node = GET_HEAD_SINGLY_LL(ll);

	while(last_node->next)
		last_node = last_node->next;

	_reverse_singly_ll3(NULL, GET_HEAD_SINGLY_LL(ll));

	GET_HEAD_SINGLY_LL(ll) = last_node;
}

int 
main(int argc, char **argv){
    ll_t* list = init_singly_ll();
    singly_ll_add_node_by_val(list, 1);
    singly_ll_add_node_by_val(list, 2);
    singly_ll_add_node_by_val(list, 3);
    singly_ll_add_node_by_val(list, 4);
    singly_ll_add_node_by_val(list, 5);
    singly_ll_add_node_by_val(list, 6);
    singly_ll_add_node_by_val(list, 7);
    singly_ll_add_node_by_val(list, 8);
    singly_ll_add_node_by_val(list, 9);
    singly_ll_add_node_by_val(list, 10);
#if 0
    uint32_t num_nodes_removed = singly_ll_remove_node_by_value(list, 100);
    printf("number of noded removed = %d\n", num_nodes_removed);
    print_singly_LL(list);
#endif
    reverse_singly_ll3(list);
    print_singly_LL(list);

   return 0; 

}

