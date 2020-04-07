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
            
            std::vector<DataStructures::Element*> getElementsWithCandidatesOnlyInSet(const DataStructures::House house,
                                                                                     DataStructures::Element* elementInHouse,
                                                                                     const std::vector<uint64_t> candidates);
    };
}