//
// Created by snizzfox on 5/23/20.
//

#ifndef BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP
#define BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP

#include <string>
#include <chrono>

#include <bhe_core/Return_Status.hpp>


//TODO redo animation state, where it supports floating points and not based on a solid game tick
namespace bhe {


    struct animationState {

        const std::string name; //Animation name

        unsigned long long current_frame_index; // where it is on the left/right
        long current_time; //the timer as microseconds
        const unsigned long long number_of_frames; // total number of offsets on the left/right
        const unsigned long long animation_offset; // where the index is on the top/bottom
        const long time_per_frame; // how long on each frame state

        animationState(const std::string &Name, unsigned long long const &Number_Of_Frames,
                       unsigned long long const &Animation_Offset, long const &Time_Per_Frame);

        [[nodiscard]] auto isReadForNextFrame() -> returnStatus<bool>; //
        auto countNextFrame(std::chrono::microseconds time_span) -> returnStatus<void>;

        [[nodiscard]] auto getCurrentFameIndex() const -> returnStatus<decltype(current_frame_index)>;

        /*animationState() = default;
        animationState(animationState const &) = default;
        animationState(animationState &&) = default;
        ~animationState() = default;
        animationState &operator=(animationState const &) = default;
        animationState &operator=(animationState &&) = default;*/

    };
    struct animationStateOld {
        [[deprecated]] animationStateOld() = default;

        std::string name;
        unsigned long long  number_of_frames;
        unsigned long long  frames_per_animation_frame;
        unsigned long long  sprite_index;
        unsigned long long  current_frame_count;
        unsigned long long  hieght_offset;
    };
} // namespace bhe

#endif // BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP
