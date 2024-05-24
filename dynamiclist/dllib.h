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

typedef DynamicList NullableDynamicList;

// DynamicList functions
DynamicList  CreateDL(const unsigned int elementSize);
void         FreeDL(DynamicList dl);
ValPtr       GetDL(const DynamicList dl, const unsigned int index);
void         SetDL(DynamicList *dl, const unsigned int index, ValPtr valuePtr);
void         AppendDL(DynamicList *dl, ValPtr valuePtr);
void         ClearDL(DynamicList *dl);
DynamicList  CopyDL(const DynamicList dl);
unsigned int CountDL(const DynamicList dl, ValPtr valuePtr);
unsigned int ExtendDL(DynamicList *dest, const DynamicList src);
int          IndexDL(const DynamicList dl, ValPtr valuePtr);
void         InsertDL(DynamicList *dl, ValPtr valuePtr, const unsigned int index);
ValPtr       PopLastDL(DynamicList *dl);
ValPtr       PopDL(DynamicList *dl, const unsigned int index);
unsigned int RemoveDL(DynamicList *dl, ValPtr valuePtr);
void         ReverseDL(DynamicList dl);
void         SortDL(DynamicList dl, int (compFunc)(const void *, const void *));
unsigned int LengthDL(const DynamicList dl);

// NullableDynamicList functions
NullableDynamicList CreateNDL(const unsigned int elementSize);
void                FreeNDL(NullableDynamicList dl);
unsigned int        IsNullNDL(const NullableDynamicList dl, const unsigned int index);
void                SetNullNDL(NullableDynamicList dl, const unsigned int index);
void                SetNotNullNDL(NullableDynamicList dl, const unsigned int index);
ValPtr              GetNDL(const NullableDynamicList dl, const unsigned int index);
void                SetNDL(NullableDynamicList *dl, const unsigned int index, ValPtr valuePtr);
void                AppendNDL(NullableDynamicList *dl, ValPtr valuePtr);
void                ClearNDL(NullableDynamicList *dl);
NullableDynamicList CopyNDL(const NullableDynamicList dl);
unsigned int        CountNDL(const NullableDynamicList dl, ValPtr valuePtr);
unsigned int        ExtendNDL(NullableDynamicList *dest, const NullableDynamicList src);
int                 IndexNDL(const NullableDynamicList dl, ValPtr valuePtr);
void                InsertNDL(NullableDynamicList *dl, ValPtr valuePtr, const unsigned int index);
ValPtr              PopLastNDL(NullableDynamicList *dl);
ValPtr              PopNDL(NullableDynamicList *dl, const unsigned int index);
unsigned int        RemoveNDL(NullableDynamicList *dl, ValPtr valuePtr);
void                ReverseNDL(NullableDynamicList dl);
void                SortNDL(NullableDynamicList dl, int (compFunc)(const void *, const void *));
unsigned int        LengthNDL(const NullableDynamicList dl);

#define foreachdl(dl, var, type) type var; for(unsigned int _i = 0; _i < dl.appendIndex && ((var = Val(type, GetDL(dl, _i))) || 1); _i++)

#endif