#pragma once

#include "Rule.hpp"


namespace Rules {

    class PointingSet : public Rule {
    public:

        PointingSet(DataStructures::Grid* grid);

        virtual bool solve();
    };
}