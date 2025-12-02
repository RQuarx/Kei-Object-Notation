#ifndef KONCPP_TYPES__BASE__HH
#define KONCPP_TYPES__BASE__HH
#include <cstdint>
#include <optional>


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
        Object
    };


    namespace types
    {
        using Null = std::nullopt_t;


        class BaseType
        {
        public:
            virtual ~BaseType() = default;


            [[nodiscard]]
            virtual constexpr auto type() const noexcept -> ValueType
                = 0;
        };


        template <typename T_ToType>
        [[nodiscard]]
        constexpr auto
        cast(BaseType &base) -> T_ToType &
        {
            static_assert(std::is_base_of_v<BaseType, T_ToType>,
                          "T_ToType must derive from BaseType<T_Allocator>");

            if (auto *ptr { dynamic_cast<T_ToType *>(&base) }; ptr != nullptr)
                return *ptr;

            throw std::bad_cast {};
        }
    }
}


#endif /* KONCPP_TYPES__BASE__HH */
