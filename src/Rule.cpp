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

    DataStructures::Element* Rule::getStartOfHouse(DataStructures::House house,
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
    
    std::set<DataStructures::Element*> Rule::getElementsWithCandidate(const DataStructures::House house,
                                                                      DataStructures::Element* elementInHouse,
                                                                      const uint64_t candidate) {        
        std::set<DataStructures::Element*> returnVal;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);
       
        while (traveller != NULL) {
            if (traveller->containsCandidate(candidate)) {
                returnVal.insert(traveller);
            }
            
            traveller = traveller->getNext(house);
        }
        
        return returnVal;        
    }
    
    bool Rule::areElementsInSameHouse(const std::set<DataStructures::Element*> elements,
                                      const DataStructures::House house) {
        bool returnVal = true;
        
        if (elements.size() >= 2) {
            DataStructures::Element* first = getStartOfHouse(house, *(elements.begin()));
            
            for (DataStructures::Element* element : elements) {
                if (getStartOfHouse(house, element) != first) {
                    returnVal = false;
                    
                    break;
                }
            }
        }
        
        return returnVal;
    }
    
    bool Rule::removeCandidatesFromHouse(const uint64_t candidate,
                                         const DataStructures::House house,
                                         DataStructures::Element* elementInHouse,
                                         const std::set<DataStructures::Element*> apartFrom) {
        bool returnVal = false;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);
        
        while (traveller != NULL) {
            if (apartFrom.find(traveller) == apartFrom.end()) {
                if (traveller->removeCandidate(candidate)) {
                    returnVal = true;
                }
            }
            
            traveller = traveller->getNext(house);
        }
        
        return returnVal;
    }

    const std::string& Rule::getName() const {
        return name;
    }

}