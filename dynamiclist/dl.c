#include "dllib.h"

DynamicList CreateDL(const uint8_t elementSize) {
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
    memset(dl->array, 0, dl->appendIndex*dl->elementSize);
    dl->appendIndex = 0;
}

DynamicList CopyDL(const DynamicList dl) {
    DynamicList dlCopy = {.length=dl.length, .appendIndex = dl.appendIndex, .elementSize = dl.elementSize};
    dlCopy.array = (void *)calloc(dl.length, dl.elementSize);
    memcpy(dlCopy.array, dl.array, dl.elementSize*dl.length);

    return dlCopy;
}

ValPtr GetDL(const DynamicList dl, const uint32_t index) {
    return dl.array + index*dl.elementSize;
}

void SetDL(DynamicList *dl, const uint32_t index, ValPtr valuePtr) {
    if (dl->appendIndex <= index) {
        if (dl->length <= index) {
            const uint32_t prevLength = dl->length;
            while (dl->length <= index) dl->length*=2;
            dl->array = realloc(dl->array, dl->length*dl->elementSize);
            memset(GetDL(*dl, prevLength), 0, (dl->length - prevLength)*dl->elementSize);
        }
        dl->appendIndex = index + 1;
    }
    memcpy(GetDL(*dl, index), valuePtr, dl->elementSize);
}

uint32_t CountDL(const DynamicList dl, ValPtr valuePtr) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < dl.appendIndex; i++) {
        if (memcmp(valuePtr, GetDL(dl, i), dl.elementSize) == 0) count++;
    }
    return count;
}

uint8_t ExtendDL(DynamicList *dest, const DynamicList src) {
    if (dest->elementSize != src.elementSize) {
        return 0;
    }
    if (dest->length < dest->appendIndex + src.appendIndex) {
        const uint32_t prevLength = dest->length;
        while (dest->length < dest->appendIndex + src.appendIndex) dest->length*=2;
        dest->array = realloc(dest->array, dest->length*dest->elementSize);
        memset(GetDL(*dest, prevLength), 0, (dest->length - prevLength)*dest->elementSize);
    }
    memcpy(dest->array + dest->appendIndex*dest->elementSize, src.array, src.appendIndex*src.elementSize);
    dest->appendIndex += src.appendIndex;
    return 1;
}

int64_t IndexDL(const DynamicList dl, ValPtr valuePtr) {
    for (uint32_t i = 0; i < dl.appendIndex; i++) {
        if (memcmp(GetDL(dl, i), valuePtr, dl.elementSize) == 0) {
            return i;
        }
    }
    return -1;
}

void InsertDL(DynamicList *dl, ValPtr valuePtr, const uint32_t index) {
    if (index >= dl->appendIndex) {
        return SetDL(dl, index, valuePtr);
    }
    if (dl->length <= dl->appendIndex) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length * dl->elementSize);
    }

    memmove(dl->array + (index+1)*dl->elementSize, dl->array + index*dl->elementSize, (dl->appendIndex-index)*dl->elementSize);
    SetDL(dl, index, valuePtr);
    dl->appendIndex++;
}

ValPtr PopLastDL(DynamicList *dl) {
    if (dl->appendIndex <= 0) return NULL;

    return GetDL(*dl, --dl->appendIndex);
}

ValPtr PopDL(DynamicList *dl, const uint32_t index) {
    if (dl->appendIndex <= 0) return NULL;
    if (index >= dl->appendIndex - 1) return PopLastDL(dl);
    void *tmp = (void *)malloc(dl->elementSize);
    memcpy(tmp, GetDL(*dl, index), dl->elementSize);
    memmove(GetDL(*dl, index), GetDL(*dl, index + 1), (--dl->appendIndex-index)*dl->elementSize);
    memcpy(GetDL(*dl, dl->appendIndex), tmp, dl->elementSize);
    free(tmp);
    return GetDL(*dl, dl->appendIndex);
}

uint8_t RemoveDL(DynamicList *dl, ValPtr valuePtr) {
    int64_t index = IndexDL(*dl, valuePtr);
    if (index == -1) return 0;
    PopDL(dl, (uint32_t)index);
    return 1;
}

void ReverseDL(DynamicList dl) {
    uint32_t l = 0, r = dl.appendIndex - 1;
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

uint32_t LengthDL(const DynamicList dl) {
    return dl.appendIndex;
}