#include <sstream>
#include <algorithm>

#include "HiddenN.hpp"
#include "NDLoop.hpp"

namespace Rules {

    HiddenN::HiddenN(DataStructures::Grid* grid,
                     const uint64_t N) : Rule("", grid),
                                         N(N) {
        switch (N) {
            case 1: {
                setName("Hidden Single");
                
                break;
            }
            
            case 2: {
                setName("Hidden Pair");
                
                break;
            }
            
            case 3: {
                setName("Hidden Triple");
                
                break;
            }
            
            case 4: {
                setName("Hidden Quad");
                
                break;
            }
            
            default: {
                std::stringstream nameStream;
                nameStream << "Hidden (N=" << N << ')';
                setName(nameStream.str());
                
                break;
            }
        }
    }

    bool HiddenN::solve() {
        bool returnVal = false;
        bool thisCandidateFound;
        bool allCandidatesFound;

        for (auto house : DataStructures::HOUSES) {
            for (auto startOfHouse : grid->getHouses(house)) {
                DataStructures::NDLoop loop(N, grid->getOrder());

                for (auto candidates : loop) {
                    auto possibleSet = getElementsWithCandidatesInSet(house, startOfHouse, candidates);

                    if (possibleSet.size() == N) {
                        allCandidatesFound = true;

                        for (auto testCandidate : candidates) {
                            thisCandidateFound = false;

                            for (auto element : possibleSet) {
                                if (element->containsCandidate(testCandidate)) {
                                    thisCandidateFound = true;

                                    break;
                                }
                            }

                            if (!thisCandidateFound) {
                                allCandidatesFound = false;

                                break;
                            }
                        }

                        if (allCandidatesFound) {
                            for (auto element : possibleSet) {
                                for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
                                    if (std::find(candidates.begin(), candidates.end(), candidate) == candidates.end()) {
                                        if (element->removeCandidate(candidate)) {
                                            returnVal = true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return returnVal;
    }
    
    std::vector<DataStructures::Element*> HiddenN::getElementsWithCandidatesInSet(const DataStructures::House house,
                                                                                  DataStructures::Element* elementInHouse,
                                                                                  const std::vector<uint64_t> candidates) {
        bool valid;
        std::vector<DataStructures::Element*> returnVal;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);

        while (traveller != NULL) {
            if (!traveller->isValueSet()) {
                valid = false;

                for (auto candidate : candidates) {
                    if (traveller->containsCandidate(candidate)) {
                        valid = true;

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
