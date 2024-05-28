#include "dllib.h"

NullableDynamicList CreateNDL(const uint8_t elementSize) {
    return CreateDL(elementSize+1);
}

void FreeNDL(NullableDynamicList dl) {
    FreeDL(dl);
}

uint8_t IsNullNDL(const NullableDynamicList dl, const uint32_t index) {
    return *(char *)(GetNDL(dl, index) + (dl.elementSize - 1)) == 0;
}

void SetNullNDL(NullableDynamicList dl, const uint32_t index) {
    memset(GetNDL(dl, index) + (dl.elementSize - 1), 0, 1);
}

void SetNotNullNDL(NullableDynamicList dl, const uint32_t index) {
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

ValPtr GetNDL(const NullableDynamicList dl, const uint32_t index) {
    return GetDL(dl, index);
}

void SetNDL(NullableDynamicList *dl, const uint32_t index, ValPtr valuePtr) {
    if (dl->appendIndex <= index) {
        if (dl->length <= index) {
            const uint32_t prevLength = dl->length;
            while (dl->length <= index) dl->length*=2;
            dl->array = realloc(dl->array, dl->length*dl->elementSize);
            memset(GetDL(*dl, prevLength), 0, (dl->length - prevLength)*dl->elementSize);
        }
        dl->appendIndex = index + 1;
    }
    memcpy(GetDL(*dl, index), valuePtr, dl->elementSize-1);
    SetNotNullNDL(*dl, index);
}

uint32_t CountNDL(const NullableDynamicList dl, ValPtr valuePtr) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < dl.appendIndex; i++) {
        if (!IsNullNDL(dl, i) && memcmp(valuePtr, GetDL(dl, i), dl.elementSize-1) == 0) count++;
    }
    return count;
}

uint8_t ExtendNDL(NullableDynamicList *dest, const NullableDynamicList src) {
    return ExtendDL(dest, src);
}

int64_t IndexNDL(const NullableDynamicList dl, ValPtr valuePtr) {
    for (uint32_t i = 0; i < dl.appendIndex; i++) {
        if (!IsNullNDL(dl, i) && memcmp(GetNDL(dl, i), valuePtr, dl.elementSize-1) == 0) {
            return i;
        }
    }
    return -1;
}

void InsertNDL(NullableDynamicList *dl, ValPtr valuePtr, const uint32_t index) {
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

ValPtr PopNDL(NullableDynamicList *dl, const uint32_t index) {
    return PopDL(dl, index);
}

uint8_t RemoveNDL(NullableDynamicList *dl, ValPtr valuePtr) {
    int64_t index = IndexNDL(*dl, valuePtr);
    if (index == -1) return 0;
    PopNDL(dl, (uint32_t)index);
    return 1;
}

void ReverseNDL(NullableDynamicList dl) {
    ReverseDL(dl);
}

void SortNDL(NullableDynamicList dl, int (compFunc)(const void *, const void *)) {
    SortDL(dl, compFunc);
}

uint32_t LengthNDL(const NullableDynamicList dl) {
    LengthDL(dl);
}