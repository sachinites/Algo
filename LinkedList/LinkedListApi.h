#define uint8_t char
#define uint32_t unsigned int
#define GET_HEAD_SINGLY_LL(ll) (ll->head)
#define INC_NODE_COUNT_SINGLY_LL(ll) (ll->node_count++)
#define DEC_NODE_COUNT_SINGLY_LL(ll) (ll->node_count--)
#define GET_NODE_COUNT_SINGLY_LL(ll) (ll->node_count)
#define GET_NEXT_NODE_SINGLY_LL(node) (node->next)

typedef enum{
    SUCCESS,
    FAILURE
} rc_t;

typedef enum{
    FALSE,
    TRUE
} bool_t;

typedef struct LL_Node{
    int data;
    struct LL_Node *next;
} singly_ll_node_t;

typedef struct LL{
    uint32_t node_count;
    singly_ll_node_t *head;
} ll_t;

ll_t* init_singly_ll();
singly_ll_node_t* singly_ll_init_node(int data);
rc_t singly_ll_add_node(ll_t *ll, singly_ll_node_t *node);
rc_t singly_ll_add_node_by_val(ll_t *ll, int data);
rc_t singly_ll_remove_node(ll_t *ll, singly_ll_node_t *node);
uint32_t singly_ll_remove_node_by_value(ll_t *ll, int data);
bool_t is_singly_ll_empty(ll_t *ll);
void print_singly_LL(ll_t *ll);
void reverse_singly_ll(ll_t *ll);
void reverse_singly_ll2(ll_t *ll);
void reverse_singly_ll3(ll_t *ll);
