#pragma once

#include "Rule.hpp"


namespace Rules {
    class NakedN : public Rule {
        public:
            NakedN(DataStructures::Grid* grid,
                   const uint64_t N);

            virtual bool solve();
            
        private :
            const uint64_t N;
    };
}