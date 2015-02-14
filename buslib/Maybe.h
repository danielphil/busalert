#pragma once

template <typename T>
class Maybe
{
public:
    Maybe() : m_has_value(false) {
    }

    Maybe(
        const T& value
    ) :
        m_has_value(true),
        m_value(value)
    {
    }

    T Value() const {
        return m_value;
    }

    bool HasValue() const {
        return m_has_value;
    }

private:
    bool m_has_value;
    T m_value;
};
