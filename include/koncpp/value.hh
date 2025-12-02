#ifndef KONCPP_VALUE__HH
#define KONCPP_VALUE__HH
#include <cstdint>

#include <SDL3/SDL.h>


namespace koncpp
{
    enum class ValueType : std::uint8_t
    {
        Null,
        Integer,
        Float,
        Boolean,
        String,
        Array,
        Object,
    };


    template <typename T_Allocator>
    class Value
    {
    public:
        Value(ValueType type);


    private:
    };
}

#endif /* KONCPP_VALUE__HH */
