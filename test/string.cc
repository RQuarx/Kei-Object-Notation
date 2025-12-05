#include <koncpp/types/string.hh>

#include <ranges>

#include "_.hh"


namespace test
{
    using namespace koncpp::types;


    TEST(constructor, {
        String a; /* default ctor (should be Null) */
        String b { "string" };

        TEST_THROWS(String e { nullptr }, StringError);

        TEST_ASSERT(a.get() == Null)
        TEST_ASSERT(*b.get() == "string")

        String c { b };            /* copy ctor */
        String d { std::move(b) }; /* move ctor */

        TEST_ASSERT(b.get() == Null)
        TEST_ASSERT(*c.get() == "string")
        TEST_ASSERT(*d.get() == "string")
    })

    TEST(assignment, {
        String a { "string" };

        String b = a;            /* copy assignment */
        String c = std::move(a); /* move assignment */
        String d = "string";

        TEST_ASSERT(a.get() == Null);
        TEST_ASSERT(*b.get() == "string");
        TEST_ASSERT(*c.get() == "string");
        TEST_ASSERT(*d.get() == "string");
    })

    TEST(iterator, {
        const String base { "string" };

        for (const auto &[i, c] : std::views::enumerate(base))
            TEST_ASSERT(base[i] == c);

        String reverse;

        for (const auto c : std::views::reverse(base)) TEST_ASSERT(c);
    })
}


auto
main() -> int
{
    test::constructor();
    test::assignment();
    test::iterator();

    return 0;
}
