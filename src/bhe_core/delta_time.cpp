//
// Created by Jim on 12/7/23.
//

#include "delta_time.hpp"
#include <utility>

namespace bhe {
    void delta_time::shift() noexcept
    {
        shift(clock::now());
    }

    delta_time::time_point const& delta_time::get_first_time_point() noexcept
    {
        return m_time_point1;
    }

    delta_time::time_point const& delta_time::get_second_time_point() noexcept
    {
        return m_time_point2;
    }

    constexpr delta_time::delta_time(time_point const& tp) : m_time_point1{tp}, m_time_point2{tp}{}


} // bhe