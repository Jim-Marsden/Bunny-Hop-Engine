//
// Created by snizzfox on 5/29/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_MOVEMENT_HPP
#define BUNNY_HOP_CORE_SRC_BHE_CORE_MOVEMENT_HPP

#include <string_view>
#include <map>

namespace bhe {
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
        std::map<std::string, movementDataT> movement_data_;
    public:
        void AddData(std::string const &String_View, movementDataT const &Movement_Data);

        void EnableValue(std::string_view const &String_View, bool State);

        [[nodiscard]] movementDataT GetData(std::string const &String_View) const;

        [[nodiscard]] float CalculateX();

        [[nodiscard]] float CalculateY();

        [[nodiscard]] movementDataT CalculateXandY();

        void ResetTimer(std::string_view const &Value);

    };
} //namespace bhe


#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_MOVEMENT_HPP
