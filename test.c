#include "path_hashing.h"

int main(int argc, char* argv[])
{
    
    int levels = atoi(argv[1]);                         // INPUT: the number of levels of the complete binary tree in path hashing
    int reserved_levels = atoi(argv[2]);                // INPUT: the number of reserved levels in path hashing
    int insert_num = atoi(argv[3]);                     // INPUT: the number of inserted items
    
    path_hash *p = path_init(levels, reserved_levels);

    uint32_t inserted = 0, removed = 0;
    int i = 0;
    
    for (i = 1; i < insert_num + 1; i++)
    { 
        char *key = malloc(sizeof(int));
        sprintf(key, "%d", i);
        char *value = malloc(sizeof(int));
        sprintf(value, "%d", 2*i);
        if (!path_insert(p, key, value))                                        // Insert an item with <key = i, value = 2i>;
        {
            inserted ++;
        }
        else
            break;
    }   
    printf("\nInserted: %d items\n\n", inserted);
    
    for(i = 1; i < 10; i ++){
        char *key = malloc(sizeof(int));
        char * get_value;
        sprintf(key, "%d", insert_num/i);
        if(get_value = (char *)path_query(p, key))                              // Query an item;
            printf("Query: key = %s: value = %s\n", key, get_value);
    }
    printf("\n");
    
    for(i = 1; i < 21; i = i + 2){
        char *key = malloc(sizeof(int));
        sprintf(key, "%d", i);
        if (!path_delete(p, key))                                               //   Remove an item;
            printf("Removed the item with key = %s\n", key);
    }   

    printf("\nSize: %d\n", p->size);
    printf("Capacity: %d\n", p->total_capacity);
    path_destroy(p, 1);

    return 0;
}