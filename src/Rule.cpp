#include <iostream>

#include "Rule.hpp"

namespace Rules{
    Rule::Rule(const std::string& name,
               DataStructures::Grid* grid) : grid(grid),
                                             name(name) {
        
    }

    std::set<DataStructures::Element*> Rule::getPeers(DataStructures::Element* element)  {
        std::set<DataStructures::Element*> peers;
        DataStructures::Element* traveller;

        for (const auto& house : DataStructures::HOUSES) {
            for (const auto& direction : DataStructures::DIRECTIONS) {
                traveller = element->getNeighbour(direction, house);

                while (traveller != NULL) {
                    peers.insert(traveller);

                    traveller = traveller->getNeighbour(direction, house);
                }
            }
        }
        
        return peers;
    }

    DataStructures::Element* Rule::getStartOfRow(DataStructures::Element* element) {
        return getStartOfHouse(DataStructures::House::ROW, element);
    }

    DataStructures::Element* Rule::getStartOfColumn(DataStructures::Element* element) {
        return getStartOfHouse(DataStructures::House::COLUMN, element);
    }
    
    DataStructures::Element* Rule::getStartOfBox(DataStructures::Element* element) {
        return getStartOfHouse(DataStructures::House::BOX, element);
    }

    DataStructures::Element* Rule::getStartOfHouse(const DataStructures::House house,
                                                   DataStructures::Element* element) {
        auto returnVal = element;
        
        while (returnVal->getPrevious(house) != NULL) {
            returnVal = returnVal->getPrevious(house);
        }
        
        return returnVal;
    }

    void Rule::setValue(DataStructures::Element* element,
                        const uint64_t value) {
        element->setValue(value);

        for (auto peer : getPeers(element)) {
            peer->removeCandidate(value);
        }
    }

    const std::string& Rule::getName() const {
        return name;
    }

}