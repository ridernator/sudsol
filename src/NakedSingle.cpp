#include <iostream>

#include "NakedSingle.hpp"

namespace Rules {
    NakedSingle::NakedSingle(DataStructures::Grid* grid) : Rule("Naked Single", grid) {
    }

    bool NakedSingle::solve() {
        bool returnVal = false;
        
        for (auto element : grid->getRows()) {
            while (element != NULL) {
                if (element->getCandidates().size() == 1) {
                    setValue(element, element->getCandidates()[0]);
                    
                    returnVal = true;
                }
                
                element = element->getNext(DataStructures::House::ROW);
            }
        }
        
        return returnVal;
    }
}
