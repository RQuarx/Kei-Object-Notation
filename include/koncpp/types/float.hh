#ifndef KONCPP_TYPES__FLOAT__HH
#define KONCPP_TYPES__FLOAT__HH
#include "koncpp/.defs.hh"
#include "koncpp/types/base.hh"


namespace koncpp::types
{
    struct FloatError : public Exception
    {
        using Exception::Exception;
    };


    /**
     * @brief A representation of a float value inside Kei Object Notation.
     *
     * The @c Float class is a @c Nullable data type that stores a floating
     * point value the size of a @c float64 or @c double.
     *
     * It supports standard arithmetic, and comparison operations.
     * Attempting to operate on a null @c Float will throw an @c FloatError.
     */
    class KONCPP_PUBLIC Float : public BaseType
    {
    public:
        Float() noexcept;

        Float(double value) noexcept;
        Float(const Float &other) noexcept;
        Float(Float &&other) noexcept;


        auto operator=(double value) noexcept -> Float &;
        auto operator=(const Float &other) noexcept -> Float &;
        auto operator=(Float &&other) noexcept -> Float;


        [[nodiscard]]
        auto type() const noexcept -> ValueType override;


        [[nodiscard]]
        auto get() const noexcept -> std::optional<double>;


        void set(double value) noexcept;


        auto operator+() const noexcept -> Float;
        auto operator-() const noexcept -> Float;


        auto operator++() noexcept -> Float &;
        auto operator++(int) noexcept -> Float;
        auto operator--() noexcept -> Float &;
        auto operator--(int) noexcept -> Float;


        auto operator+(const Float &rhs) const noexcept -> Float;
        auto operator-(const Float &rhs) const noexcept -> Float;
        auto operator*(const Float &rhs) const noexcept -> Float;
        auto operator/(const Float &rhs) const -> Float;


        auto operator+=(const Float &rhs) noexcept -> Float &;
        auto operator-=(const Float &rhs) noexcept -> Float &;
        auto operator*=(const Float &rhs) noexcept -> Float &;
        auto operator/=(const Float &rhs) -> Float &;


        auto operator==(const Float &rhs) const noexcept -> bool;
        auto operator!=(const Float &rhs) const noexcept -> bool;
        auto operator<(const Float &rhs) const noexcept -> bool;
        auto operator>(const Float &rhs) const noexcept -> bool;
        auto operator<=(const Float &rhs) const noexcept -> bool;
        auto operator>=(const Float &rhs) const noexcept -> bool;


        explicit(true) operator float() const noexcept;
        explicit(true) operator double() const noexcept;


    private:
        std::optional<double> m_value;
    };
}


#ifndef KONCPP_NO_FORMATTER

#include <format>

template <>
struct std::formatter<koncpp::types::Float, char> : std::formatter<double, char>
{
    auto
    format(const koncpp::types::Float &i, std::format_context &ctx) const
    {
        if (!i.get()) return std::format_to(ctx.out(), "null");
        return std::formatter<double, char>::format(*i.get(), ctx);
    }
};

#endif
#endif /* KONCPP_TYPES__FLOAT__HH */
