#include <iostream>

// Define the KeyValuePair and KeyValueMap as described above
template <auto Key, auto Value>
struct KeyValuePair {
    static constexpr auto key = Key;
    static constexpr auto value = Value;
};

template <typename... Pairs>
struct KeyValueMap;

template <auto Key, typename Map>
struct FindValueByKey;

template <auto Key, typename FirstPair, typename... RestPairs>
struct FindValueByKey<Key, KeyValueMap<FirstPair, RestPairs...>> {
    static constexpr auto value = (Key == FirstPair::key) ? FirstPair::value : FindValueByKey<Key, KeyValueMap<RestPairs...>>::value;
};

template <auto Key>
struct FindValueByKey<Key, KeyValueMap<>> {
    static constexpr auto value = static_cast<unsigned int>(-1); // Default value if key is not found
};

template <auto Key, typename Map>
constexpr auto GetValueByKey = FindValueByKey<Key, Map>::value;

// Define the non-recursive iteration mechanism using fold expressions
template <typename Map, template <auto, auto> class Func>
struct IterateMap;

template <template <auto, auto> class Func, typename... Pairs>
struct IterateMap<KeyValueMap<Pairs...>, Func> {
    static void apply() {
        (Func<Pairs::key, Pairs::value>::apply(), ...);
    }
};

// Define a functor to print each key/value pair
template <auto Key, auto Value>
struct PrintKeyValue {
    static void apply() {
        std::cout << "Key: " << Key << ", Value: " << Value << std::endl;
    }
};

// Define some keys and values
constexpr int KeyA = 1;
constexpr int KeyB = 2;
constexpr int KeyC = 3;
constexpr int KeyD = 4;
constexpr int KeyE = 5;

constexpr unsigned int ValueA = 100;
constexpr unsigned int ValueB = 200;
constexpr unsigned int ValueC = 300;
constexpr unsigned int ValueD = 400;
constexpr unsigned int ValueE = 500;

int main() {
    // Define the key/value map
    using MyMap = KeyValueMap<
        KeyValuePair<KeyA, ValueA>,
        KeyValuePair<KeyB, ValueB>,
        KeyValuePair<KeyC, ValueC>,
        KeyValuePair<KeyD, ValueD>,
        KeyValuePair<KeyE, ValueE>
    >;

    // Get values by key
    constexpr auto ValueForKeyA = GetValueByKey<KeyA, MyMap>;
    constexpr auto ValueForKeyB = GetValueByKey<KeyB, MyMap>;
    constexpr auto ValueForKeyC = GetValueByKey<KeyC, MyMap>;
    constexpr auto ValueForKeyD = GetValueByKey<KeyD, MyMap>;
    constexpr auto ValueForKeyE = GetValueByKey<KeyE, MyMap>;
    constexpr auto ValueForKeyF = GetValueByKey<6, MyMap>; // Key not in map

    // Static assertions to verify the values
    static_assert(ValueForKeyA == ValueA, "ValueForKeyA should be ValueA");
    static_assert(ValueForKeyB == ValueB, "ValueForKeyB should be ValueB");
    static_assert(ValueForKeyC == ValueC, "ValueForKeyC should be ValueC");
    static_assert(ValueForKeyD == ValueD, "ValueForKeyD should be ValueD");
    static_assert(ValueForKeyE == ValueE, "ValueForKeyE should be ValueE");
    static_assert(ValueForKeyF == static_cast<unsigned int>(-1), "ValueForKeyF should be -1");

    // Iterate over the map and print each key/value pair
    IterateMap<MyMap, PrintKeyValue>::apply();

    return 0;
}