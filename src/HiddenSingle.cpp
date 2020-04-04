#include <iostream>

#include "HiddenSingle.hpp"

namespace Rules {

    HiddenSingle::HiddenSingle(DataStructures::Grid* grid) : Rule("Hidden Single", grid) {
    }

    bool HiddenSingle::solve() {
        bool returnVal = false;
        DataStructures::Element* storedElement;
        uint64_t numElementsWithCandidate;

        for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
            for (const auto& house : DataStructures::HOUSES) {
                for (auto element : grid->getHouses(house)) {
                    numElementsWithCandidate = 0;

                    while (element != NULL) {
                        if (element->containsCandidate(candidate)) {
                            storedElement = element;
                            
                            if (++numElementsWithCandidate == 2) {
                                break;
                            }
                        }

                        element = element->getNext(house);
                    }

                    if (numElementsWithCandidate == 1) {
                        setValue(storedElement, candidate);

                        returnVal = true;
                    }
                }
            }
        }

        return returnVal;
    }
}
