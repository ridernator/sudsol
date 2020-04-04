#pragma once

#include "Rule.hpp"


namespace Rules {

    class HiddenSingle : public Rule {
    public:

        HiddenSingle(DataStructures::Grid* grid);

        virtual bool solve();
    };
}