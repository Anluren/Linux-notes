

```c++
// shrink a integer sequence
template<typename T, T... Ints>
struct pop_back;

template<typename T, T First, T... Ints>
struct pop_back<T, First, Ints...> {
    using type = typename std::conditional<sizeof...(Ints) == 0,
                                           std::integer_sequence<T>,
                                           typename pop_back<T, Ints...>::type>::type;
};

template<typename T, T Last>
struct pop_back<T, Last> {
    using type = std::integer_sequence<T>;
};

template<typename T, T... Ints>
using pop_back_t = typename pop_back<T, Ints...>::type;
```

```c++
// barrel shift a index sequence
template <std::size_t Shift, std::size_t... Is>
constexpr auto barrel_shift(std::index_sequence<Is...>) {
   constexpr std::size_t size = sizeof...(Is);
   return std::index_sequence<(Is + size + Shift) % size...>{};
}

// testing code
auto result = barrel_shift<1>(std::index_sequence<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>{});
static_assert(std::is_same_v<decltype(result), std::index_sequence<1, 2, 3, 4, 5, 6, 7, 8, 9, 0>>); 
```

```c++
#include <type_traits>

// Helper struct to check for the existence of a member function
template <typename T, typename = void>
struct has_member_func : std::false_type {};

template <typename T>
struct has_member_func<T, std::void_t<decltype(&T::member_func)>> : std::true_type {};

// Test class with the member function
class MyClass {
public:
    void member_func() {}
};

// Test class without the member function
class MyOtherClass {};

int main() {
    static_assert(has_member_func<MyClass>::value, "MyClass should have member_func");
    static_assert(!has_member_func<MyOtherClass>::value, "MyOtherClass should not have member_func");
    return 0;
}
```

In C++17, you can create a compile-time key/type map using template metaprogramming techniques. One way to achieve this is by using a combination of variadic templates, type traits, and constexpr functions. Below is an example of how to implement a compile-time key/type map.

### Example: Compile-Time Key/Type Map

#### Step 1: Define the Key/Type Pair

First, define a struct to represent a key/type pair:

```cpp
template <auto Key, typename T>
struct KeyTypePair {
    static constexpr auto key = Key;
    using type = T;
};
```

#### Step 2: Define the Key/Type Map

Next, define a struct to represent the key/type map. This struct will use variadic templates to store multiple key/type pairs:

```cpp
template <typename... Pairs>
struct KeyTypeMap;
```

#### Step 3: Implement a Helper to Find a Type by Key

Implement a helper struct to find a type by key at compile time:

```cpp
template <auto Key, typename Map>
struct FindTypeByKey;

template <auto Key, typename FirstPair, typename... RestPairs>
struct FindTypeByKey<Key, KeyTypeMap<FirstPair, RestPairs...>> {
    using type = std::conditional_t<
        (Key == FirstPair::key),
        typename FirstPair::type,
        typename FindTypeByKey<Key, KeyTypeMap<RestPairs...>>::type
    >;
};

template <auto Key>
struct FindTypeByKey<Key, KeyTypeMap<>> {
    using type = void; // Default type if key is not found
};
```

#### Step 4: Define a Helper Function to Get the Type

Define a helper function to get the type associated with a key:

```cpp
template <auto Key, typename Map>
using GetTypeByKey = typename FindTypeByKey<Key, Map>::type;
```

### Example Usage

Here is an example of how to use the compile-time key/type map:

```cpp
#include <iostream>
#include <type_traits>

// Define the KeyTypePair and KeyTypeMap as described above
template <auto Key, typename T>
struct KeyTypePair {
    static constexpr auto key = Key;
    using type = T;
};

template <typename... Pairs>
struct KeyTypeMap;

template <auto Key, typename Map>
struct FindTypeByKey;

template <auto Key, typename FirstPair, typename... RestPairs>
struct FindTypeByKey<Key, KeyTypeMap<FirstPair, RestPairs...>> {
    using type = std::conditional_t<
        (Key == FirstPair::key),
        typename FirstPair::type,
        typename FindTypeByKey<Key, KeyTypeMap<RestPairs...>>::type
    >;
};

template <auto Key>
struct FindTypeByKey<Key, KeyTypeMap<>> {
    using type = void; // Default type if key is not found
};

template <auto Key, typename Map>
using GetTypeByKey = typename FindTypeByKey<Key, Map>::type;

// Define some types and keys
struct TypeA {};
struct TypeB {};
struct TypeC {};

constexpr int KeyA = 1;
constexpr int KeyB = 2;
constexpr int KeyC = 3;

int main() {
    // Define the key/type map
    using MyMap = KeyTypeMap<
        KeyTypePair<KeyA, TypeA>,
        KeyTypePair<KeyB, TypeB>,
        KeyTypePair<KeyC, TypeC>
    >;

    // Get types by key
    using TypeForKeyA = GetTypeByKey<KeyA, MyMap>;
    using TypeForKeyB = GetTypeByKey<KeyB, MyMap>;
    using TypeForKeyC = GetTypeByKey<KeyC, MyMap>;
    using TypeForKeyD = GetTypeByKey<4, MyMap>; // Key not in map

    // Static assertions to verify the types
    static_assert(std::is_same_v<TypeForKeyA, TypeA>, "TypeForKeyA should be TypeA");
    static_assert(std::is_same_v<TypeForKeyB, TypeB>, "TypeForKeyB should be TypeB");
    static_assert(std::is_same_v<TypeForKeyC, TypeC>, "TypeForKeyC should be TypeC");
    static_assert(std::is_same_v<TypeForKeyD, void>, "TypeForKeyD should be void");

    std::cout << "All static assertions passed." << std::endl;

    return 0;
}
```

### Explanation

- **KeyTypePair**: Represents a key/type pair.
- **KeyTypeMap**: Represents a compile-time map of key/type pairs.
- **FindTypeByKey**: A helper struct to find a type by key at compile time.
- **GetTypeByKey**: A helper alias to get the type associated with a key.
- **Example Usage**: Demonstrates how to define a key/type map and retrieve types by key using static assertions to verify the types.

### Summary

This example demonstrates how to create a compile-time key/type map in C++17 using template metaprogramming techniques. The key/type map allows you to associate keys with types and retrieve the types at compile time. The provided example includes the necessary components and demonstrates how to use the key/type map with static assertions to verify the types.