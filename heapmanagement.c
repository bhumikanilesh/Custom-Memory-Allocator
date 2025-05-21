#include <stdio.h>
#include <stdlib.h>

// we are creatng  structure that stores the size of block
// checks is its free or no
// and a pointer to the next blcok

typedef struct Block {
    size_t size;            
    int is_free;            
    struct Block* next;     
} Block;

Block* heap_start = NULL;

void initialize_heap(size_t size) {
    heap_start = (Block*)malloc(size);
    heap_start->size = size - sizeof(Block); // total heap size - size of block  basically for checking if heap is full or no
    // or to check the block sizes
    heap_start->is_free = 1;
    heap_start->next = NULL;
}

void* allocate(size_t size) {
    Block* current = heap_start;
    Block* best_fit = NULL;

    while (current != NULL) {
        if (current->is_free && current->size >= size) {  //the remaining size must be >   the requested size
            if (best_fit == NULL || current->size < best_fit->size) { //ini condi or we found a smaller block than the current,the requesed size
                best_fit = current; // then assign curr to bestf
            }
        }
        current = current->next; // else move ahead
    }

    if (best_fit == NULL) {
        printf("memory allocation failed.\n");
        return NULL;
    } 

    // split the block if it is larger than needed
    if (best_fit->size > size + sizeof(Block)) { // checks if the assigned  block is greater than requested size + size required for 
        //the meta data of block
        Block* newblock = (Block*)((char*)best_fit + sizeof(Block) + size); //new block
        newblock->size = best_fit->size - size - sizeof(Block); // new size = bestf size - size - size of meta deta
        newblock->is_free = 1; 
        newblock->next = best_fit->next; //connect the next of new block the next of the best fit

        best_fit->size = size;
        best_fit->next = newblock;
    }

    best_fit->is_free = 0;
    return (void*)(best_fit + 1);
}


void free_memory(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    Block* block_to_free = (Block*)ptr - 1; // reduce the ptr 
    block_to_free->is_free = 1;

    // merges the nearby free blocks
    Block* current = heap_start;
    while (current != NULL) {
        //code to just connect
        if (current->is_free && current->next != NULL && current->next->is_free) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void print_heap() {
    Block* current = heap_start;
    printf("Heap:\n");
    while (current != NULL) {
        printf("Block: %p, Size: %zu, Free: %d\n", (void*)current, current->size, current->is_free);
        current = current->next;
    }
}


int main() {

    initialize_heap(1024);

    void* p1 = allocate(100);
    void* p2 = allocate(2);
    void* p3 = allocate(89);

    printf("After allocation:\n");
    print_heap();
    printf("memory location: %d", &p1);

    //free_memory(p2);
    //printf("After freeing ptr2:\n");
    //print_heap();

    //free_memory(p1);
    //printf("After freeing ptr1:\n");
    //print_heap();

    //free_memory(p3);
    //printf("After freeing ptr3:\n");
    //print_heap();

    return 0;
}