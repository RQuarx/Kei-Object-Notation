#ifndef KONCPP_TYPES__STRING__HH
#define KONCPP_TYPES__STRING__HH
#include <memory>

#include "koncpp/types/base.hh"


namespace koncpp::types
{
    /**
     * @brief A representation of a string value inside Kei Object Notation.
     *
     * The @c String class is a @c Nullable data type that stores a
     * null-terminated array of bytes. This type works similarly to how
     * @c std::string works, but slimmer.
     *
     * @tparam T_Allocator The allocator used to allocate the internal storage.
     */
    template <typename T_Allocator = std::allocator<char>>
    class String : public BaseType
    {
    public:
        using SizeType = std::size_t;
        static constexpr SizeType Npos { static_cast<SizeType>(-1) };


        String() noexcept = default;
        String(const String &other) noexcept
        {
            if (other.m_string != nullptr)
                mf_init_from(other.m_string, other.m_capacity);
        }

        String(String &&other) noexcept
            : m_string(other.m_string), m_capacity(other.m_capacity)
        {
            other.m_string   = nullptr;
            other.m_capacity = 0;
        }


        ~String() override { mf_deallocate(); }


        auto
        operator=(const char *string) -> String &
        {
            mf_deallocate();
            mf_init_from(string, mf_length(string));
            return *this;
        }


        auto
        operator=(const String &other) noexcept -> String &
        {
            if (this != &other)
            {
                mf_deallocate();
                if (other.m_string != nullptr)
                    mf_init_from(other.m_string, other.m_capacity);
            }

            return *this;
        }

        auto
        operator=(String &&other) noexcept -> String
        {
            if (this != &other)
            {
                mf_deallocate();
                m_string         = other.m_string;
                m_capacity       = other.m_capacity;
                other.m_string   = nullptr;
                other.m_capacity = 0;
            }

            return *this;
        }


        /**
         * @brief Duplicate a string @p string into the internal storage.
         *
         * @param string The string to be duplicated.
         * @param length The length of the string, defaults to @e Npos .
         *               @p string must be null-terminated when
         *               the value is @e Npos .
         */
        String(const char *string, SizeType length = Npos)
        {
            if (string == nullptr) return;
            mf_init_from(string, length == Npos ? mf_length(string) : length);
        }


        [[nodiscard]]
        constexpr auto
        type() const noexcept -> ValueType override
        {
            return ValueType::String;
        }


    private:
        char       *m_string { nullptr };
        SizeType    m_capacity { Npos };
        T_Allocator m_alloc;


        void
        mf_init_from(const char *s, SizeType len)
        {
            m_capacity = len;
            m_string   = m_alloc.allocate(len + 1);

            mf_memcpy(s, m_string, len);
            m_string[len] = '\0';
        }


        void
        mf_deallocate()
        {
            if (m_string != nullptr)
            {
                m_alloc.deallocate(m_string, m_capacity + 1);
                m_string = nullptr;
            }
        }


        [[nodiscard]]
        static auto
        mf_length(const char *string) -> SizeType
        {
            SizeType length { 0 };
            for (const char *i { string }; *i != '\0'; i++) length++;
            return length;
        }


        static void
        mf_memcpy(const char *src, char *dst, SizeType length)
        {
            for (SizeType i { 0 }; i < length; i++) dst[i] = src[i];
        }
    };
}


#endif /* KONCPP_TYPES__STRING__HH */
