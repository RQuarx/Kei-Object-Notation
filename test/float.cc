#include <koncpp/types/float.hh>

#include <cmath>
#include <format>

#include "_.hh"


namespace test
{
    using namespace koncpp::types;

    constexpr double EPS { 1e-12 };

    inline auto
    eq(double a, double b) -> bool
    {
        return std::fabs(a - b) < EPS;
    }


    TEST(constructor, {
        Float a { 1.5 };
        TEST_ASSERT(eq(a.get().value(), 1.5))

        Float b { -2.25 };
        TEST_ASSERT(eq(b.get().value(), -2.25))

        Float c { a };
        TEST_ASSERT(eq(c.get().value(), 1.5))

        Float d { 2.0 };
        Float e { std::move(d) };
        TEST_ASSERT(eq(e.get().value(), 2.0))
        TEST_ASSERT(!d.get())
    })


    TEST(assignment, {
        Float a { 0.0 };
        a = 3.14;
        TEST_ASSERT(eq(a.get().value(), 3.14))

        Float b { 2.71 };
        Float c {};
        c = b;
        TEST_ASSERT(eq(c.get().value(), 2.71))

        Float d { 9.81 };
        Float e {};
        e = std::move(d);
        TEST_ASSERT(eq(e.get().value(), 9.81))
        TEST_ASSERT(!d.get())
    })


    TEST(getset, {
        Float a { 1.0 };
        TEST_ASSERT(eq(a.get().value(), 1.0))

        a.set(42.0);
        TEST_ASSERT(eq(a.get().value(), 42.0))

        Float b { 100.0 };
        Float c { std::move(b) };
        TEST_ASSERT(!b.get())
    })


    TEST(unary, {
        Float a { 5.0 };
        TEST_ASSERT(eq((+a).get().value(), 5.0))
        TEST_ASSERT(eq((-a).get().value(), -5.0))

        Float b { 1.0 };
        ++b;
        TEST_ASSERT(eq(b.get().value(), 2.0))

        Float c { 3.0 };
        Float d = c++;
        TEST_ASSERT(eq(d.get().value(), 3.0))
        TEST_ASSERT(eq(c.get().value(), 4.0))

        Float e { 10.0 };
        --e;
        TEST_ASSERT(eq(e.get().value(), 9.0))

        Float f { 4.0 };
        Float g = f--;
        TEST_ASSERT(eq(g.get().value(), 4.0))
        TEST_ASSERT(eq(f.get().value(), 3.0))
    })


    TEST(arithmetic, {
        Float a { 10.0 };
        Float b { 2.0 };

        TEST_ASSERT(eq((a + b).get().value(), 12.0))
        TEST_ASSERT(eq((a - b).get().value(), 8.0))
        TEST_ASSERT(eq((a * b).get().value(), 20.0))
        TEST_ASSERT(eq((a / b).get().value(), 5.0))

        a += b;
        TEST_ASSERT(eq(a.get().value(), 12.0))

        a -= b;
        TEST_ASSERT(eq(a.get().value(), 10.0))

        a *= b;
        TEST_ASSERT(eq(a.get().value(), 20.0))

        a /= b;
        TEST_ASSERT(eq(a.get().value(), 10.0))

        Float z { 0.0 };
        TEST_THROWS(Float { 1.0 } / z, FloatError)
        TEST_THROWS(a /= z, FloatError)
    })


    TEST(comparison, {
        Float a { 2.0 };
        Float b { 2.0 };
        Float c { 3.0 };

        TEST_ASSERT(a == b)
        TEST_ASSERT(!(a != b))
        TEST_ASSERT(a < c)
        TEST_ASSERT(c > a)
        TEST_ASSERT(a <= b)
        TEST_ASSERT(a <= c)
        TEST_ASSERT(c >= b)
    })


    TEST(conversion, {
        Float a { std::numbers::pi_v<double> };

        auto f { static_cast<float>(a) };
        auto d { static_cast<double>(a) };

        TEST_ASSERT(eq(f, std::numbers::pi_v<float>))
        TEST_ASSERT(eq(d, std::numbers::pi_v<double>))
    })


    TEST(formatter, {
        Float a { 1.5 };
        TEST_ASSERT(std::format("{}", a) == "1.5")

        Float inf { std::numeric_limits<double>::infinity() };
        TEST_ASSERT(std::format("{}", inf) == "inf")

        Float b {};
        TEST_ASSERT(std::format("{}", b) == "null")
    })


    TEST(special_cases, {
        Float a { std::numeric_limits<double>::infinity() };
        TEST_ASSERT(std::isinf(*a.get()))

        Float b { -std::numeric_limits<double>::infinity() };
        TEST_ASSERT(std::isinf(*b.get()))

        Float c { std::numeric_limits<double>::quiet_NaN() };
        TEST_ASSERT(std::isnan(*c.get()))
    })
}


auto
main() -> int
{
    test::constructor();
    test::assignment();
    test::getset();
    test::unary();
    test::arithmetic();
    test::comparison();
    test::conversion();
    test::formatter();
    test::special_cases();
    return 0;
}
