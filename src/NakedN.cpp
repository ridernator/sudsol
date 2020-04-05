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
            for (auto element : grid->getHouses(house)) {
                DataStructures::NDLoop loop(N, 9);
                
                for (auto set : loop) {
                    auto possibleSet = getElementsWithOnlyCandidates(house, element, set);

                    if (possibleSet.size() == N) {
                        for (auto candidate : set) {
                            if (removeCandidatesFromHouse(candidate, house, element, possibleSet)) {
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
