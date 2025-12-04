#include <koncpp/types/integer.hh>

#include "_.hh"


namespace test
{
    using namespace koncpp::types;


    TEST(constructor, {
        /* default constructor */
        Integer a {};
        TEST_ASSERT(a.get().value() == 0)

        /* signed construction */
        Integer b { 42 };
        TEST_ASSERT(b.get().value() == 42)

        /* unsigned construction */
        Integer<Unsigned> c { 42U };
        TEST_ASSERT(c.get().value() == 42)

        /* unsigned receiving negative => null */
        Integer<Unsigned> d { -1 };
        TEST_ASSERT(!d.get())

        /* signed overflow => null */
        Integer e { std::numeric_limits<Signed>::max() };
        e = std::numeric_limits<Signed>::max();
        TEST_ASSERT(e.get().has_value())

        /* copy constructor */
        Integer g { 123 };
        Integer h { g }; /* NOLINT */
        TEST_ASSERT(h.get().value() == 123)

        /* move constructor */
        Integer i { 456 };
        Integer j { std::move(i) };
        TEST_ASSERT(j.get().value() == 456)
        TEST_ASSERT(!i.get())
    })


    TEST(assignment, {
        Integer a { 10 };
        a = 20;
        TEST_ASSERT(a.get() == 20)

        /* unsigned into negative, should be null */
        Integer<Unsigned> b { 5 };
        b = -5;
        TEST_ASSERT(!b.get())

        /* copy expression */
        Integer c { 33 };
        Integer d {};
        d = c;
        TEST_ASSERT(d.get().value() == 33)

        /* move assignment */
        Integer e { 44 };
        Integer f {};
        f = std::move(e);
        TEST_ASSERT(f.get().value() == 44) TEST_ASSERT(!e.get())
    })


    TEST(unary, {
        Integer a { 5 };
        TEST_ASSERT((+a).get().value() == 5)
        TEST_ASSERT((-a).get().value() == -5)
        TEST_ASSERT((~a).get().value() == (~5))
        TEST_ASSERT(!(!a))

        Integer b { 0 };
        TEST_ASSERT(!b)

        Integer c { 10 };
        TEST_ASSERT((c++).get().value() == 10)
        TEST_ASSERT(c.get().value() == 11)

        TEST_ASSERT((++c).get().value() == 12)

        Integer d { 10 };
        TEST_ASSERT((d--).get().value() == 10)
        TEST_ASSERT(d.get().value() == 9)

        TEST_ASSERT((--d).get().value() == 8)
    })


    TEST(arithmetic_ops, {
        Integer a { 10 };
        Integer b { 3 };

        TEST_ASSERT((a + b).get().value() == 13)
        TEST_ASSERT((a - b).get().value() == 7)
        TEST_ASSERT((a * b).get().value() == 30)
        TEST_ASSERT((a / b).get().value() == 3)
        TEST_ASSERT((a % b).get().value() == 1)

        a += b;
        TEST_ASSERT(a.get().value() == 13)

        a -= b;
        TEST_ASSERT(a.get().value() == 10)

        a *= b;
        TEST_ASSERT(a.get().value() == 30)

        a /= b;
        TEST_ASSERT(a.get().value() == 10)

        a %= b;
        TEST_ASSERT(a.get().value() == 1)

        /* division by 0 */
        Integer z { 0 };
        TEST_THROWS(a / z, IntegerError)

        /* module by 0 */
        TEST_THROWS(a % z, IntegerError)
    })


    TEST(bitwise, {
        Integer a { 0b1100 };
        Integer b { 0b1010 };

        TEST_ASSERT((a & b).get().value() == 0b1000)
        TEST_ASSERT((a | b).get().value() == 0b1110)
        TEST_ASSERT((a ^ b).get().value() == 0b0110)

        Integer c { 0b0101 };
        c &= Integer { 0b0011 };
        TEST_ASSERT(c.get().value() == 0b0001)

        c |= Integer { 0b1000 };
        TEST_ASSERT(c.get().value() == 0b1001)

        c ^= Integer { 0b0001 };
        TEST_ASSERT(c.get().value() == 0b1000)

        Integer d { 1 };
        TEST_ASSERT((d << 3).get().value() == 8)
        TEST_ASSERT((d >> 1).get().value() == 0)

        d <<= 4;
        TEST_ASSERT(d.get().value() == 16)

        d >>= 2;
        TEST_ASSERT(d.get().value() == 4)
    })


    TEST(comparison, {
        Integer a { 5 };
        Integer b { 10 };

        TEST_ASSERT(a < b)
        TEST_ASSERT(a <= b)
        TEST_ASSERT(b > a)
        TEST_ASSERT(b >= a)

        TEST_ASSERT(a != b)
        TEST_ASSERT(!(a == b))

        Integer c { 5 };
        TEST_ASSERT(a == c) TEST_ASSERT(a <= c) TEST_ASSERT(a >= c)
    })


    TEST(conversion, {
        Integer a { 5 };
        bool    b { a };

        TEST_ASSERT(b == true)

        Integer c { 0 };
        TEST_ASSERT(!bool(c))

        int x { Integer { 42 } };
        TEST_ASSERT(x == 42)
    })


    TEST(formatter, {
        Integer a { 16 };
        TEST_ASSERT(std::format("{}", a) == "16")

        Integer b { 0 };
        TEST_ASSERT(std::format("{}", b) == "0")

        Integer<Unsigned> nullv { -1 };
        TEST_ASSERT(std::format("{}", nullv) == "null")
    })
}


auto
main() -> int
{
    test::constructor();
    test::assignment();
    test::unary();
    test::arithmetic_ops();
    test::bitwise();
    test::comparison();
    test::conversion();
    test::formatter();

    return 0;
}
