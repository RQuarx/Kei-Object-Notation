/**
 * @file koncpp/types/integer.hh
 * @copyright Copyright (C) 2025-2026 Kei <RQuarx@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KONCPP_TYPES__INTEGER__HH
#define KONCPP_TYPES__INTEGER__HH
#include "koncpp/types/base.hh"


namespace koncpp::types
{
    using Signed   = std::int64_t;
    using Unsigned = std::uint64_t;


    template <typename T_Int>
    concept IntType
        = std::same_as<T_Int, Signed> || std::same_as<T_Int, Unsigned>;


    struct IntegerError : public Exception
    {
        using Exception::Exception;
    };


    /**
     * @brief A representation of an integer value inside Kei Object Notation.
     *
     * The @c Integer class is a @c Nullable data type that can store either a
     * signed or unsigned integer. The signed variant uses the
     * @c koncpp::types::Signed type, while the unsigned variant uses
     * @c koncpp::types::Unsigned .
     *
     * This class supports standard arithmetic, bitwise, comparison operations,
     * and implicit boolean casting.
     *
     * @tparam T_Int The underlying integer type.
     *               Must be either @c Signed , or @c Unsigned.
     *               Defaults to @c Signed .
     *
     * @warning Operating on a null @c Integer
     *          will trigger undefined behaviours.
     * @warning There is not overflow check.
     */
    template <IntType T_Int = Signed>
    class Integer : public BaseType
    {
    public:
        Integer() noexcept : m_value(0) {}

        template <typename T_Other>
        Integer(T_Other value) noexcept
            requires(std::is_convertible_v<T_Other, T_Int>)
        {
            mf_assign_safely(value);
        }

        Integer(const Integer &other) noexcept : m_value(other.m_value) {}
        Integer(Integer &&other) noexcept
        {
            if (&other != this)
            {
                m_value = other.m_value;
                other.m_value.reset();
            }
        }


        template <typename T_Other>
        auto
        operator=(T_Other value) noexcept -> Integer &
            requires(std::is_convertible_v<T_Other, T_Int>)
        {
            return mf_assign_safely(value), *this;
        }


        auto
        operator=(const Integer &other) noexcept -> Integer &
        {
            return (m_value = other.m_value), *this;
        }


        auto
        operator=(Integer &&other) noexcept -> Integer<T_Int>
        {
            if (&other != this)
            {
                m_value = other.m_value;
                other.m_value.reset();
            }

            return *this;
        }


        [[nodiscard]] auto
        type() const noexcept -> ValueType override
        {
            return ValueType::Integer;
        }


        [[nodiscard]]
        constexpr auto
        is_unsigned() const noexcept -> bool
        {
            return std::is_unsigned_v<T_Int>;
        }


        [[nodiscard]]
        constexpr auto
        is_signed() const noexcept -> bool
        {
            return std::is_signed_v<T_Int>;
        }


        [[nodiscard]]
        auto
        get() const noexcept -> std::optional<T_Int>
        {
            return m_value;
        }


        void
        set(T_Int value) noexcept
        {
            m_value = value;
        }


        auto
        operator+() const noexcept -> Integer
        {
            return *this;
        }

        auto
        operator-() const noexcept -> Integer
        {
            return -m_value.value();
        }

        auto
        operator~() const noexcept -> Integer
        {
            return ~m_value.value();
        }

        auto
        operator!() const noexcept -> bool
        {
            return *m_value == 0;
        }

        auto
        operator++() -> Integer &
        {
            ++(*m_value);
            return *this;
        }

        auto
        operator++(int) -> Integer
        {
            auto tmp { *this };
            ++(*this);
            return tmp;
        }

        auto
        operator--() -> Integer &
        {
            --(*m_value);
            return *this;
        }

        auto
        operator--(int) -> Integer
        {
            auto tmp { *this };
            --(*this);
            return tmp;
        }


        auto
        operator+(const Integer &rhs) const noexcept -> Integer
        {
            return *m_value + *rhs.m_value;
        }

        auto
        operator-(const Integer &rhs) const noexcept -> Integer
        {
            return *m_value - *rhs.m_value;
        }

        auto
        operator*(const Integer &rhs) const noexcept -> Integer
        {
            return *m_value * *rhs.m_value;
        }

        auto
        operator/(const Integer &rhs) const -> Integer
        {
            if (!*rhs.m_value) throw IntegerError { "division by zero" };
            return *m_value / *rhs.m_value;
        }

        auto
        operator%(const Integer &rhs) const -> Integer
        {
            if (!*rhs.m_value) throw IntegerError { "modulo by zero" };
            return *m_value % *rhs.m_value;
        }

        auto
        operator+=(const Integer &rhs) noexcept -> Integer &
        {
            *m_value += *rhs.m_value;
            return *this;
        }

        auto
        operator-=(const Integer &rhs) noexcept -> Integer &
        {
            *m_value -= *rhs.m_value;
            return *this;
        }

        auto
        operator*=(const Integer &rhs) noexcept -> Integer &
        {
            *m_value *= *rhs.m_value;
            return *this;
        }

        auto
        operator/=(const Integer &rhs) -> Integer &
        {
            if (!*rhs.m_value) throw IntegerError { "division by zero" };
            *m_value /= *rhs.m_value;
            return *this;
        }

        auto
        operator%=(const Integer &rhs) -> Integer &
        {
            if (!*rhs.m_value) throw IntegerError { "modulo by zero" };
            *m_value %= *rhs.m_value;
            return *this;
        }


        auto
        operator&(const Integer &rhs) const noexcept -> Integer
        {
            return *m_value & *rhs.m_value;
        }

        auto
        operator|(const Integer &rhs) const noexcept -> Integer
        {
            return *m_value | *rhs.m_value;
        }

        auto
        operator^(const Integer &rhs) const noexcept -> Integer
        {
            return *m_value ^ *rhs.m_value;
        }

        auto
        operator&=(const Integer &rhs) noexcept -> Integer &
        {
            *m_value &= *rhs.m_value;
            return *this;
        }

        auto
        operator|=(const Integer &rhs) noexcept -> Integer &
        {
            *m_value |= *rhs.m_value;
            return *this;
        }

        auto
        operator^=(const Integer &rhs) noexcept -> Integer &
        {
            *m_value ^= *rhs.m_value;
            return *this;
        }

        auto
        operator<<(int shift) const noexcept -> Integer
        {
            return *m_value << shift;
        }

        auto
        operator>>(int shift) const noexcept -> Integer
        {
            return *m_value >> shift;
        }

        auto
        operator<<=(int shift) noexcept -> Integer &
        {
            *m_value <<= shift;
            return *this;
        }

        auto
        operator>>=(int shift) noexcept -> Integer &
        {
            *m_value >>= shift;
            return *this;
        }


        auto
        operator==(const Integer &rhs) const noexcept -> bool
        {
            return *m_value == *rhs.m_value;
        }

        auto
        operator!=(const Integer &rhs) const noexcept -> bool
        {
            return *m_value != *rhs.m_value;
        }

        auto
        operator<(const Integer &rhs) const noexcept -> bool
        {
            return *m_value < *rhs.m_value;
        }

        auto
        operator<=(const Integer &rhs) const noexcept -> bool
        {
            return *m_value <= *rhs.m_value;
        }

        auto
        operator>(const Integer &rhs) const noexcept -> bool
        {
            return *m_value > *rhs.m_value;
        }

        auto
        operator>=(const Integer &rhs) const noexcept -> bool
        {
            return *m_value >= *rhs.m_value;
        }


        explicit(true)
        operator bool() const noexcept
        {
            return *m_value != 0;
        }

        operator T_Int() const noexcept { return *m_value; }

        operator int() const noexcept { return *m_value; }


    private:
        std::optional<T_Int> m_value;


        template <typename T_Other>
        void
        mf_assign_safely(T_Other value) noexcept
        {
            using C = std::common_type_t<T_Other, T_Int>;

            if constexpr (std::is_unsigned_v<T_Int>)
                if (value < 0)
                {
                    m_value = Null;
                    return;
                }

            if (value > C(std::numeric_limits<T_Int>::max())
                || value < C(std::numeric_limits<T_Int>::min()))
            {
                m_value = Null;
            }
            else
                m_value = static_cast<T_Int>(value);
        }
    };
}


#ifndef KONCPP_NO_FORMATTER

#include <format>

template <koncpp::types::IntType T_Int>
struct std::formatter<koncpp::types::Integer<T_Int>> : std::formatter<T_Int>
{
    auto
    format(const koncpp::types::Integer<T_Int> &i,
           std::format_context                 &ctx) const
    {
        if (!i.get()) return std::format_to(ctx.out(), "null");
        return std::formatter<T_Int, char>::format(*i.get(), ctx);
    }
};

#endif
#endif /* KONCPP_TYPES__INTEGER__HH */
