#include "path_hashing.h"

int main(int argc, char* argv[])
{
    
    int levels = atoi(argv[1]);                         // INPUT: the number of levels of the complete binary tree in path hashing
    int reserved_levels = atoi(argv[2]);                // INPUT: the number of reserved levels in path hashing
    int insert_num = atoi(argv[3]);                     // INPUT: the number of inserted items
    int query_num_start = atoi(argv[4]);
	int query_num_finish = atoi(argv[5]);
	
    path_hash *p = path_init(levels, reserved_levels);

    uint32_t inserted = 0, queried = 0;
    int i = 0;
    uint8_t key[KEY_LEN];
	uint8_t value[VALUE_LEN];
	struct timespec start, finish;
	double single_time;
	clock_t clock_start, clock_finish;
	clock_start = clock();
	
	clock_gettime(CLOCK_MONOTONIC, &start);
    for (i = 1; i < insert_num + 1; i++)
    { 
        snprintf(key, KEY_LEN, "%d", i);
	    snprintf(value, VALUE_LEN, "%d", i*3);
        if (!path_insert(p, key, value))                                        // Insert an item with <key = i, value = 2i>;
        {
            inserted ++;
        }
        else
            break;
    }   
    printf("\nInserted: %d items\n\n", inserted);
    clock_gettime(CLOCK_MONOTONIC, &finish);
	clock_finish = clock();
	single_time = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Insert time: %f %d\n", single_time, inserted);
	printf("Insert clock time: %d %d\n", clock_finish-clock_start, inserted);
	
	uint8_t * get_value;

	clock_start = clock();
	clock_gettime(CLOCK_MONOTONIC, &start);
    for(i = query_num_start; i < query_num_finish; i ++){
		queried ++;
		snprintf(key, KEY_LEN, "%d", i);
        if(get_value = (uint8_t *)path_query(p, key))                              // Query an item;
            ;//printf("Query: key = %s: value = %s\n", key, get_value);
		//else
			//break;
    }
    printf("\n");

	clock_gettime(CLOCK_MONOTONIC, &finish);
	clock_finish = clock();
	single_time = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Query time: %f %d\n", single_time, queried);
	printf("Query clock time: %d %d\n", clock_finish-clock_start, queried);
	
	
		clock_gettime(CLOCK_MONOTONIC, &finish);
	clock_finish = clock();
	single_time = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Query time: %f\n", single_time);
	printf("Query clock time: %d\n", clock_finish-clock_start);
	
		clock_start = clock();
	clock_gettime(CLOCK_MONOTONIC, &start);
    for(i = query_num_start; i < query_num_finish; i ++){
		snprintf(key, KEY_LEN, "%d", i);
        if(!path_delete(p, key))                              // Query an item;
            ;//printf("Delete: key = %s\n", key);
    }
    printf("\n");

	clock_gettime(CLOCK_MONOTONIC, &finish);
	clock_finish = clock();
	single_time = (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("Delete time: %f\n", single_time);
	printf("Delete clock time: %d\n", clock_finish-clock_start);
	
    printf("\nSize: %d\n", p->size);
    printf("Capacity: %d\n", p->total_capacity);
	printf("Space utilization: %f\n", p->size*1.0/p->total_capacity);

    return 0;
}