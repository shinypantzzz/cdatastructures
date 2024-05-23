#ifndef _DLLIB_H_
#define _DLLIB_H_

#include "stdlib.h"
#include "malloc.h"
#include "mem.h"
#include "../valptr.h"

#define DL_INITIAL_LENGTH 1

typedef struct DynamicList {
    unsigned int length;
    unsigned int appendIndex;
    const unsigned int elementSize;
    void *array;
} DynamicList;


DynamicList  CreateDL(const unsigned int elementSize);
void         FreeDL(DynamicList dl);
ValPtr       GetDL(const DynamicList dl, const unsigned int index);
void         SetDL(DynamicList dl, const unsigned int index, ValPtr valuePtr);
void         AppendDL(DynamicList *dl, ValPtr valuePtr);
void         ClearDL(DynamicList *dl);
DynamicList  CopyDL(const DynamicList dl);
unsigned int CountDL(const DynamicList dl, ValPtr valuePtr);
unsigned int ExtendDL(DynamicList *dest, const DynamicList src);
int          IndexDL(const DynamicList dl, ValPtr valuePtr);
void         InsertDL(DynamicList *dl, ValPtr valuePtr, const unsigned int pos);
ValPtr       PopLastDL(DynamicList *dl);
ValPtr       PopDL(DynamicList *dl, const unsigned int index);
unsigned int RemoveDL(DynamicList *dl, ValPtr valuePtr);
void         ReverseDL(DynamicList dl);
void         SortDL(DynamicList dl, int (compFunc)(const void *, const void *));
unsigned int LengthDL(const DynamicList dl);

#define dlforeach(dl, var, type) type var; for(unsigned int _i = 0; _i < dl.appendIndex && ((var = Val(type, GetDL(dl, _i))) || 1); _i++)

#endif