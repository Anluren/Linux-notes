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