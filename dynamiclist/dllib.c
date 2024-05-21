#include "dllib.h"

DynamicList CreateDL(const unsigned int element_size) {
    DynamicList dl = {.length=DL_INITIAL_LENGTH, .append_index = 0, .element_size = element_size};
    dl.array = (void *)calloc(dl.length, dl.element_size);
    return dl;
}

void FreeDL(DynamicList dl) {
    free(dl.array);
}

void AppendDL(DynamicList *dl, ValPtr value_ptr) {
    if (dl->append_index >= dl->length) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length*dl->element_size);
    }
    memcpy(dl->array + dl->append_index*dl->element_size, value_ptr, dl->element_size);
    dl->append_index++;
}

void ClearDL(DynamicList *dl) {
    dl->append_index = 0;
}

DynamicList CopyDL(const DynamicList dl) {
    DynamicList dl_copy = {.length=dl.length, .append_index = dl.append_index, .element_size = dl.element_size};
    dl_copy.array = (void *)calloc(dl.length, dl.element_size);
    memcpy(dl_copy.array, dl.array, dl.element_size*dl.append_index);

    return dl_copy;
}

ValPtr GetDL(const DynamicList dl, const unsigned int index) {
    return dl.array + index*dl.element_size;
}

unsigned int CountDL(const DynamicList dl, ValPtr value_ptr) {
    int count = 0;
    for (int i = 0; i < dl.append_index; i++) {
        if (memcmp(value_ptr, GetDL(dl, i), dl.element_size) == 0) count++;
    }
    return count;
}

unsigned int ExtendDL(DynamicList *dest, const DynamicList src) {
    if (dest->element_size != src.element_size) {
        return 0;
    }
    if (dest->length < dest->append_index + src.append_index) {
        dest->length = 1;
        while (dest->length < dest->append_index + src.append_index) dest->length*=2;
        dest->array = realloc(dest->array, dest->length*dest->element_size);
    }
    memcpy(dest->array + dest->append_index*dest->element_size, src.array, src.append_index*src.element_size);
    dest->append_index += src.append_index;
    return 1;
}

int IndexDL(const DynamicList dl, ValPtr value_ptr) {
    for (unsigned int i = 0; i < dl.append_index; i++) {
        if (memcmp(GetDL(dl, i), value_ptr, dl.element_size) == 0) {
            return i;
        }
    }
    return -1;
}

void InsertDL(DynamicList *dl, ValPtr value_ptr, const unsigned int pos) {
    if (pos >= dl->append_index) {
        return AppendDL(dl, value_ptr);
    }
    if (dl->length <= dl->append_index) {
        dl->length *= 2;
        dl->array = realloc(dl->array, dl->length * dl->element_size);
    }

    memmove(dl->array + (pos+1)*dl->element_size, dl->array + pos*dl->element_size, (dl->append_index-pos)*dl->element_size);
    memcpy(GetDL(*dl, pos), value_ptr, dl->element_size);
    dl->append_index++;
}

ValPtr PopLastDL(DynamicList *dl) {
    if (dl->append_index <= 0) return NULL;

    return GetDL(*dl, --dl->append_index);
}

ValPtr PopDL(DynamicList *dl, const unsigned int index) {
    if (dl->append_index <= 0) return NULL;
    if (index >= dl->append_index - 1) return PopLastDL(dl);
    void *tmp = (void *)malloc(dl->element_size);
    memcpy(tmp, GetDL(*dl, index), dl->element_size);
    memmove(GetDL(*dl, index), GetDL(*dl, index + 1), (--dl->append_index-index)*dl->element_size);
    memcpy(GetDL(*dl, dl->append_index), tmp, dl->element_size);
    free(tmp);
    return GetDL(*dl, dl->append_index);
}

unsigned int RemoveDL(DynamicList *dl, ValPtr value_ptr) {
    unsigned int index = IndexDL(*dl, value_ptr);
    if (index == -1) return 0;
    PopDL(dl, index);
    return 1;
}

void ReverseDL(DynamicList dl) {
    unsigned int l = 0, r = dl.append_index - 1;
    void *tmp = (void *)malloc(dl.element_size);
    while(l < r) {
        memcpy(tmp, GetDL(dl, l), dl.element_size);
        memcpy(GetDL(dl, l), GetDL(dl, r), dl.element_size);
        memcpy(GetDL(dl, r), tmp, dl.element_size);
        l++; r--;
    }
    free(tmp);
}

void SortDL(DynamicList dl, int (comp_func)(const void *, const void *)) {
    qsort(dl.array, dl.append_index, dl.element_size, comp_func);
}

unsigned int LengthDL(const DynamicList dl) {
    return dl.append_index;
}