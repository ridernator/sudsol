#include <sstream>

#include "NFish.hpp"
#include "NDLoop.hpp"

namespace Rules {

    NFish::NFish(DataStructures::Grid* grid,
                 const uint64_t N) : Rule("", grid),
                                     N(N) {
        switch (N) {
            case 2: {
                setName("X-Wing");
                
                break;
            }
            
            case 3: {
                setName("Swordfish");
                
                break;
            }
            
            case 4: {
                setName("Jellyfish");
                
                break;
            }
            
            default: {
                std::stringstream nameStream;
                nameStream << "Basic Fish (N=" << N << ')';
                setName(nameStream.str());
                
                break;
            }
        }    
    }

    bool NFish::solve() {
        bool returnVal = false;
        DataStructures::NDLoop loop(N, grid->getOrder());
        std::vector<std::vector<DataStructures::Element*>> results;
        
        for (auto houseNums : loop) {
            for (auto houseA : DataStructures::HOUSES) {
                for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
                    results.clear();

                    for (auto houseNum : houseNums) {
                        auto result = getElementsWithCandidate(houseA, grid->getHouse(houseA, houseNum), candidate);

                        if ((result.size() >=2 ) && (result.size() <= N)) {
                            results.push_back(result);
                        } else {
                            break;
                        }                
                    }

                    if (results.size() == N) {
                        std::vector<DataStructures::Element*> allResults;
                        
                        for (auto result : results) {
                            for (auto element : result) {
                                allResults.push_back(element);
                            }
                        }
                        
                        for (auto houseB : DataStructures::HOUSES) {
                            if (houseA != houseB) {
                                std::set<DataStructures::Element*> secondHouses;

                                for (auto element : allResults) {
                                    secondHouses.insert(getStartOfHouse(houseB, element));
                                }
                                
                                if (secondHouses.size() == N) {
                                    for (auto startOfHouse : secondHouses) {
                                        if (removeCandidatesFromHouse(candidate, houseB, startOfHouse, allResults)) {
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
}
