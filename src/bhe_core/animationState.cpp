//
// Created by snizzfox on 5/23/20.
//

#include "animationState.hpp"
#include <iostream>

bhe::animationState::animationState(const std::string &name, unsigned long long const &number_of_frames,
                                    unsigned long long const &animation_offset, long const &time_per_frame)
    :current_frame_index{0},
	 current_time{0}, number_of_frames{number_of_frames},
	 animation_offset{animation_offset}, time_per_frame{time_per_frame} {

}

auto bhe::animationState::is_read_for_next_frame() -> returnStatus<bool> {

  return {false};
}

auto bhe::animationState::count_next_frame(std::chrono::microseconds time_span) -> returnStatus<void> {

  current_time += time_span.count();
  //std::cout << current_time << ':' <<  time_per_frame << '\n';
  if (current_time > time_per_frame) {
    current_time = 0;
    current_frame_index++;
    if (current_frame_index > this->number_of_frames)
      current_frame_index = 0;
  }
  return {};

}

auto bhe::animationState::get_current_fame_index() const -> returnStatus<decltype(current_frame_index)> {
  return {current_frame_index};
}
