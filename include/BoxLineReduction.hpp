#pragma once

#include "Rule.hpp"


namespace Rules {

    class BoxLineReduction : public Rule {
    public:

        BoxLineReduction(DataStructures::Grid* grid);

        virtual bool solve();
    };
}