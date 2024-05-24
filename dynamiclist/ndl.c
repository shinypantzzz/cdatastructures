#include "dllib.h"

NullableDynamicList CreateNDL(const unsigned int elementSize) {
    return CreateDL(elementSize+1);
}

void FreeNDL(NullableDynamicList dl) {
    FreeDL(dl);
}

unsigned int IsNullNDL(const NullableDynamicList dl, unsigned int index) {
    return *(char *)(GetNDL(dl, index) + (dl.elementSize - 1)) == 0;
}

void SetNullNDL(NullableDynamicList dl, const unsigned int index) {
    memset(GetNDL(dl, index) + (dl.elementSize - 1), 0, 1);
}

void SetNotNullNDL(NullableDynamicList dl, const unsigned int index) {
    memset(GetNDL(dl, index) + (dl.elementSize - 1), 1, 1);
}

void AppendNDL(NullableDynamicList *dl, ValPtr valuePtr) {
    if (dl->appendIndex >= dl->length) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length*dl->elementSize);
    }
    memcpy(dl->array + dl->appendIndex*dl->elementSize, valuePtr, dl->elementSize-1);
    SetNotNullNDL(*dl, dl->appendIndex);
    dl->appendIndex++;
}

void ClearNDL(NullableDynamicList *dl) {
    ClearDL(dl);
}

NullableDynamicList CopyNDL(const NullableDynamicList dl) {
    return CopyDL(dl);
}

ValPtr GetNDL(const NullableDynamicList dl, const unsigned int index) {
    return GetDL(dl, index);
}

void SetNDL(NullableDynamicList *dl, const unsigned int index, ValPtr valuePtr) {
    if (dl->appendIndex <= index) {
        if (dl->length <= index) {
            const unsigned int prevLength = dl->length;
            while (dl->length <= index) dl->length*=2;
            dl->array = realloc(dl->array, dl->length*dl->elementSize);
            memset(GetDL(*dl, prevLength), 0, (dl->length - prevLength)*dl->elementSize);
        }
        dl->appendIndex = index + 1;
    }
    memcpy(GetDL(*dl, index), valuePtr, dl->elementSize-1);
    SetNotNullNDL(*dl, index);
}

unsigned int CountNDL(const NullableDynamicList dl, ValPtr valuePtr) {
    int count = 0;
    for (int i = 0; i < dl.appendIndex; i++) {
        if (memcmp(valuePtr, GetDL(dl, i), dl.elementSize-1) == 0) count++;
    }
    return count;
}

unsigned int ExtendNDL(NullableDynamicList *dest, const NullableDynamicList src) {
    return ExtendDL(dest, src);
}

int IndexNDL(const NullableDynamicList dl, ValPtr valuePtr) {
    for (unsigned int i = 0; i < dl.appendIndex; i++) {
        if (!IsNullNDL(dl, i) && memcmp(GetNDL(dl, i), valuePtr, dl.elementSize-1) == 0) {
            return i;
        }
    }
    return -1;
}

void InsertNDL(NullableDynamicList *dl, ValPtr valuePtr, const unsigned int index) {
    if (index >= dl->appendIndex) {
        return SetNDL(dl, index, valuePtr);
    }
    if (dl->length <= dl->appendIndex) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length * dl->elementSize);
    }

    memmove(dl->array + (index+1)*dl->elementSize, dl->array + index*dl->elementSize, (dl->appendIndex-index)*dl->elementSize);
    SetNDL(dl, index, valuePtr);
    dl->appendIndex++;
}

ValPtr PopLastNDL(NullableDynamicList *dl) {
    return PopLastDL(dl);
}

ValPtr PopNDL(NullableDynamicList *dl, const unsigned int index) {
    return PopDL(dl, index);
}

unsigned int RemoveNDL(NullableDynamicList *dl, ValPtr valuePtr) {
    unsigned int index = IndexNDL(*dl, valuePtr);
    if (index == -1) return 0;
    PopNDL(dl, index);
    return 1;
}

void ReverseNDL(NullableDynamicList dl) {
    ReverseDL(dl);
}

void SortNDL(NullableDynamicList dl, int (compFunc)(const void *, const void *)) {
    SortDL(dl, compFunc);
}

unsigned int LengthNDL(const NullableDynamicList dl) {
    LengthDL(dl);
}