#ifndef _DLLIB_H_
#define _DLLIB_H_

#include "stdlib.h"
#include "malloc.h"
#include "mem.h"
#include "../valptr.h"

#define DL_INITIAL_LENGTH 1

typedef struct DynamicList {
    unsigned int length;
    unsigned int append_index;
    const unsigned int element_size;
    void *array;
} DynamicList;


DynamicList  CreateDL(const unsigned int element_size);
void         FreeDL(DynamicList d);
void         AppendDL(DynamicList *d, ValPtr value_ptr);
void         ClearDL(DynamicList *d);
DynamicList  CopyDL(const DynamicList d);
ValPtr       GetDL(const DynamicList d, const unsigned int index);
unsigned int CountDL(const DynamicList d, ValPtr value_ptr);
unsigned int ExtendDL(DynamicList *dest, const DynamicList src);
int          IndexDL(const DynamicList d, ValPtr value_ptr);
void         InsertDL(DynamicList *d, ValPtr value_ptr, const unsigned int pos);
ValPtr       PopLastDL(DynamicList *d);
ValPtr       PopDL(DynamicList *d, const unsigned int index);
unsigned int RemoveDL(DynamicList *d, ValPtr value_ptr);
void         ReverseDL(DynamicList d);
void         SortDL(DynamicList d, int (comp_func)(const void *, const void *));
unsigned int LengthDL(const DynamicList d);

#define dlforeach(dl, var, type) type var; for(unsigned int _i = 0; _i < dl.append_index && ((var = Val(type, GetDL(dl, _i))) || 1); _i++)

#endif