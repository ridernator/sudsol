#include <algorithm>

#include "Element.hpp"

namespace DataStructures {

    Element::Element(const uint64_t maxCandidates) : maxCandidates(maxCandidates),
                                                     value(UINT64_MAX) {
        resetCandidates();   
    }

    Element::~Element() {

    }

    Element* Element::getNeighbour(const Direction direction,
                const House house) {
        return neighbours[{direction, house}];
    }
    
    Element* Element::getNext(const House house) {
        return getNeighbour(Direction::NEXT, house);
    }

    Element* Element::getPrevious(const House house) {
        return getNeighbour(Direction::PREVIOUS, house);
    }
    
    void Element::setNeighbour(Element* element, 
                               const Direction direction,
                               const House house) {
        neighbours[{direction, house}] = element;
    }

    uint64_t Element::getValue() const {
        return value;
    }

    void Element::setValue(const uint64_t value) {
        this->value = value;
        candidates.clear();
    }

    bool Element::isValueSet() const {
        return candidates.empty();
    }

    void Element::unsetValue() {        
        resetCandidates();
    }

    void Element::resetCandidates() {
        candidates.clear();
        
        for (uint64_t candidate = 0; candidate < maxCandidates; ++candidate) {
            candidates.push_back(candidate);
        }
    }

    bool Element::removeCandidate(const uint64_t candidate) {
        bool returnVal = false;
        auto iterator = std::find(candidates.begin(), candidates.end(), candidate);

        if (iterator != candidates.end()) {
            candidates.erase(iterator);

            returnVal = true;
        }

        return returnVal;
    }

    bool Element::containsCandidate(const uint64_t candidate) const {
        bool returnVal = false;
        
        if (std::find(candidates.begin(), candidates.end(), candidate) != candidates.end()) {
            returnVal = true;
        }
        
        return returnVal;
    }

    const std::vector<uint64_t>& Element::getCandidates() const {
        return candidates;
    }

}