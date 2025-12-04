/**
 * @file koncpp/types/boolean.hh
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

#ifndef KONCPP_TYPES__BOOLEAN__HH
#define KONCPP_TYPES__BOOLEAN__HH
#include "koncpp/.defs.hh"
#include "koncpp/types/base.hh"


namespace koncpp::types
{
    struct BooleanError : public Exception
    {
        using Exception::Exception;
    };


    /**
     * @brief A representation of a boolean value inside Kei Object Notation.
     *
     * The @c Boolean class is a @c Nullable data type that stores a boolean
     * value (true/false).
     *
     * This class supports standard boolean operations and implicit conversion
     * to @c bool .
     *
     * @warning Operating on a null @c Boolean
     *          will trigger undefined behaviours.
     */
    class KONCPP_PUBLIC Boolean : public BaseType
    {
        enum class Value : std::uint8_t
        {
            False = 0,
            True,
            Null
        };

    public:
        Boolean() noexcept;
        Boolean(const Boolean &other) noexcept;
        Boolean(Boolean &&other) noexcept;

        template <typename T_Type>
        Boolean(T_Type value)
            requires(std::is_convertible_v<T_Type, bool>)
            : m_value(value ? Value::True : Value::False)
        {
        }


        auto operator=(const Boolean &other) noexcept -> Boolean &;
        auto operator=(Boolean &&other) noexcept -> Boolean &;

        template <typename T_Type>
        auto
        operator=(T_Type value) noexcept -> Boolean &
            requires(std::is_convertible_v<T_Type, bool>)
        {
            m_value = value ? Value::True : Value::False;
            return *this;
        }


        [[nodiscard]]
        auto type() const noexcept -> ValueType override;


        [[nodiscard]]
        auto get() const noexcept -> std::optional<bool>;


        template <typename T_Type>
        void
        set(T_Type value) noexcept
            requires(std::is_convertible_v<T_Type, bool>)
        {
            m_value = value ? Value::True : Value::False;
        }


        operator bool() const noexcept;

        auto operator!() const noexcept -> bool;

        auto operator==(const Boolean &rhs) const noexcept -> bool;
        auto operator!=(const Boolean &rhs) const noexcept -> bool;

        auto operator&&(const Boolean &rhs) const noexcept -> Boolean;
        auto operator||(const Boolean &rhs) const noexcept -> Boolean;

        auto operator&=(const Boolean &rhs) -> Boolean &;
        auto operator|=(const Boolean &rhs) -> Boolean &;


    private:
        Value m_value;
    };
}


#ifndef KONCPP_NO_FORMATTER

#include <format>

template <>
struct std::formatter<koncpp::types::Boolean> : std::formatter<bool>
{
    auto
    format(const koncpp::types::Boolean &b, std::format_context &ctx) const
    {
        if (!b.get()) return std::format_to(ctx.out(), "null");
        return std::formatter<bool, char>::format(*b.get(), ctx);
    }
};

#endif
#endif /* KONCPP_TYPES__BOOLEAN__HH */
