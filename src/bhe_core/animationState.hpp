//
// Created by snizzfox on 5/23/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_ANIMATIONSTATE_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_ANIMATIONSTATE_HPP

#include <string>
#include <chrono>

#include <bhe_core/Return_Status.hpp>


//TODO redo animation state, where it supports floating points and not based on a solid game tick
namespace bhe {


    struct animationState {

        const std::string name; //Animation get_name

        unsigned long long current_frame_index; // where it is on the left/right
        long long current_time; //the timer as microseconds
        const unsigned long long number_of_frames; // total number of offsets on the left/right
        const unsigned long long animation_offset; // where the index is on the top/bottom
        const long time_per_frame; // how long on each frame state

        animationState(const std::string &name, unsigned long long const &number_of_frames,
                       unsigned long long const &animation_offset, long const &time_per_frame);

        [[nodiscard]] auto is_read_for_next_frame() -> returnStatus<bool>; //
        auto count_next_frame(std::chrono::microseconds time_span) -> returnStatus<void>;

        [[nodiscard]] auto get_current_fame_index() const -> returnStatus<decltype(current_frame_index)>;

        /*animationState() = default;
        animationState(animationState const &) = default;
        animationState(animationState &&) = default;
        ~animationState() = default;
        animationState &operator=(animationState const &) = default;
        animationState &operator=(animationState &&) = default;*/

    };

} // namespace bhe

#endif // BUNNY_HOP_CORE_SRC_BHE_CORE_ANIMATIONSTATE_HPP
