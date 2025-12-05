/**
 * @file types/float.cc
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

#include "koncpp/types/float.hh"

using koncpp::types::Float;


Float::Float() noexcept : m_value(Null) {}
Float::Float(double value) noexcept : m_value { value } {}
Float::Float(const Float &other) noexcept : m_value(other.m_value) {}
Float::Float(Float &&other) noexcept
{
    if (&other != this)
    {
        m_value = other.m_value;
        other.m_value.reset();
    }
}


auto
Float::operator=(double value) noexcept -> Float &
{
    m_value = value;
    return *this;
}


auto
Float::operator=(const Float &other) noexcept -> Float &
{
    if (&other != this) m_value = other.m_value;
    return *this;
}


auto
Float::operator=(Float &&other) noexcept -> Float
{
    if (&other != this)
    {
        m_value = other.m_value;
        other.m_value.reset();
    }

    return *this;
}


auto
Float::type() const noexcept -> ValueType
{
    return ValueType::Float;
}


auto
Float::get() const noexcept -> std::optional<double>
{
    return m_value;
}


void
Float::set(double value) noexcept
{
    m_value = value;
}


auto
Float::operator+() const noexcept -> Float
{
    return *this;
}


auto
Float::operator-() const noexcept -> Float
{
    return Float { -m_value.value() };
}


auto
Float::operator++() noexcept -> Float &
{
    m_value = *m_value + 1;
    return *this;
}


auto
Float::operator++(int) noexcept -> Float
{
    Float tmp { *this };
    ++(*this);
    return tmp;
}


auto
Float::operator--() noexcept -> Float &
{
    m_value = *m_value - 1;
    return *this;
}


auto
Float::operator--(int) noexcept -> Float
{
    Float tmp { *this };
    --(*this);
    return tmp;
}


auto
Float::operator+(const Float &rhs) const noexcept -> Float
{
    return Float { *m_value + *rhs.m_value };
}


auto
Float::operator-(const Float &rhs) const noexcept -> Float
{
    return Float { *m_value - *rhs.m_value };
}

auto
Float::operator*(const Float &rhs) const noexcept -> Float
{
    return Float { *m_value * *rhs.m_value };
}

auto
Float::operator/(const Float &rhs) const -> Float
{
    if (*rhs.m_value == 0) throw FloatError { "division by zero" };

    return Float { *m_value / *rhs.m_value };
}


auto
Float::operator+=(const Float &rhs) noexcept -> Float &
{
    m_value = *m_value + *rhs.m_value;
    return *this;
}

auto
Float::operator-=(const Float &rhs) noexcept -> Float &
{
    m_value = *m_value - *rhs.m_value;
    return *this;
}

auto
Float::operator*=(const Float &rhs) noexcept -> Float &
{
    m_value = *m_value * *rhs.m_value;
    return *this;
}

auto
Float::operator/=(const Float &rhs) -> Float &
{
    if (*rhs.m_value == 0.0F) throw FloatError { "division by zero" };

    m_value = *m_value / *rhs.m_value;
    return *this;
}


auto
Float::operator==(const Float &rhs) const noexcept -> bool
{
    return m_value == rhs.m_value;
}


auto
Float::operator!=(const Float &rhs) const noexcept -> bool
{
    return m_value != rhs.m_value;
}


auto
Float::operator<(const Float &rhs) const noexcept -> bool
{
    return m_value < rhs.m_value;
}


auto
Float::operator<=(const Float &rhs) const noexcept -> bool
{
    return m_value <= rhs.m_value;
}


auto
Float::operator>(const Float &rhs) const noexcept -> bool
{
    return m_value > rhs.m_value;
}


auto
Float::operator>=(const Float &rhs) const noexcept -> bool
{
    return m_value >= rhs.m_value;
}


Float::
operator float() const noexcept
{
    return *m_value;
}


Float::
operator double() const noexcept
{
    return *m_value;
}
