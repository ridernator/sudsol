#pragma once

#include "Rule.hpp"


namespace Rules {
    class NakedSingle : public Rule {
        public:
            NakedSingle(DataStructures::Grid* grid);

            virtual bool solve();
    };
}