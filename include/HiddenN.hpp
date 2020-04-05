#pragma once

#include "Rule.hpp"


namespace Rules {
    class HiddenN : public Rule {
        public:
            HiddenN(DataStructures::Grid* grid,
                    const uint64_t N);

            virtual bool solve();
            
        private :
            const uint64_t N;
    };
}