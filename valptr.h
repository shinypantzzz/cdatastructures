typedef void* ValPtr; // Represents pointer to value of unknown type

#define Val(type, ptr) *(type *)(ptr) // Gets value of type *type* from pointer
#define Ptr(type, value) (ValPtr)&(type){value} // Gets pointer to value of type *type*