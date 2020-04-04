#pragma once

#include <stdint.h>
#include <map>
#include <utility>
#include <set>
#include <list>
#include <vector>

#include "House.hpp"
#include "Direction.hpp"

namespace DataStructures {

    class Element {
        public:
            Element(const uint64_t numPencilMarks);

            ~Element();

            Element* getNeighbour(const Direction direction,
                                  const House house);

            void setNeighbour(Element* element,
                              const Direction direction,
                              const House house);

            Element* getNext(const House house);

            Element* getPrevious(const House house);

            bool isValueSet() const;

            uint64_t getValue() const;

            void setValue(const uint64_t value);

            void unsetValue();

            bool removeCandidate(const uint64_t candidate);

            bool containsCandidate(const uint64_t candidate) const;

            const std::vector<uint64_t>& getCandidates() const;

        private:
            void resetCandidates();

            std::map<std::pair<Direction, House>, Element*> neighbours;

            std::vector<uint64_t> candidates;

            const uint64_t maxCandidates;

            uint64_t value;
    };
}