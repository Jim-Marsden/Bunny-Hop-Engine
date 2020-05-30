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


        };

    protected:
        std::map<std::string, movementDataT> _movement_data;
    public:
        void AddData(std::string const &String_view, movementDataT const &Movement_data);

        void EnableValue(std::string_view const &String_view, bool State);

        [[nodiscard]] movementDataT GetData(std::string const &String_view) const;

        [[nodiscard]] float CalculateX() const;

        [[nodiscard]] float CalculateY() const;

        [[nodiscard]] movementDataT CalculateXandY() const;

    };
} //namespace mt


#endif //MOONLIGHT_TRAILS_MOVEMENT_HPP
