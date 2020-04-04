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


//void foo(DataStructures::Element* element,
//       std::vector<DataStructures::Element*> results);
//#include <iostream>
//#include <thread>
//#include "NakedSingle.hpp"
//
//namespace Rules {
//
//    NakedSingle::NakedSingle(DataStructures::Grid* grid) : Rule("Naked Single", grid) {
//    }
//
//    void NakedSingle::foo(DataStructures::Element* element,
//                          std::vector<DataStructures::Element*> results) {
//        while (element != NULL) {
//            if (element->getCandidates().size() == 1) {
//                results.push_back(element);
//            }
//
//            element = element->getNext(DataStructures::House::ROW);
//        }
//    }
//
//    bool NakedSingle::solve() {
//        std::thread* threads[grid->getOrder()];
//        std::vector<DataStructures::Element*> results;
//        
//        for (uint64_t index = 0; index < grid->getOrder(); ++index) {
//            threads[index] = new std::thread(&NakedSingle::foo, this, grid->getRow(index), results);
//        }
//        
//        for (uint64_t index = 0; index < grid->getOrder(); ++index) {
//            threads[index]->join();
//        }
//        
//        for (DataStructures::Element* element : results) {
//            setValue(element, element->getCandidates()[0]);
//        }
//
//        return !results.empty();
//    }
//}
