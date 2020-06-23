//
// Created by snizzfox on 5/23/20.
//

#include "animationState.hpp"

bhe::animationState::animationState(const std::string &Name, unsigned long long const &Number_Of_Frames,
                                    unsigned long long const &Animation_Offset, float const &Time_Per_Frame) : current_frame_index{0},
                                            current_time{0.0F}, number_of_frames{Number_Of_Frames},
                                            animation_offset{Animation_Offset}, time_per_frame{Time_Per_Frame} {

}
