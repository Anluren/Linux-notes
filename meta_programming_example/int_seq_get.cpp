#include <iostream>
#include <utility>

// Helper struct to get the value at a given index
template <std::size_t Index, typename Seq>
struct GetValueAtIndex;

template <std::size_t Index, std::size_t First, std::size_t... Rest>
struct GetValueAtIndex<Index, std::integer_sequence<std::size_t, First, Rest...>> {
    static constexpr std::size_t value = GetValueAtIndex<Index - 1, std::integer_sequence<std::size_t, Rest...>>::value;
};

template <std::size_t First, std::size_t... Rest>
struct GetValueAtIndex<0, std::integer_sequence<std::size_t, First, Rest...>> {
    static constexpr std::size_t value = First;
};

// Helper alias to simplify usage
template <std::size_t Index, typename Seq>
constexpr std::size_t get_value_at_index_v = GetValueAtIndex<Index, Seq>::value;

int main() {
    using MySequence = std::integer_sequence<std::size_t, 10, 20, 30, 40, 50>;

    constexpr std::size_t value_at_0 = get_value_at_index_v<0, MySequence>;
    constexpr std::size_t value_at_1 = get_value_at_index_v<1, MySequence>;
    constexpr std::size_t value_at_2 = get_value_at_index_v<2, MySequence>;
    constexpr std::size_t value_at_3 = get_value_at_index_v<3, MySequence>;
    constexpr std::size_t value_at_4 = get_value_at_index_v<4, MySequence>;

    std::cout << "Value at index 0: " << value_at_0 << std::endl;
    std::cout << "Value at index 1: " << value_at_1 << std::endl;
    std::cout << "Value at index 2: " << value_at_2 << std::endl;
    std::cout << "Value at index 3: " << value_at_3 << std::endl;
    std::cout << "Value at index 4: " << value_at_4 << std::endl;

    return 0;
}