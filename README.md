# Custom Memory Allocator

This project is a simple custom memory allocator implemented in C. It simulates how dynamic memory allocation works by managing a heap using a linked list of memory blocks. The allocator supports initialization, best-fit allocation, freeing memory with coalescing, and heap state debugging.

## Features

- **Heap Initialization**: Allocate a fixed-size heap space.
- **Best-Fit Allocation**: Allocate memory blocks based on the best-fit strategy to minimize fragmentation.
- **Block Splitting**: Divide larger free blocks during allocation to improve utilization.
- **Memory Freeing**: Free a given block and merge adjacent free blocks (coalescing).
- **Heap Visualization**: Print the current state of the heap for debugging.

## File Structure

- `heapmanagement.c`: Main source file containing all logic for initialization, allocation, freeing, and heap visualization.

## How to Compile and Run

```bash
gcc heapmanagement.c -o heap_allocator
./heap_allocator
