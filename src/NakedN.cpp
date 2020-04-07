#include <sstream>
#include <algorithm>

#include "NakedN.hpp"
#include "NDLoop.hpp"

namespace Rules {

    NakedN::NakedN(DataStructures::Grid* grid,
                   const uint64_t N) : Rule("", grid),
                                       N(N) {
        switch (N) {
            case 1: {
                setName("Naked Single");
                
                break;
            }
            
            case 2: {
                setName("Naked Pair");
                
                break;
            }
            
            case 3: {
                setName("Naked Triple");
                
                break;
            }
            
            case 4: {
                setName("Naked Quad");
                
                break;
            }
            
            default: {
                std::stringstream nameStream;
                nameStream << "Naked (N=" << N << ')';
                setName(nameStream.str());
                
                break;
            }
        }        
    }

    bool NakedN::solve() {        
        bool returnVal = false;

        for (auto house : DataStructures::HOUSES) {
            for (auto startOfHouse : grid->getHouses(house)) {
                DataStructures::NDLoop loop(N, grid->getOrder());
                
                for (auto candidates : loop) {
                    auto possibleSet = getElementsWithCandidatesOnlyInSet(house, startOfHouse, candidates);

                    if (possibleSet.size() == N) {
                        for (auto candidate : candidates) {
                            if (removeCandidatesFromHouse(candidate, house, startOfHouse, possibleSet)) {
                                returnVal = true;
                            }
                        }
                    }
                }
            }
        }

        return returnVal;
    }
    
    std::vector<DataStructures::Element*> NakedN::getElementsWithCandidatesOnlyInSet(const DataStructures::House house,
                                                                                     DataStructures::Element* elementInHouse,
                                                                                     const std::vector<uint64_t> candidates) {
        bool valid;
        std::vector<DataStructures::Element*> returnVal;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);

        while (traveller != NULL) {
            if (!traveller->isValueSet()) {
                valid = true;

                for (auto candidate : traveller->getCandidates()) {
                    if (std::find(candidates.begin(), candidates.end(), candidate) == candidates.end()) {
                        valid = false;

                        break;
                    }
                }

                if (valid) {
                    returnVal.push_back(traveller);
                }
            }

            traveller = traveller->getNext(house);
        }

        return returnVal;
    }
}
