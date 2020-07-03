//
// Created by snizzfox on 5/23/20.
//

#include "animationState.hpp"
#include <iostream>

bhe::animationState::animationState(const std::string &Name, unsigned long long const &Number_Of_Frames,
                                    unsigned long long const &Animation_Offset, long const &Time_Per_Frame)
        : current_frame_index{0},
          current_time{0}, number_of_frames{Number_Of_Frames},
          animation_offset{Animation_Offset}, time_per_frame{Time_Per_Frame} {

}

auto bhe::animationState::isReadForNextFrame() -> bool {


    return false;
}

auto bhe::animationState::countNextFrame(std::chrono::microseconds time_span) -> void {

    current_time = time_span.count() - current_time;
    if (current_time < 0) {
        current_time = this->time_per_frame;
        current_frame_index++;
        if (current_frame_index > this->number_of_frames)
            current_frame_index = 0;
    }

}

auto bhe::animationState::getCurrentFameIndex() const -> decltype(current_time) {
    return current_frame_index;
}
