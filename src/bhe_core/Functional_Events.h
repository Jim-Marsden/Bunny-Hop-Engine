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


template <class iterator_type, class Render_Surface_T>
auto draw( iterator_type begin, iterator_type end, Render_Surface_T const &Render_Surface) {
  std::for_each(begin, end, [&Render_Surface](decltype(*begin) const &element) {
    Render_Surface.draw(element);
  });

}

    template <class iterator_type, class Function_T>
auto entity_update(iterator_type begin, iterator_type  end, iterator_type Function){
  std::for_each(begin, end, Function);
  }
} // namespace bhe

#endif //BUNNY_HOP_CORE_SRC_BHE_CORE_FUNCTIONAL_EVENTS_H
