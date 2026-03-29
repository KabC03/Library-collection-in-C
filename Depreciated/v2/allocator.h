#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Block {
    //Start not needed since data begins right after struct
    uint32_t end;
    struct Block *next;
    struct Block *prev;
} Block;




#endif
