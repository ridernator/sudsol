#include <sstream>

#include "NakedN.hpp"
#include "NDLoop.hpp"

namespace Rules {

    NakedN::NakedN(DataStructures::Grid* grid,
                   const uint64_t N) : Rule("", grid),
                                       N(N) {
        std::stringstream nameStream;
        nameStream << "Naked (N=" << N << ')';
        setName(nameStream.str());
    }

    bool NakedN::solve() {
        bool returnVal = false;

        for (auto house : DataStructures::HOUSES) {
            for (auto startOfHouse : grid->getHouses(house)) {
                DataStructures::NDLoop loop(N, grid->getOrder());
                
                for (auto candidates : loop) {
                    auto possibleSet = getElementsWithOnlyCandidates(house, startOfHouse, candidates);

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
}
