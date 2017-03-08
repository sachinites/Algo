#include "sort_struct.h"


/* igmp snooping vlan */

void*
igmp_snooping_vlan_get_key(void *_ds){
        igmp_snooping_vlan_t *ds = (igmp_snooping_vlan_t *)_ds;
        return (void *)(ds->vlan_id);
}

int
igmp_snooping_vlan_compare(void *key1, void *key2, int key_size){
        if((int)key1 == (int)key2)
                return 0;
        if((int)key1 < (int)key2)
                return -1;
        return 1;
}

int
igmp_snooping_vlan_get_size(void){
        return sizeof(igmp_snooping_vlan_t);
}


int
igmp_snooping_vlan_get_key_size(void){
        return sizeof(int);
}

/* igmp snooping vlan ends*/
