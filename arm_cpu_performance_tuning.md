```c++
unsigned int rotate_right(unsigned int value, unsigned int count) {
    unsigned int result;
    #if defined(__ARM_ARCH)
    __asm__("ror %0, %1, %2" : "=r" (result) : "r" (value), "r" (count));
    #else
    // Alternative implementation for non-ARM architectures
    result = (value >> count) | (value << (-count & (sizeof(value)*8 - 1)));
    #endif
    return result;
}
```

if the value is a compile time constant

```c++
template<unsigned int value>
unsigned int rotate_right(unsigned int count) {
    unsigned int result;
    #if defined(__ARM_ARCH)
    __asm__("ror %0, %1, %2" : "=r" (result) : "r" (value), "r" (count));
    #else
    // Alternative implementation for non-ARM architectures
    result = (value >> count) | (value << (-count & (sizeof(value)*8 - 1)));
    #endif
    return result;
}
```

a macro which is compiled to ror

```c++
#define ROR(x,y) ((unsigned)(x) >> (y) | (unsigned)(x) << 32 - (y))
```
it turns out, a constexpr should also work

```c++
constexpr unsigned int rotate_left(unsigned int value, int shift) {
    return (value << shift) | (value >> ((sizeof(value)*8) - shift));
}

constexpr unsigned int rotate_right(unsigned int value, int shift) {
    return (value >> shift) | (value << ((sizeof(value)*8) - shift));
}
```
