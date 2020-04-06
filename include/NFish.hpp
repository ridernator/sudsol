#pragma once

#include "Rule.hpp"


namespace Rules {
    class NFish : public Rule {
        public:
            NFish(DataStructures::Grid* grid,
                  const uint64_t N);

            virtual bool solve();
            
        private :
            const uint64_t N;
    };
}