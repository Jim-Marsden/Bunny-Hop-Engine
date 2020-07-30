//
// Created by snizzfox on 7/24/20.
//

#include <bhe_core/animationState.hpp>
#include <catch2/catch.hpp>


TEST_CASE("bhe::animationState::GetCurrentFameIndex") {
    /* animationState(const std::string &Name, unsigned long long const &Number_Of_Frames,
    unsigned long long const &Animation_Offset, long const &Time_Per_Frame);


     */

    auto number_of_frames{4ull}, animation_offset{0ull};
    auto time_per_frame{5l};
    bhe::animationState animation_state{"Name", number_of_frames, animation_offset, time_per_frame};


    REQUIRE(true);


}
