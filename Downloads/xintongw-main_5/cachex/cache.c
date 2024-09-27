//
// Created by Alex Brodsky on 2024-03-10.
//

#include "cache.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    unsigned char valid;
    unsigned long tag;
    unsigned char block[32];
}line;//THE lins in the set
typedef struct{
    line *E_line;
}Set;//the set of the cache
typedef struct{
    Set *set;
    unsigned int line_num;
    unsigned int set_num;
    unsigned char sign;
}cache;//the cache
int poww(int x,int y){
	int item=x;
	for(int i=1;i<y;i++){
		x*=item;
	}
	return x;
}
//Initialize cache
cache* init(int set_num, int line_num){
    fprintf(stderr, "called init\n"); 
    int current_offset = 0;
    
    cache *ptr_cache=(cache *)c_info.F_memory;
    ptr_cache->sign=1;//Mark the initial cache
    ptr_cache->set_num=set_num;//Count the number of sets in the cache
    ptr_cache->line_num=line_num;//Count the number of lines in a set

    // after cache struct
    current_offset += sizeof(cache);
	//The current set position is the initial plus struct
    Set *set=(Set *)(c_info.F_memory + current_offset);
    ptr_cache->set = set;
    current_offset += sizeof(Set) * set_num;
    
    for(int i=0;i<ptr_cache->set_num;i++){
        set[i].E_line = (line *)(c_info.F_memory + current_offset);
	current_offset += sizeof(line) * line_num;
        //The initial position of each line is the position of the first line plus sizeof(line)
	for(int j=0;j<line_num;j++) {
		set[i].E_line[j].valid = 0;
	}
    }
    return ptr_cache;
}
extern int cache_get(unsigned long address, unsigned long *value) {
    cache *ptr=(cache *)c_info.F_memory;
   int set_num=(c_info.F_size-sizeof(cache))/(sizeof(Set)+sizeof(line));//caculate the number of set
    if(ptr->sign==0){
        ptr=init(set_num, 1);//One line per set
    }
    int n=1,sign=1;
    while(sign){
        if((int)poww(2,n)<set_num){
            n++;
            if((int)poww(2,n)>=set_num){
                sign=0;
            }
        }
    }
    
    fprintf(stderr, "pow %d\n", poww(2,n));
    fprintf(stderr, "set %d\n", set_num);
    unsigned int index=(address>>5)%set_num;
    //(address / DATA_SIZE) Calculate the data block number corresponding to the address
    unsigned long tag=address/(32*set_num);
    int offset=address%32;//Here offset is any position of the block
    fprintf(stderr, "offsetL %d\n", offset);

    Set *ll=(Set *)((unsigned char *)ptr + sizeof(cache));
    if(ll[index].E_line->valid&&ll[index].E_line->tag==tag){//cache hit
	if(offset<=24){
	   memcpy(value, &((ll[index].E_line)->block[offset]), sizeof(unsigned long));
	}//address
	else{
	  memget(address, &ll[index].E_line->block,32);
	  memcpy(value, &((ll[index].E_line)->block[0]), sizeof(unsigned long));
	}
        return 1;
    }
    else{//cache miss
        ll[index].E_line->valid=1;
        ll[index].E_line->tag=tag;	
        memget(address-offset, &ll[index].E_line->block,32);
        memcpy(value, &((ll[index].E_line)->block[offset]), sizeof(unsigned long));
        return 0;
    }
  return 0;
}
