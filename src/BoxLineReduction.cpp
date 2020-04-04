#include <iostream>

#include "BoxLineReduction.hpp"

#include "Direction.hpp"
#include "House.hpp"

namespace Rules {

    BoxLineReduction::BoxLineReduction(DataStructures::Grid* grid) : Rule("Box/Line Reduction", grid) {
    }

    bool BoxLineReduction::solve() {
        bool returnVal = false;

        for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
            for (auto row : grid->getRows()) {
                auto elements = getElementsWithCandidate(DataStructures::House::ROW, row, candidate);
                
                if (areElementsInSameHouse(elements, DataStructures::House::BOX)) {
                    if (removeCandidatesFromHouse(candidate, DataStructures::House::BOX, *(elements.begin()), elements)) {
                        returnVal = true;
                    }
                }
            }
        }

        return returnVal;
    }
}
