#include <sstream>
#include <algorithm>

#include "HiddenN.hpp"
#include "NDLoop.hpp"

namespace Rules {

    HiddenN::HiddenN(DataStructures::Grid* grid,
                     const uint64_t N) : Rule("", grid),
                                         N(N) {
        std::stringstream nameStream;
        nameStream << "Hidden (N=" << N << ')';
        setName(nameStream.str());
    }

    bool HiddenN::solve() {
        bool returnVal = false;

        for (auto house : DataStructures::HOUSES) {
            for (auto startOfHouse : grid->getHouses(house)) {
                DataStructures::NDLoop loop(N, grid->getOrder());

                for (auto candidates : loop) {
                    auto possibleSet = getElementsWithCandidates(house, startOfHouse, candidates);

                    if (possibleSet.size() == N) {
                        bool match = true;

                        for (auto candidate : candidates) {
                            if (getElementsWithCandidate(house, startOfHouse, candidate).size() != N) {
                                match = false;

                                break;
                            }
                        }

                        if (match) {
                            for (uint64_t candidate = 0; candidate < grid->getOrder(); ++candidate) {
                                if (std::find(candidates.begin(), candidates.end(), candidate) == candidates.end()) {
                                    for (auto element : possibleSet) {
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
}
