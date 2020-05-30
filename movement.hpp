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
        movement() = default;

        movement(movement &Copy) = default;

        movement(movement &&Move) = default;

        struct movementDataT {
            //std::string_view name;
            bool enabled{};
            float x{}, y{};

            movementDataT() = default;

            movementDataT(movementDataT &) = default;

            movementDataT(movementDataT &&) = default;

            movementDataT(const movementDataT &) = default;

            movementDataT &operator=(movementDataT const &) = default;

        };

    protected:
        std::map<std::string_view, movementDataT> movement_data;
    public:
        void AddData(std::string_view const &String_view, movementDataT const &);

        [[nodiscard]] movementDataT GetData(std::string_view const &String_view) const;

        [[nodiscard]] float CalculateX() const;

        [[nodiscard]] float CalculateY() const;

        [[nodiscard]] movementDataT CalculateXandY() const;

    };
} //namespace mt


#endif //MOONLIGHT_TRAILS_MOVEMENT_HPP
