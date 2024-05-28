#ifndef _DLLIB_H_
#define _DLLIB_H_

#include "stdlib.h"
#include "malloc.h"
#include "mem.h"
#include "stdint.h"

#include "../valptr.h"

#define DL_INITIAL_LENGTH 1

typedef struct DynamicList {
    uint32_t length;
    uint32_t appendIndex;
    const uint8_t elementSize;
    void *array;
} DynamicList;

typedef DynamicList NullableDynamicList;

// DynamicList functions
DynamicList CreateDL(const uint8_t elementSize);
void        FreeDL(DynamicList dl);
ValPtr      GetDL(const DynamicList dl, const uint32_t index);
void        SetDL(DynamicList *dl, const uint32_t index, ValPtr valuePtr);
void        AppendDL(DynamicList *dl, ValPtr valuePtr);
void        ClearDL(DynamicList *dl);
DynamicList CopyDL(const DynamicList dl);
uint32_t    CountDL(const DynamicList dl, ValPtr valuePtr);
uint8_t     ExtendDL(DynamicList *dest, const DynamicList src);
int64_t     IndexDL(const DynamicList dl, ValPtr valuePtr);
void        InsertDL(DynamicList *dl, ValPtr valuePtr, const uint32_t index);
ValPtr      PopLastDL(DynamicList *dl);
ValPtr      PopDL(DynamicList *dl, const uint32_t index);
uint8_t     RemoveDL(DynamicList *dl, ValPtr valuePtr);
void        ReverseDL(DynamicList dl);
void        SortDL(DynamicList dl, int (compFunc)(const void *, const void *));
uint32_t    LengthDL(const DynamicList dl);

// NullableDynamicList functions
NullableDynamicList CreateNDL(const uint8_t elementSize);
void                FreeNDL(NullableDynamicList dl);
uint8_t             IsNullNDL(const NullableDynamicList dl, const uint32_t index);
void                SetNullNDL(NullableDynamicList dl, const uint32_t index);
void                SetNotNullNDL(NullableDynamicList dl, const uint32_t index);
ValPtr              GetNDL(const NullableDynamicList dl, const uint32_t index);
void                SetNDL(NullableDynamicList *dl, const uint32_t index, ValPtr valuePtr);
void                AppendNDL(NullableDynamicList *dl, ValPtr valuePtr);
void                ClearNDL(NullableDynamicList *dl);
NullableDynamicList CopyNDL(const NullableDynamicList dl);
uint32_t            CountNDL(const NullableDynamicList dl, ValPtr valuePtr);
uint8_t             ExtendNDL(NullableDynamicList *dest, const NullableDynamicList src);
int64_t             IndexNDL(const NullableDynamicList dl, ValPtr valuePtr);
void                InsertNDL(NullableDynamicList *dl, ValPtr valuePtr, const uint32_t index);
ValPtr              PopLastNDL(NullableDynamicList *dl);
ValPtr              PopNDL(NullableDynamicList *dl, const uint32_t index);
uint8_t             RemoveNDL(NullableDynamicList *dl, ValPtr valuePtr);
void                ReverseNDL(NullableDynamicList dl);
void                SortNDL(NullableDynamicList dl, int (compFunc)(const void *, const void *));
uint32_t            LengthNDL(const NullableDynamicList dl);

#define foreachdl(dl, var, type) type var; for(uint32_t _i = 0; _i < dl.appendIndex && ((var = Val(type, GetDL(dl, _i))) || 1); _i++)

#endif