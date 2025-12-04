/**
 * @file types/boolean.cc
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

#include "koncpp/types/boolean.hh"

using koncpp::types::Boolean;


Boolean::Boolean() noexcept : m_value(Value::Null) {}
Boolean::Boolean(const Boolean &other) noexcept : m_value(other.m_value) {}
Boolean::Boolean(Boolean &&other) noexcept
{
    if (this != &other)
    {
        m_value       = other.m_value;
        other.m_value = Value::Null;
    }
}


auto
Boolean::operator=(const Boolean &other) noexcept -> Boolean &
{
    m_value = other.m_value;
    return *this;
}


auto
Boolean::operator=(Boolean &&other) noexcept -> Boolean &
{
    if (this != &other)
    {
        m_value       = other.m_value;
        other.m_value = Value::Null;
    }

    return *this;
}


[[nodiscard]]
auto
Boolean::type() const noexcept -> ValueType
{
    return ValueType::Boolean;
}


[[nodiscard]]
auto
Boolean::get() const noexcept -> std::optional<bool>
{
    if (m_value == Value::Null) return Null;
    return static_cast<bool>(m_value);
}


Boolean::
operator bool() const noexcept
{
    return m_value == Value::True;
}


auto
Boolean::operator!() const noexcept -> bool
{
    return m_value != Value::True;
}


auto
Boolean::operator==(const Boolean &rhs) const noexcept -> bool
{
    return m_value == rhs.m_value;
}


auto
Boolean::operator!=(const Boolean &rhs) const noexcept -> bool
{
    return m_value != rhs.m_value;
}


auto
Boolean::operator&&(const Boolean &rhs) const noexcept -> Boolean
{
    return { static_cast<bool>(*this) && static_cast<bool>(rhs) };
}


auto
Boolean::operator||(const Boolean &rhs) const noexcept -> Boolean
{
    return { static_cast<bool>(*this) || static_cast<bool>(rhs) };
}


auto
Boolean::operator&=(const Boolean &rhs) -> Boolean &
{
    *this = static_cast<bool>(*this) && static_cast<bool>(rhs);
    return *this;
}


auto
Boolean::operator|=(const Boolean &rhs) -> Boolean &
{
    *this = static_cast<bool>(*this) || static_cast<bool>(rhs);
    return *this;
}
