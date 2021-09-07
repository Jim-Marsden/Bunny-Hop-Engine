//
// Created by Jim Marsden on 8/7/20.
//

#ifndef BUNNY_HOP_CORE_FUNCTIONAL_EVENTS_H
#define BUNNY_HOP_CORE_FUNCTIONAL_EVENTS_H

#include <algorithm>
#include <concepts>

namespace bhe::functional {

template <class Render_Surface_T>
concept Render_Surface_Concept = requires(Render_Surface_T render_surface_t) {
 render_surface_t.draw;
};


template <class iterator_type, class Render_Surface_T>
auto draw( iterator_type begin, iterator_type end, Render_Surface_T const &render_surface) {
  std::for_each(begin, end, [&render_surface](decltype(*begin) const &element) {
    render_surface.draw(element);
  });

}

    template <class iterator_type, class Function_T>
auto entity_update(iterator_type begin, iterator_type  end, iterator_type function){
  std::for_each(begin, end, function);
  }
} // namespace bhe

#endif //BUNNY_HOP_CORE_FUNCTIONAL_EVENTS_H
