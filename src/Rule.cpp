#include <iostream>
#include <algorithm>

#include "Rule.hpp"

namespace Rules{
    Rule::Rule(const std::string& name,
               DataStructures::Grid* grid) : grid(grid),
                                             name(name) {
        
    }

    std::vector<DataStructures::Element*> Rule::getPeers(DataStructures::Element* element)  {
        std::vector<DataStructures::Element*> peers;
        DataStructures::Element* traveller;

        for (const auto& house : DataStructures::HOUSES) {
            for (const auto& direction : DataStructures::DIRECTIONS) {
                traveller = element->getNeighbour(direction, house);

                while (traveller != NULL) {
                    peers.push_back(traveller);

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
    
    std::vector<DataStructures::Element*> Rule::getElementsWithCandidate(const DataStructures::House house,
                                                                         DataStructures::Element* elementInHouse,
                                                                         const uint64_t candidate) {        
        std::vector<DataStructures::Element*> returnVal;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);
       
        while (traveller != NULL) {
            if (traveller->containsCandidate(candidate)) {
                returnVal.push_back(traveller);
            }
            
            traveller = traveller->getNext(house);
        }
        
        return returnVal;        
    }
    
    std::vector<DataStructures::Element*> Rule::getElementsWithCandidates(const DataStructures::House house,
                                                                          DataStructures::Element* elementInHouse,
                                                                          const std::vector<uint64_t> candidates) {  
        return getElementsWithCandidates(house, elementInHouse, candidates, false);
    }
            
    std::vector<DataStructures::Element*> Rule::getElementsWithOnlyCandidates(const DataStructures::House house,
                                                                              DataStructures::Element* elementInHouse,
                                                                              const std::vector<uint64_t> candidates) {
        return getElementsWithCandidates(house, elementInHouse, candidates, true);
    }
            
    std::vector<DataStructures::Element*> Rule::getElementsWithCandidates(const DataStructures::House house,
                                                                          DataStructures::Element* elementInHouse,
                                                                          const std::vector<uint64_t> candidates,
                                                                          const bool only) {
        bool valid;   
        std::vector<DataStructures::Element*> returnVal;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);
       
        while (traveller != NULL) {
            valid = true;
            
            for (auto candidate : candidates) {
                if (!traveller->containsCandidate(candidate)) {
                    valid = false;
                    
                    break;
                }
            }
            
            if (valid) {
                if (only) {
                    if (traveller->getCandidates().size() == candidates.size()) {
                        returnVal.push_back(traveller);
                    }
                } else {
                    returnVal.push_back(traveller);
                }
            }
            
            traveller = traveller->getNext(house);
        }
        
        return returnVal;
    }
    
    bool Rule::areElementsInSameHouse(const std::vector<DataStructures::Element*> elements,
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
                                         const std::vector<DataStructures::Element*> apartFrom) {
        bool returnVal = false;
        DataStructures::Element* traveller = getStartOfHouse(house, elementInHouse);
        
        while (traveller != NULL) {
            if (std::find(apartFrom.begin(), apartFrom.end(), traveller) == apartFrom.end()) {
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
    
    void Rule::setName(const std::string& name) {
        this->name = name;
    }

}