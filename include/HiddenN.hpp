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
            
            std::vector<DataStructures::Element*> getElementsWithCandidatesInSet(const DataStructures::House house,
                                                                                 DataStructures::Element* elementInHouse,
                                                                                 const std::vector<uint64_t> candidates);
    };
}