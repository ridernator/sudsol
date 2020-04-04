#pragma once

#include <stdint.h>
#include <map>
#include <list>

#include "Element.hpp"


namespace DataStructures {

    class Grid {
    public:
        Grid(const uint32_t boxWidth,
                const uint32_t boxHeight);
        
        Grid(const uint32_t boxWidth,
                const uint32_t boxHeight,
                const std::string& values);
        
        Grid(const std::string& values);
        
        ~Grid();

        Element* getRow(const uint64_t index);

        Element* getColumn(const uint64_t index);

        Element* getBox(const uint64_t index);

        Element* getHouse(const House house,
                const uint64_t index);

        std::list<Element*> getRows();

        std::list<Element*> getColumns();

        std::list<Element*> getBoxes();

        std::list<Element*> getHouses(const House house);
        
        void loadValues(const std::string& values);
        
        bool isSolved();
        
        void printGridForForum();
        
        void printGrid();
        
        uint64_t getOrder() const;

    private:
        void initialise(const uint32_t width,
                const uint32_t height);
        
        std::map<std::pair<uint64_t, uint64_t>, Element*> data;
        
        std::map<House, std::list<Element*>> houses;
        
        uint32_t boxWidth;
        
        uint32_t boxHeight;
        
        uint64_t order;
    };
}