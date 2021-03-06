#include <iostream>

#include "PointingSet.hpp"

#include "Direction.hpp"
#include "House.hpp"

namespace Rules {

    PointingSet::PointingSet(DataStructures::Grid* grid) : Rule("Pointing Set", grid) {
    }

    bool PointingSet::solve() {
        bool returnVal = false;

        for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
            for (auto startOfBox : grid->getBoxes()) {
                auto elements = getElementsWithCandidate(DataStructures::House::BOX, startOfBox, candidate);

                if (!elements.empty()) {
                    if (areElementsInSameHouse(elements, DataStructures::House::ROW)) {
                        if (removeCandidatesFromHouse(candidate, DataStructures::House::ROW, *(elements.begin()), elements)) {
                            returnVal = true;
                        }
                    } else if (areElementsInSameHouse(elements, DataStructures::House::COLUMN)) {
                        if (removeCandidatesFromHouse(candidate, DataStructures::House::COLUMN, *(elements.begin()), elements)) {
                            returnVal = true;
                        }
                    }
                }
            }
        }

        return returnVal;
    }
}
