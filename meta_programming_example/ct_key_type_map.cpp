#include <iostream>
#include <typeinfo>

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

// Define the iteration mechanism
template <typename Map, template <auto, typename> class Func>
struct IterateMap;

template <template <auto, typename> class Func>
struct IterateMap<KeyTypeMap<>, Func> {
    static void apply() {}
};

template <typename FirstPair, typename... RestPairs, template <auto, typename> class Func>
struct IterateMap<KeyTypeMap<FirstPair, RestPairs...>, Func> {
    static void apply() {
        Func<FirstPair::key, typename FirstPair::type>::apply();
        IterateMap<KeyTypeMap<RestPairs...>, Func>::apply();
    }
};

// Define a functor to print each key/type pair
template <auto Key, typename T>
struct PrintKeyType {
    static void apply() {
        std::cout << "Key: " << Key << ", Type: " << typeid(T).name() << std::endl;
    }
};

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

    // Iterate over the map and print each key/type pair
    IterateMap<MyMap, PrintKeyType>::apply();

    return 0;
}