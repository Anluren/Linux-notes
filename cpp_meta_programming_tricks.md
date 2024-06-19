

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