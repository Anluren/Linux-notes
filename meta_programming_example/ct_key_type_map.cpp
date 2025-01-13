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

template <auto Key, typename... Pairs>
struct FindTypeByKey<Key, KeyTypeMap<Pairs...>> {
private:
    template <typename Pair>
    static constexpr bool match() {
        return Key == Pair::key;
    }

    template <typename Pair>
    static constexpr auto get_type() -> typename Pair::type;

    template <typename...>
    struct TypeHelper;

    template <typename Pair, typename... Rest>
    struct TypeHelper<Pair, Rest...> {
        using type = std::conditional_t<
            match<Pair>(),
            typename Pair::type,
            typename TypeHelper<Rest...>::type
        >;
    };

    template <>
    struct TypeHelper<> {
        using type = void; // Default type if key is not found
    };

public:
    using type = typename TypeHelper<Pairs...>::type;
};

template <auto Key, typename Map>
using GetTypeByKey = typename FindTypeByKey<Key, Map>::type;

// Define the non-recursive iteration mechanism using fold expressions
template <typename Map, template <auto, typename> class Func>
struct IterateMap;

template <template <auto, typename> class Func, typename... Pairs>
struct IterateMap<KeyTypeMap<Pairs...>, Func> {
    static void apply() {
        (Func<Pairs::key, typename Pairs::type>::apply(), ...);
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
constexpr int KeyD = 4;
constexpr int KeyE = 5;

int main() {
    // Define the key/type map with many-to-one mappings
    using MyMap = KeyTypeMap<
        KeyTypePair<KeyA, TypeA>,
        KeyTypePair<KeyB, TypeB>,
        KeyTypePair<KeyC, TypeC>,
        KeyTypePair<KeyD, TypeB>, // KeyD maps to TypeB
        KeyTypePair<KeyE, TypeB>  // KeyE maps to TypeB
    >;

    // Get types by key
    using TypeForKeyA = GetTypeByKey<KeyA, MyMap>;
    using TypeForKeyB = GetTypeByKey<KeyB, MyMap>;
    using TypeForKeyC = GetTypeByKey<KeyC, MyMap>;
    using TypeForKeyD = GetTypeByKey<KeyD, MyMap>;
    using TypeForKeyE = GetTypeByKey<KeyE, MyMap>;
    using TypeForKeyF = GetTypeByKey<6, MyMap>; // Key not in map

    // Static assertions to verify the types
    static_assert(std::is_same_v<TypeForKeyA, TypeA>, "TypeForKeyA should be TypeA");
    static_assert(std::is_same_v<TypeForKeyB, TypeB>, "TypeForKeyB should be TypeB");
    static_assert(std::is_same_v<TypeForKeyC, TypeC>, "TypeForKeyC should be TypeC");
    static_assert(std::is_same_v<TypeForKeyD, TypeB>, "TypeForKeyD should be TypeB");
    static_assert(std::is_same_v<TypeForKeyE, TypeB>, "TypeForKeyE should be TypeB");
    static_assert(std::is_same_v<TypeForKeyF, void>, "TypeForKeyF should be void");

    // Iterate over the map and print each key/type pair
    IterateMap<MyMap, PrintKeyType>::apply();

    return 0;
}