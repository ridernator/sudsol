#pragma once

#include <set>

#include "Grid.hpp"


namespace Rules {

    class Rule {
        public:
            Rule(const std::string& name,
                 DataStructures::Grid* grid);

            virtual bool solve() = 0;

            static void setValue(DataStructures::Element* element,
                                 const uint64_t value);

            static std::set<DataStructures::Element*> getPeers(DataStructures::Element* element);

            static DataStructures::Element* getStartOfRow(DataStructures::Element* element);

            static DataStructures::Element* getStartOfColumn(DataStructures::Element* element);

            static DataStructures::Element* getStartOfBox(DataStructures::Element* element);

            static DataStructures::Element* getStartOfHouse(const DataStructures::House house,
                                                            DataStructures::Element* element);

            const std::string& getName() const;

        protected:
            DataStructures::Grid* grid;

        private:
            const std::string name;
    };
}