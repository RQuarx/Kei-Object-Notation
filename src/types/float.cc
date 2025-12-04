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
