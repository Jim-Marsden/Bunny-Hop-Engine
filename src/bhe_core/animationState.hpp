//
// Created by snizzfox on 5/23/20.
//

#ifndef BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP
#define BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP

#include <string>

namespace bhe {

    struct animationState {

        std::string name;
        uint_fast64_t number_of_frames;
        uint_fast64_t frames_per_animation_frame;
        uint_fast64_t sprite_index;
        uint_fast64_t current_frame_count;
        uint_fast64_t hieght_offset;
    };
} // namespace bhe

#endif // BUNNY_HOP_ENGINE_ANIMATIONSTATE_HPP
