#ifndef KONCPP_TYPES__INTEGER__HH
#define KONCPP_TYPES__INTEGER__HH

#include <concepts>
#include <cstdint>
#include <optional>
#include <stdexcept>

#include "koncpp/types/base.hh"

namespace koncpp::types
{
    template <typename T_Int>
    concept IntType = std::same_as<T_Int, std::int64_t>
                   || std::same_as<T_Int, std::uint64_t>;


    class IntegerError : public std::runtime_error
    {
    public:
        using std::runtime_error::what;

        IntegerError(const char *string) : std::runtime_error { string } {}
    };


    /**
     * @brief A representation of an integer value.
     */
    template <IntType T_Int = std::int64_t>
    class Integer : public BaseType
    {
    public:
        template <typename T_Other>
        Integer(T_Other value) noexcept
            requires(std::is_convertible_v<T_Other, T_Int>)
            : m_value { static_cast<T_Int>(value) }
        {
        }


        template <typename T_Other>
        auto
        operator=(T_Other value) noexcept -> Integer &
            requires(std::is_convertible_v<T_Other, T_Int>)
        {
            m_value = static_cast<T_Int>(value);
            return *this;
        }


        Integer(const Integer &other) noexcept : m_value(other.m_value) {}


        auto
        operator=(const Integer &other) noexcept -> Integer &
        {
            if (&other != this) m_value = other.m_value;
            return *this;
        }


        Integer(Integer &&other) noexcept
        {
            if (&other != this)
            {
                m_value = std::move(other.m_value);
                other.m_value.reset();
            }
        }


        auto
        operator=(Integer &&other) noexcept -> Integer<T_Int>
        {
            if (&other != this)
            {
                m_value = std::move(other.m_value);
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
        operator-() const -> Integer
        {
            throw_if_null("Tried to perform operations on a null integer.");
            return Integer { -m_value.value() };
        }


        auto
        operator~() const -> Integer
        {
            throw_if_null("Tried to perform operations on a null integer.");
            return Integer { ~m_value.value() };
        }


        auto
        operator++() -> Integer &
        {
            throw_if_null("Tried to perform operations on a null integer.");
            m_value = *m_value + 1;
            return *this;
        }


        auto
        operator++(int) -> Integer
        {
            Integer tmp = *this;
            ++(*this);
            return tmp;
        }


        auto
        operator--() noexcept -> Integer &
        {
            m_value = m_value - 1;
            return *this;
        }


        auto
        operator--(int) noexcept -> Integer
        {
            Integer tmp = *this;
            --(*this);
            return tmp;
        }


        auto
        operator+(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            return Integer { *m_value + *rhs };
        }


        auto
        operator-(const Integer &rhs) const noexcept -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            return Integer { *m_value - *rhs.m_value };
        }

        auto
        operator*(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            return Integer { *m_value * *rhs.m_value };
        }

        auto
        operator/(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            if (*rhs.m_value == 0)
                throw IntegerError { "Attempted division by zero" };

            return Integer { *m_value / *rhs.m_value };
        }


        auto
        operator%(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            if (*rhs.m_value == 0)
                throw IntegerError { "Attempted modulo by zero" };

            return Integer { *m_value % *rhs.m_value };
        }


        auto
        operator+=(const Integer &rhs) noexcept -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            m_value = *m_value + *rhs.m_value;
            return *this;
        }

        auto
        operator-=(const Integer &rhs) noexcept -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            m_value = *m_value - *rhs.m_value;
            return *this;
        }

        auto
        operator*=(const Integer &rhs) noexcept -> Integer &
        {
            m_value = *m_value * *rhs.m_value;
            return *this;
        }

        auto
        operator/=(const Integer &rhs) -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            if (*rhs.m_value == 0)
                throw IntegerError { "Attempted division by zero" };

            m_value = *m_value / *rhs.m_value;
            return *this;
        }

        auto
        operator%=(const Integer &rhs) -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            if (*rhs.m_value == 0)
                throw IntegerError { "Attempted modulo by zero" };

            m_value = *m_value % *rhs.m_value;
            return *this;
        }


        auto
        operator&(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            return Integer { *m_value & *rhs.m_value };
        }


        auto
        operator|(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            return Integer { *m_value | *rhs.m_value };
        }


        auto
        operator^(const Integer &rhs) const -> Integer
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            return Integer { *m_value ^ *rhs.m_value };
        }


        auto
        operator&=(const Integer &rhs) -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            m_value = *m_value & *rhs.m_value;
            return *this;
        }


        auto
        operator|=(const Integer &rhs) -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            m_value = *m_value | *rhs.m_value;
            return *this;
        }


        auto
        operator^=(const Integer &rhs) -> Integer &
        {
            throw_if_null(rhs,
                          "Tried to perform operations on a null integer.");
            m_value = *m_value ^ *rhs.m_value;
            return *this;
        }


        auto
        operator<<=(int shift) -> Integer &
        {
            throw_if_null("Tried to perform operations on a null integer.");
            m_value = *m_value << shift;
            return *this;
        }


        auto
        operator>>=(int shift) -> Integer &
        {
            throw_if_null("Tried to perform operations on a null integer.");
            m_value = *m_value >> shift;
            return *this;
        }


        auto
        operator<<(int shift) const -> Integer
        {
            throw_if_null("Tried to perform operations on a null integer.");
            return Integer { m_value << shift };
        }


        auto
        operator>>(int shift) const -> Integer
        {
            throw_if_null("Tried to perform operations on a null integer.");
            return Integer { m_value >> shift };
        }


        auto
        operator==(const Integer &rhs) const -> bool
        {
            return m_value == rhs.m_value;
        }


        auto
        operator!=(const Integer &rhs) const -> bool
        {
            return m_value != rhs.m_value;
        }


        auto
        operator<(const Integer &rhs) const -> bool
        {
            return m_value < rhs.m_value;
        }


        auto
        operator<=(const Integer &rhs) const -> bool
        {
            return m_value <= rhs.m_value;
        }


        auto
        operator>(const Integer &rhs) const -> bool
        {
            return m_value > rhs.m_value;
        }


        auto
        operator>=(const Integer &rhs) const -> bool
        {
            return m_value >= rhs.m_value;
        }


    private:
        std::optional<T_Int> m_value;


        void
        throw_if_null(const char *msg)
        {
            if (!m_value) throw IntegerError { msg };
        }


        void
        throw_if_null(const Integer &other, const char *msg)
        {
            if (!m_value) throw IntegerError { msg };
            if (!other.m_value) throw IntegerError { msg };
        }
    };
};


#endif /* KONCPP_TYPES__INTEGER__HH */
