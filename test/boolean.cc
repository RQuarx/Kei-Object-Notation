#include <koncpp/types/boolean.hh>

#include <format>

#include "_.hh"


namespace test
{
    using namespace koncpp::types;


    TEST(constructor, {
        Boolean a {};
        TEST_ASSERT(!a.get())
        TEST_ASSERT(a.get() == Null)

        Boolean b { true };
        Boolean c { false };
        TEST_ASSERT(b.get().value() == true)
        TEST_ASSERT(c.get().value() == false)

        Boolean d { 1 };
        Boolean e { 0 };
        TEST_ASSERT(d.get().value() == true)
        TEST_ASSERT(e.get().value() == false)

        Boolean f { b }; /* NOLINT */
        TEST_ASSERT(f.get().value() == true)

        Boolean g { true };
        Boolean h { std::move(g) };
        TEST_ASSERT(h.get().value() == true)
        TEST_ASSERT(!g.get())
    })


    TEST(assignment, {
        Boolean a {};
        a = true;
        TEST_ASSERT(a.get().value() == true);
        a = false;
        TEST_ASSERT(a.get().value() == false)

        Boolean b { true };
        Boolean c {};
        c = b;
        TEST_ASSERT(c.get() == b.get())

        Boolean d { false };
        Boolean e {};
        e = std::move(d);
        TEST_ASSERT(e.get().value() == false)
        TEST_ASSERT(!d.get())
    })


    TEST(conversion, {
        Boolean a { true };
        bool    x = a; /* implicit conversion */
        TEST_ASSERT(x == true)

        Boolean b { false };
        bool    y = b;
        TEST_ASSERT(y == false)

        Boolean c {};
        TEST_ASSERT(!static_cast<bool>(c))
    })


    TEST(logic, {
        Boolean t { true };
        Boolean f { false };
        Boolean n {}; /* null */

        TEST_ASSERT(!t == false)
        TEST_ASSERT(!f == true)
        TEST_ASSERT(!n == true) /* null treated as false → !false == true */

        TEST_ASSERT((t && t).get().value() == true)
        TEST_ASSERT((t && f).get().value() == false)
        TEST_ASSERT((f && t).get().value() == false)
        TEST_ASSERT(*(n && t).get() == false) /* null becomes false */
        TEST_ASSERT(*(t && n).get() == false)
        TEST_ASSERT(*(n && n).get() == false)

        TEST_ASSERT((t || f).get().value() == true)
        TEST_ASSERT((f || t).get().value() == true)
        TEST_ASSERT((f || f).get().value() == false)
        TEST_ASSERT(*(n || f).get() == false) /* null becomes false */
        TEST_ASSERT(*(f || n).get() == false)
        TEST_ASSERT(*(n || n).get() == false)

        Boolean a { true };
        Boolean b { false };

        a &= b; /* true && false = false */
        TEST_ASSERT(a.get().value() == false)

        a  = true;
        a |= b; /* true || false = true */
        TEST_ASSERT(a.get().value() == true)
    })


    TEST(comparison, {
        Boolean t { true };
        Boolean f { false };
        Boolean n {};

        TEST_ASSERT(t == Boolean { true })
        TEST_ASSERT(f == Boolean { false })
        TEST_ASSERT(!(t == f))
        TEST_ASSERT(t != f)

        TEST_ASSERT(!(t == n))
        TEST_ASSERT(n == Boolean {})
        TEST_ASSERT(n != t) TEST_ASSERT(n != f)
    })


    TEST(formatter, {
        Boolean a { true };
        TEST_ASSERT(std::format("{}", a) == "true")

        Boolean b { false };
        TEST_ASSERT(std::format("{}", b) == "false")

        Boolean c {};
        TEST_ASSERT(std::format("{}", c) == "null")
    })
}


auto
main() -> int
{
    test::constructor();
    test::assignment();
    test::conversion();
    test::logic();
    test::comparison();
    test::formatter();
    return 0;
}
