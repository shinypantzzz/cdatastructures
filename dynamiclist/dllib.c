#include "dllib.h"

DynamicList CreateDL(const unsigned int elementSize) {
    DynamicList dl = {.length=DL_INITIAL_LENGTH, .appendIndex = 0, .elementSize = elementSize};
    dl.array = (void *)calloc(dl.length, dl.elementSize);
    return dl;
}

void FreeDL(DynamicList dl) {
    free(dl.array);
}

void AppendDL(DynamicList *dl, ValPtr valuePtr) {
    if (dl->appendIndex >= dl->length) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length*dl->elementSize);
    }
    memcpy(dl->array + dl->appendIndex*dl->elementSize, valuePtr, dl->elementSize);
    dl->appendIndex++;
}

void ClearDL(DynamicList *dl) {
    dl->appendIndex = 0;
}

DynamicList CopyDL(const DynamicList dl) {
    DynamicList dlCopy = {.length=dl.length, .appendIndex = dl.appendIndex, .elementSize = dl.elementSize};
    dlCopy.array = (void *)calloc(dl.length, dl.elementSize);
    memcpy(dlCopy.array, dl.array, dl.elementSize*dl.appendIndex);

    return dlCopy;
}

ValPtr GetDL(const DynamicList dl, const unsigned int index) {
    return dl.array + index*dl.elementSize;
}

void SetDL(DynamicList dl, const unsigned int index, ValPtr valuePtr) {
    memcpy(GetDL(dl, index), valuePtr, dl.elementSize);
}

unsigned int CountDL(const DynamicList dl, ValPtr valuePtr) {
    int count = 0;
    for (int i = 0; i < dl.appendIndex; i++) {
        if (memcmp(valuePtr, GetDL(dl, i), dl.elementSize) == 0) count++;
    }
    return count;
}

unsigned int ExtendDL(DynamicList *dest, const DynamicList src) {
    if (dest->elementSize != src.elementSize) {
        return 0;
    }
    if (dest->length < dest->appendIndex + src.appendIndex) {
        dest->length = 1;
        while (dest->length < dest->appendIndex + src.appendIndex) dest->length*=2;
        dest->array = realloc(dest->array, dest->length*dest->elementSize);
    }
    memcpy(dest->array + dest->appendIndex*dest->elementSize, src.array, src.appendIndex*src.elementSize);
    dest->appendIndex += src.appendIndex;
    return 1;
}

int IndexDL(const DynamicList dl, ValPtr valuePtr) {
    for (unsigned int i = 0; i < dl.appendIndex; i++) {
        if (memcmp(GetDL(dl, i), valuePtr, dl.elementSize) == 0) {
            return i;
        }
    }
    return -1;
}

void InsertDL(DynamicList *dl, ValPtr valuePtr, const unsigned int pos) {
    if (pos >= dl->appendIndex) {
        return AppendDL(dl, valuePtr);
    }
    if (dl->length <= dl->appendIndex) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length * dl->elementSize);
    }

    memmove(dl->array + (pos+1)*dl->elementSize, dl->array + pos*dl->elementSize, (dl->appendIndex-pos)*dl->elementSize);
    memcpy(GetDL(*dl, pos), valuePtr, dl->elementSize);
    dl->appendIndex++;
}

ValPtr PopLastDL(DynamicList *dl) {
    if (dl->appendIndex <= 0) return NULL;

    return GetDL(*dl, --dl->appendIndex);
}

ValPtr PopDL(DynamicList *dl, const unsigned int index) {
    if (dl->appendIndex <= 0) return NULL;
    if (index >= dl->appendIndex - 1) return PopLastDL(dl);
    void *tmp = (void *)malloc(dl->elementSize);
    memcpy(tmp, GetDL(*dl, index), dl->elementSize);
    memmove(GetDL(*dl, index), GetDL(*dl, index + 1), (--dl->appendIndex-index)*dl->elementSize);
    memcpy(GetDL(*dl, dl->appendIndex), tmp, dl->elementSize);
    free(tmp);
    return GetDL(*dl, dl->appendIndex);
}

unsigned int RemoveDL(DynamicList *dl, ValPtr valuePtr) {
    unsigned int index = IndexDL(*dl, valuePtr);
    if (index == -1) return 0;
    PopDL(dl, index);
    return 1;
}

void ReverseDL(DynamicList dl) {
    unsigned int l = 0, r = dl.appendIndex - 1;
    void *tmp = (void *)malloc(dl.elementSize);
    while(l < r) {
        memcpy(tmp, GetDL(dl, l), dl.elementSize);
        memcpy(GetDL(dl, l), GetDL(dl, r), dl.elementSize);
        memcpy(GetDL(dl, r), tmp, dl.elementSize);
        l++; r--;
    }
    free(tmp);
}

void SortDL(DynamicList dl, int (compFunc)(const void *, const void *)) {
    qsort(dl.array, dl.appendIndex, dl.elementSize, compFunc);
}

unsigned int LengthDL(const DynamicList dl) {
    return dl.appendIndex;
}