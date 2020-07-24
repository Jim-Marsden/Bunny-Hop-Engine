//
// Created by snizzfox on 7/23/20.
//

#ifndef BUNNY_HOP_CORE_BASEPANNEL_HPP
#define BUNNY_HOP_CORE_BASEPANNEL_HPP


class basePanel {
public:
    basePanel() = default;

    basePanel(basePanel const &) = default;

    basePanel(basePanel &&) = default;

    virtual ~basePanel() = default;

    basePanel &operator=(basePanel const &) = default;

    basePanel &operator=(basePanel &&) = default;

protected:


};


#endif //BUNNY_HOP_CORE_BASEPANNEL_HPP
