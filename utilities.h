
#if __cplusplus < 202002L
// C++17 (and earlier) code

// this was added in C++20 so not available in earlier standards
template<class T>
struct remove_cvref
{
    typedef std::remove_cv_t<std::remove_reference_t<T>> type;
};
#endif


/** Returns true if value is equal to any of arguments
  * @param value  the value to check
  * @param args   the list of arguments to compare with value
  * @return       true if value is equal to any item in args otherwise false
  */
template<typename T, typename... Args>
[[nodiscard]] bool is_one_of(T&& value, Args&&...args)
{
    static_assert(sizeof...(Args) > 0, "too few arguments. must have at least one argument to test against.");
    static_assert((std::is_same_v<typename remove_cvref<T&&>::type, typename remove_cvref<Args&&>::type> && ...), "mismatched argument types. all arguments must have same underlying type.");

    // expands to (((value == args[0]) || value == args[1]) || value == args[2])...)
    return (... || (value == args));
}
