//
// Created by Jim on 12/7/23.
//

#pragma once
#include <chrono>

namespace bhe {


class delta_time {
public:
    using clock = std::chrono::steady_clock;
    using time_point = std::chrono::time_point<clock>;
    using duration = std::chrono::duration<float>; // seconds as float

    delta_time() = default;

    /**
     * \brief The explicit constructor for constructing with a time point.
     * \param tp the time point to set the two time points
     */
    constexpr explicit delta_time(time_point const & tp);

    /**
     * \brief Shifts the current time into m_time_point1 and m_time_point1 into m_time_point2.
     */
    void shift() noexcept;

    /**
     * \brief \brief Shifts the parameter into time_point1 and m_time_point1 into m_time_point2.
     * \param new_first The value to be placed into time_point1
     */
    constexpr void shift(time_point const & new_first) noexcept;

    /**
     * \brief returns a duration object, for the elapsed time between the two time internal
     * time points.
     * \return (durration)(m_time_point1 - m_time_point2)
     */
    [[nodiscard]] constexpr duration delta() const noexcept;

    // Mainly used for unit testing, don't rely on these.
    [[nodiscard]] time_point const &get_first_time_point() noexcept;
    [[nodiscard]] time_point const &get_second_time_point() noexcept;

private:
    time_point m_time_point1{clock::now()};
    time_point m_time_point2{m_time_point1};
};

    constexpr delta_time::duration delta_time::delta() const noexcept
    {
        return std::chrono::duration_cast<duration>(m_time_point1 - m_time_point2);
    }

    constexpr void delta_time::shift(time_point const & new_first) noexcept
    {
        m_time_point2 = std::exchange(m_time_point1, new_first);
    }
} // bhe

