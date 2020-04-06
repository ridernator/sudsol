#pragma once

#include <vector>

#include "Grid.hpp"


namespace Rules {

    class Rule {
        public:
            Rule(const std::string& name,
                 DataStructures::Grid* grid);

            virtual bool solve() = 0;

            static void setValue(DataStructures::Element* element,
                                 const uint64_t value);

            static std::vector<DataStructures::Element*> getPeers(DataStructures::Element* element);

            static DataStructures::Element* getStartOfRow(DataStructures::Element* element);

            static DataStructures::Element* getStartOfColumn(DataStructures::Element* element);

            static DataStructures::Element* getStartOfBox(DataStructures::Element* element);

            static DataStructures::Element* getStartOfHouse(DataStructures::House house,
                                                            DataStructures::Element* element);
            
            static std::vector<DataStructures::Element*> getElementsWithCandidate(const DataStructures::House house,
                                                                                  DataStructures::Element* elementInHouse,
                                                                                  const uint64_t candidate);
            
            static std::vector<DataStructures::Element*> getElementsWithCandidates(const DataStructures::House house,
                                                                                   DataStructures::Element* elementInHouse,
                                                                                   const std::vector<uint64_t> candidates);
            
            static std::vector<DataStructures::Element*> getElementsWithOnlyCandidates(const DataStructures::House house,
                                                                                       DataStructures::Element* elementInHouse,
                                                                                       const std::vector<uint64_t> candidates);
            
            static bool areElementsInSameHouse(const std::vector<DataStructures::Element*> elements,
                                               const DataStructures::House house);
            
            static bool removeCandidatesFromHouse(const uint64_t candidate,
                                                  const DataStructures::House house,
                                                  DataStructures::Element* elementInHouse,
                                                  const std::vector<DataStructures::Element*> apartFrom);

            const std::string& getName() const;

        protected:
            DataStructures::Grid* grid;
            
            void setName(const std::string& name);

        private:
            std::string name;
            
            static std::vector<DataStructures::Element*> getElementsWithCandidates(const DataStructures::House house,
                                                                                   DataStructures::Element* elementInHouse,
                                                                                   const std::vector<uint64_t> candidates,
                                                                                   const bool only);
    };
}