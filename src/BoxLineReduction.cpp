#include <iostream>

#include "BoxLineReduction.hpp"

#include "Direction.hpp"
#include "House.hpp"

namespace Rules {

    BoxLineReduction::BoxLineReduction(DataStructures::Grid* grid) : Rule("Box/Line Reduction", grid) {
    }

    bool BoxLineReduction::solve() {
        bool returnVal = false;
        std::map<bool, DataStructures::Element*> foundElements;

        for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
            for (auto element : grid->getBoxes()) {
                foundElements.clear();

                while (element != NULL) {
                    if (element->containsCandidate(candidate)) {
                        foundElements.insert({false, element});
                    }

                    element = element->getNeighbour(DataStructures::Direction::NEXT, DataStructures::House::BOX);
                }

                if (!foundElements.empty()) {
                    for (const auto& house : DataStructures::HOUSES) {
                        if (house != DataStructures::House::BOX) {
                            DataStructures::Element* houseIterator = getStartOfHouse(house, foundElements[0]);
                            
                            while (houseIterator != NULL) {
                                
                                houseIterator = houseIterator->getNext(house);
                            }
                        }
                    }
                }
            }
        }

        return returnVal;
    }
}
