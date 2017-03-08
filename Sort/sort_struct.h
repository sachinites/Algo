#ifndef __SORT_STRUCT__
#define __SORT_STRUCT__

/* igmp snooping vlan Begins */

/* Example : 
1. Define the data structure wwhose array is to be be sorted
*/
typedef struct igmp_snooping_vlan{
        int vlan_id;
        void *data_ptr;
} igmp_snooping_vlan_t;

/* 2. Write a fn prototype to get key for the data structure */
void *
igmp_snooping_vlan_get_key(void *ds);

/* 3. Wite a fn prototype to compare the keys for the DS */
int
igmp_snooping_vlan_compare(void *key1, void *key2, int key_size);

/* 4.  Wite a fn prototype to get structure size */
int
igmp_snooping_vlan_get_size(void);

/* 5. Wite a fn prototype to get key size */
int
igmp_snooping_vlan_get_key_size(void);

/* 6. Write a macro to ease the callback registration*/

/* Define all */
#define IGMP_SNOOPING_VLAN_INIT_SORT(sort, src)		\
do{							\
sort = init_sort(src, igmp_snooping_vlan_get_key,	\
	       igmp_snooping_vlan_compare,		\
	       igmp_snooping_vlan_get_size,		\
	       NULL,					\
	       igmp_snooping_vlan_get_key_size);	\
}while(0);

/* igmp snooping vlan ENDS */
	
#endif
