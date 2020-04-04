#pragma once

#include "Rule.hpp"


namespace Rules {

    class IntersectionRemoval : public Rule {
    public:

        IntersectionRemoval(DataStructures::Grid* grid);

        virtual bool solve();
    };
}