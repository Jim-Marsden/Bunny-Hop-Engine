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

auto bhe::animationState::IsReadForNextFrame() -> returnStatus<bool> {

  return {false};
}

auto bhe::animationState::CountNextFrame(std::chrono::microseconds Time_Span) -> returnStatus<void> {

  current_time += Time_Span.count();
  //std::cout << current_time << ':' <<  time_per_frame << '\n';
  if (current_time > time_per_frame) {
    current_time = 0;
    current_frame_index++;
    if (current_frame_index > this->number_of_frames)
      current_frame_index = 0;
  }
  return {};

}

auto bhe::animationState::GetCurrentFameIndex() const -> returnStatus<decltype(current_frame_index)> {
  return {current_frame_index};
}
