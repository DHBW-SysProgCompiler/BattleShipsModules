#ifndef HEAPALLOC_H
#define HEAPALLOC_H

// Base of Heap
#define Heap_Base 0x20000000

// Boards for Player and Bot
#define Payerboard_Base Heap_Base
#define Botboard_Base Payerboard_Base + Board_Length
#define Board_Length 100

// Buffer for user-input
#define User_Input_Base Botboard_Base + Board_Length
#define User_input_Length 20

#endif