//
// Created by snizzfox on 5/23/20.
//

#ifndef BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP
#define BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP

#include <string>


//TODO redo animation state, where it supports floating points and not based on a solid game tick
namespace bhe {


    struct animationState{

        const std::string name; //Animation name

        unsigned long long current_frame_index; // where it is on the left/right
        float current_time; //the timer
        const unsigned long long  number_of_frames; // total number of offsets on the left/right
        const unsigned long long  animation_offset; // where the index is on the top/bottom
        const float time_per_frame; // how long on each frame state

        animationState(const std::string &Name, unsigned long long const &Number_Of_Frames,
                       unsigned long long const &Animation_Offset, float const &Time_Per_Frame);


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
