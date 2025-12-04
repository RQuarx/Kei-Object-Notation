/**
 * @file koncpp/types/base.hh
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

#ifndef KONCPP_TYPES__BASE__HH
#define KONCPP_TYPES__BASE__HH
#include <cstdint>
#include <format>
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


    class Exception
    {
    public:
        template <typename... T_Args>
        Exception(std::format_string<T_Args...> fmt, T_Args &&...args)
            : m_msg(std::format(fmt, std::forward<T_Args>(args)...))
        {
        }


        [[nodiscard]]
        auto
        what() const noexcept -> const char *
        {
            return m_msg.c_str();
        }


    private:
        std::string m_msg;
    };


    namespace types
    {
        inline constexpr auto Null { std::nullopt };


        struct BaseType
        {
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
                          "T_ToType must derive from BaseType");

            if (auto *ptr { dynamic_cast<T_ToType *>(&base) }; ptr != nullptr)
                return *ptr;

            throw std::bad_cast {};
        }
    }
}


#endif /* KONCPP_TYPES__BASE__HH */
