//
// Created by snizzfox on 5/29/20.
//

#ifndef MOONLIGHT_TRAILS_MOVEMENT_HPP
#define MOONLIGHT_TRAILS_MOVEMENT_HPP

#include <string_view>
#include <map>

namespace mt {
    class movement {


    public:


        struct movementDataT {
            //std::string_view name;
            bool enabled{};
            float x{}, y{};
            bool enabled_timer{};
            int timer{};
            int max_timer{};
            //movementDataT() = default;


        };

    protected:
        std::map<std::string, movementDataT> _movement_data;
    public:
        void AddData(std::string const &String_view, movementDataT const &Movement_data);

        void EnableValue(std::string_view const &String_view, bool State);

        [[nodiscard]] movementDataT GetData(std::string const &String_view) const;

        [[nodiscard]] float CalculateX();

        [[nodiscard]] float CalculateY();

        [[nodiscard]] movementDataT CalculateXandY();

        void ResetTimer(std::string_view const &Value);

    };
} //namespace mt


#endif //MOONLIGHT_TRAILS_MOVEMENT_HPP
