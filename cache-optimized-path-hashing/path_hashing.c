#include "path_hashing.h"

#define FIRST_HASH(hash, capacity) (hash % (capacity / 2))
#define SECOND_HASH(hash, capacity) ((hash % (capacity / 2)) + (capacity / 2))
#define F_IDX() FIRST_HASH(                       \
    hash((void *)key, strlen(key), path->f_seed), \
    path->addr_capacity)
#define S_IDX() SECOND_HASH(                       \
    hash((void *)key, strlen(key), path->s_seed), \
    path->addr_capacity)
    

void generate_seeds(path_hash *path)
{
    srand(time(NULL));
    do
    {
        path->f_seed = rand();
        path->s_seed = rand();
        path->f_seed = path->f_seed << (rand() % 63);
        path->s_seed = path->s_seed << (rand() % 63);
    } while (path->f_seed == path->s_seed);
}

path_hash *path_init(uint32_t levels, uint32_t reserved_levels)
{
    
    path_hash *path = malloc(sizeof(path_hash));
    if (!path)
    {
        printf("The Initialization Fails1!\n");
        exit(1);
    }
    
    path->levels = levels;
    path->reserved_levels = reserved_levels;
    path->addr_capacity = pow(2, levels - 1);
    path->total_capacity = pow(2, levels) - pow(2, levels - reserved_levels);
    path->size = 0;
    generate_seeds(path);
    
    printf("Path node Size: %d\n", sizeof(path_node));
    path->nodes = calloc(path->total_capacity, sizeof(path_node));
    
    if (!path->nodes)
    {
        printf("The Initialization Fails2!\n");
        exit(1);
    }
    
    printf("The Initialization succeeds!\n");
    printf("The number of levels in path hashing: %d\n", path->levels);
    printf("The number of reserved levels in path hashing: %d\n", path->reserved_levels);
    printf("The number of addressable cells in path hashing: %d\n", path->addr_capacity);
    printf("The total number of cells in path hashing: %d\n", path->total_capacity);
    
    return path;
}


uint8_t path_insert(path_hash *path, uint8_t *key, uint8_t *value)
{
    uint32_t f_idx = F_IDX();
    uint32_t s_idx = S_IDX();
    
    uint32_t sub_f_idx = f_idx;
    uint32_t sub_s_idx = s_idx;
    uint32_t capacity = 0;
    
    int i;      
    for(i = 0; i < path->reserved_levels; i = i + 2){
        if (!path->nodes[capacity + f_idx/2].entry[f_idx%2].token)               
        {
            memcpy(path->nodes[capacity + f_idx/2].entry[f_idx%2].key, key, KEY_LEN);
            memcpy(path->nodes[capacity + f_idx/2].entry[f_idx%2].value, value, VALUE_LEN);
            path->nodes[capacity + f_idx/2].entry[f_idx%2].token = 1;;
            path->size++;
            return 0;
            
        }
        if(!path->nodes[capacity + s_idx/2].entry[s_idx%2].token)
        {
            memcpy(path->nodes[capacity + s_idx/2].entry[s_idx%2].key, key, KEY_LEN);
            memcpy(path->nodes[capacity + s_idx/2].entry[s_idx%2].value, value, VALUE_LEN);
            path->nodes[capacity + s_idx/2].entry[s_idx%2].token = 1;
            path->size++;
            return 0;
        }
        if(!path->nodes[capacity + f_idx/2].entry[2].token)
        {
            memcpy(path->nodes[capacity + f_idx/2].entry[2].key, key, KEY_LEN);
            memcpy(path->nodes[capacity + f_idx/2].entry[2].value, value, VALUE_LEN);
            path->nodes[capacity + f_idx/2].entry[2].token = 1;
            path->size++;
            return 0;
        }
        if(!path->nodes[capacity + s_idx/2].entry[2].token)
        {
            memcpy(path->nodes[capacity + s_idx/2].entry[2].key, key, KEY_LEN);
            memcpy(path->nodes[capacity + s_idx/2].entry[2].value, value, VALUE_LEN);
            path->nodes[capacity + s_idx/2].entry[2].token = 1;
            path->size++;
            return 0;
        }
        sub_f_idx = sub_f_idx/4;
        sub_s_idx = sub_s_idx/4;            
        capacity = (int)((int)pow(2, path->levels + 2) - (int)pow(2, path->levels - i))/6;
        
        f_idx = sub_f_idx;
        s_idx = sub_s_idx;   
    }
    
    printf("Insertion fails: %s\n", key);
    return 1;
}

uint8_t* path_query(path_hash *path, uint8_t *key)
{
    uint32_t f_idx = F_IDX();
    uint32_t s_idx = S_IDX();
    
    uint32_t sub_f_idx = f_idx;
    uint32_t sub_s_idx = s_idx;
    uint32_t capacity = 0;
    
    int i;      
    for(i = 0; i < path->reserved_levels; i = i + 2){   
        if (path->nodes[capacity + f_idx/2].entry[f_idx%2].token)               
        {
            if(strcmp(path->nodes[capacity + f_idx/2].entry[f_idx%2].key, key) == 0){
                return path->nodes[capacity + f_idx/2].entry[f_idx%2].value;
            }
        }
        if (path->nodes[capacity + s_idx/2].entry[s_idx%2].token)
        {
            if(strcmp(path->nodes[capacity + s_idx/2].entry[s_idx%2].key, key) == 0){
                return path->nodes[capacity + s_idx/2].entry[s_idx%2].value;
            }
        }
        if(path->nodes[capacity + f_idx/2].entry[2].token)
        {
            if(strcmp(path->nodes[capacity + f_idx/2].entry[2].key, key) == 0){
                return path->nodes[capacity + f_idx/2].entry[2].value;
            }
        }
        if (path->nodes[capacity + s_idx/2].entry[2].token)
        {
            if(strcmp(path->nodes[capacity + s_idx/2].entry[2].key, key) == 0){
                return path->nodes[capacity + s_idx/2].entry[2].value;
            }
        }
        sub_f_idx = sub_f_idx/4;
        sub_s_idx = sub_s_idx/4;            
        capacity = (int)((int)pow(2, path->levels + 2) - (int)pow(2, path->levels - i))/6;
        
        f_idx = sub_f_idx;
        s_idx = sub_s_idx;   
    }
    
    printf("The key does not exist: %s\n", key);
    return NULL;
}


uint8_t path_delete(path_hash *path, uint8_t *key)
{
    uint32_t f_idx = F_IDX();
    uint32_t s_idx = S_IDX();
    
    uint32_t sub_f_idx = f_idx;
    uint32_t sub_s_idx = s_idx;
    uint32_t capacity = 0;
    
    int i;      
    for(i = 0; i < path->reserved_levels; i = i + 2){   
        if (path->nodes[capacity + f_idx/2].entry[f_idx%2].token)               
        {
            if(strcmp(path->nodes[capacity + f_idx/2].entry[f_idx%2].key, key) == 0){
                path->nodes[capacity + f_idx/2].entry[f_idx%2].token = 0;
                path->size--;
                return 0;
            }
        }
        if (path->nodes[capacity + s_idx/2].entry[s_idx%2].token)
        {
            if(strcmp(path->nodes[capacity + s_idx/2].entry[s_idx%2].key, key) == 0){
                path->nodes[capacity + s_idx/2].entry[s_idx%2].token = 0;
                path->size--;
                return 0;
            }
        }
        if(path->nodes[capacity + f_idx/2].entry[2].token)
        {
            if(strcmp(path->nodes[capacity + f_idx/2].entry[2].key, key) == 0){
                path->nodes[capacity + f_idx/2].entry[2].token = 0;
                path->size--;
                return 0;
            }
        }
        if (path->nodes[capacity + s_idx/2].entry[2].token)
        {
            if(strcmp(path->nodes[capacity + s_idx/2].entry[2].key, key) == 0){
                path->nodes[capacity + s_idx/2].entry[2].token = 0;
                path->size--;
                return 0;
            }
        }
        sub_f_idx = sub_f_idx/4;
        sub_s_idx = sub_s_idx/4;            
        capacity = (int)((int)pow(2, path->levels + 2) - (int)pow(2, path->levels - i))/6;
        
        f_idx = sub_f_idx;
        s_idx = sub_s_idx;   
    }
    
    printf("The key does not exist: %s\n", key);
    return 1;
}







