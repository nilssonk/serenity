#ifndef STACKWRITER_H
#define STACKWRITER_H

namespace Kernel {

class StackWriter {
    FlatPtr m_top;

public:
    explicit StackWriter(FlatPtr top) noexcept
        : m_top { top }
    {
    }

    template<typename T>
    [[nodiscard]] T& emplace(size_t offset = 0) noexcept
    {
        VERIFY(offset <= sizeof(T));

        m_top -= sizeof(T) - offset;
        return *reinterpret_cast<T*>(m_top);
    }

    template<typename T>
    void write(T x) noexcept
    {
        m_top -= sizeof(T);
        *reinterpret_cast<T*>(m_top) = x;
    }

    [[nodiscard]] FlatPtr get() const noexcept { return m_top; };
};

}

#endif
