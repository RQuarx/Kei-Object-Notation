/**
 * @file koncpp/types/string.hh
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

#ifndef KONCPP_TYPES__STRING__HH
#define KONCPP_TYPES__STRING__HH
#include <memory>

#include "koncpp/types/base.hh"


namespace koncpp::types
{
    struct StringError : public Exception
    {
        using Exception::Exception;
    };


    /**
     * @brief A representation of a string value inside Kei Object Notation.
     *
     * The @c String class is a @c Nullable data type that stores an array
     * of null-terminated bytes.
     *
     * @tparam T_Allocator The allocator used to allocate internal storage.
     *
     * @warning Operating on a null @c String
     *          will trigger undefined behaviours.
     */
    template <typename T_Allocator = std::allocator<char>>
    class String : public BaseType
    {
        using BaseString
            = std::basic_string<char, std::char_traits<char>, T_Allocator>;

    public:
        using SizeType = BaseString::size_type;

        using Iterator             = BaseString::iterator;
        using ConstIterator        = BaseString::const_iterator;
        using ReverseIterator      = BaseString::reverse_iterator;
        using ConstReverseIterator = BaseString::const_reverse_iterator;

        static constexpr SizeType Npos { BaseString::npos };


#pragma region Constructors

        constexpr String() noexcept = default;
        String(BaseString string) : m_string(std::move(string)) {}
        String(const char *string) : m_string(BaseString { string }) {}
        String(std::string_view string)
            : m_string(BaseString { string.begin(), string.end() })
        {
        }

        String(const String &) = default;
        String(String &&)      = default;

#pragma endregion

#pragma region Assignments

        auto operator=(const String &) -> String<T_Allocator> &     = default;
        auto operator=(String &&) noexcept -> String<T_Allocator> & = default;

        auto
        operator=(BaseString string) -> String<T_Allocator> &
        {
            m_string = std::move(string);
            return *this;
        }

        auto
        operator=(std::string_view sv) -> String<T_Allocator> &
        {
            m_string = BaseString { sv.begin(), sv.end() };
            return *this;
        }

        auto
        operator=(const char *s) -> String<T_Allocator> &
        {
            m_string = BaseString { s };
            return *this;
        }

#pragma endregion

        [[nodiscard]]
        constexpr auto
        type() const noexcept -> ValueType override
        {
            return ValueType::String;
        }


        [[nodiscard]]
        auto
        get() const noexcept -> std::optional<BaseString>
        {
            return m_string;
        }


        void
        set(BaseString string)
        {
            m_string = std::move(string);
        }

#pragma region Iterators

        [[nodiscard]]
        auto
        begin() -> Iterator
        {
            return m_string->begin();
        }


        [[nodiscard]]
        auto
        end() -> Iterator
        {
            return m_string->end();
        }


        [[nodiscard]]
        auto
        begin() const -> ConstIterator
        {
            return m_string->begin();
        }


        [[nodiscard]]
        auto
        end() const -> ConstIterator
        {
            return m_string->end();
        }


        [[nodiscard]]
        auto
        cbegin() const -> ConstIterator
        {
            return m_string->cbegin();
        }

        [[nodiscard]]
        auto
        cend() const -> ConstIterator
        {
            return m_string->cend();
        }


        [[nodiscard]]
        auto
        rbegin() -> ReverseIterator
        {
            return m_string->rbegin();
        }


        [[nodiscard]]
        auto
        rend() -> ReverseIterator
        {
            return m_string->rend();
        }


        [[nodiscard]]
        auto
        rbegin() const -> ConstReverseIterator
        {
            return m_string->rbegin();
        }


        [[nodiscard]]
        auto
        rend() const -> ConstReverseIterator
        {
            return m_string->rend();
        }


        [[nodiscard]]
        auto
        crbegin() const -> ConstReverseIterator
        {
            return m_string->crbegin();
        }


        [[nodiscard]]
        auto
        crend() const -> ConstReverseIterator
        {
            return m_string->crend();
        }

#pragma endregion

#pragma region Accessors

        [[nodiscard]]
        auto
        operator[](SizeType i) -> char &
        {
            return m_string[i];
        }


        [[nodiscard]]
        auto
        operator[](SizeType i) const -> const char &
        {
            return m_string[i];
        }


        [[nodiscard]]
        auto
        at(SizeType i) -> char &
        {
            return m_string->at(i);
        }


        [[nodiscard]]
        auto
        at(SizeType i) const -> const char &
        {
            return m_string->at(i);
        }


        [[nodiscard]]
        auto
        length() const -> SizeType
        {
            return m_string->length();
        }


    private:
        std::optional<BaseString> m_string;
    };
}


#endif /* KONCPP_TYPES__STRING__HH */
