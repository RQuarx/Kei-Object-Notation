#include <koncpp/types/string.hh>

#include "_.hh"


namespace test
{
    using namespace koncpp::types;

    TEST(constructor,
         String string { "Hello, World!" };
         String null_str {};
    )
}


auto
main() -> int
{
    test::constructor();

    return 0;
}