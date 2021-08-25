//
// Created by james on 8/23/2021.
//

#ifndef BUNNY_HOP_CORE_DESIGNER_MENU_HPP
#define BUNNY_HOP_CORE_DESIGNER_MENU_HPP
namespace bhe::designer {
struct menu_struct {
	short new_file: 1;
	short exit: 1;
	short settings: 1;
	short about: 1;
	short demo : 1;
	short mode: 4;
};
menu_struct generate_menu(menu_struct const& menu = {});
} // namespace bhe::designer

#endif //BUNNY_HOP_CORE_DESIGNER_MENU_HPP
