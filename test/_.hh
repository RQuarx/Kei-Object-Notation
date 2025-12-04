#ifndef __HH
#define __HH
#include <print>


namespace
{
    void
    _() /* NOLINT */
    {
        std::print("");
    }
}


#define TEST(name, ...)                 \
    void                                \
    name()                              \
    {                                   \
        std::print("test {}: ", #name); \
        __VA_ARGS__                     \
        std::println("success");        \
    }

#define TEST_ASSERT(expr)                                   \
    if (!(expr))                                            \
    {                                                       \
        std::println("failed ({}:{})", __FILE__, __LINE__); \
        std::exit(1);                                       \
    }

#define TEST_THROWS(expr, except)                            \
    try                                                      \
    {                                                        \
        expr;                                                \
        std::println("failed: ({}:{})", __FILE__, __LINE__); \
    }                                                        \
    catch (const except &e)                                  \
    {}

#endif /* __HH */
