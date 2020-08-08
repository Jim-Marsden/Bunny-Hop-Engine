//
// Created by snizzfox on 8/7/20.
//

#ifndef BUNNY_HOP_CORE_SRC_BHE_CORE_FUNCTIONAL_EVENTS_H
#define BUNNY_HOP_CORE_SRC_BHE_CORE_FUNCTIONAL_EVENTS_H

#include <algorithm>
#include <concepts>

namespace bhe::functional {

template <class Render_Surface_T>
concept Render_Surface_Concept = requires(Render_Surface_T RS) {
 RS.draw;
};


template <class iterator_type>
constexpr auto draw( std::input_iterator auto begin, std::input_iterator auto end, Render_Surface_Concept auto const &Render_Surface) {
  std::for_each(begin, end, [&Render_Surface](auto const &element) {
    Render_Surface.draw(element);
  });

}


constexpr auto entity_update(std::input_iterator auto begin, std::input_iterator auto end, auto Function){
  std::for_each(begin, end, Function);
  }
} // namespace bhe

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_FUNCTIONAL_EVENTS_H
