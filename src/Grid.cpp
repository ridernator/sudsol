#include <iostream>
#include <cmath>

#include "Grid.hpp"
#include "Rule.hpp"

namespace DataStructures {

    Grid::Grid(const uint32_t boxWidth,
               const uint32_t boxHeight,
               const std::string& values) {
        initialise(boxWidth, boxHeight);

        loadValues(values);
    }

    Grid::Grid(const std::string& values) {
        initialise(std::pow(values.length(), 0.25), std::pow(values.length(), 0.25));

        loadValues(values);
    }

    Grid::Grid(const uint32_t boxWidth,
               const uint32_t boxHeight) {
        initialise(boxWidth, boxHeight);
    }
    
    Grid::~Grid() {
        for (uint64_t row = 0; row < boxWidth * boxHeight; ++row) {
            for (uint64_t column = 0; column < boxWidth * boxHeight; ++column) {
                delete data[{row, column}];
            }
        }
    }

    void Grid::loadValues(const std::string& values) {
        Element* element;
        uint64_t stringIndex = 0;

        for (uint64_t rowIndex = 0; rowIndex < order; ++rowIndex) {
            element = getRow(rowIndex);

            while (element != NULL) {
                element->unsetValue();
                element = element->getNext(House::ROW);
            }
        }

        for (uint64_t rowIndex = 0; rowIndex < order; ++rowIndex) {
            element = getRow(rowIndex);

            while (element != NULL) {
                if (values[stringIndex] != '0') {
                    Rules::Rule::setValue(element, values[stringIndex] - '1');
                }

                ++stringIndex;
                element = element->getNext(House::ROW);
            }
        }
    }

    void Grid::initialise(const uint32_t width,
                          const uint32_t height) {
        this->boxWidth = width;
        this->boxHeight = height;
        this->order = width * height;
        
        for (uint64_t row = 0; row < order; ++row) {
            for (uint64_t column = 0; column < order; ++column) {
                data[{row, column}] = new Element(order);
            }
        }

        for (uint64_t row = 0; row < order; ++row) {
            for (uint64_t column = 0; column < order; ++column) {
                if (column != order - 1) {
                    data[{row, column}]->setNeighbour(data[{row, column + 1}], Direction::NEXT, House::ROW);
                    data[{row, column + 1}]->setNeighbour(data[{row, column}], Direction::PREVIOUS, House::ROW);
                }
                
                if (row != order - 1) {
                    data[{row, column}]->setNeighbour(data[{row + 1, column}], Direction::NEXT, House::COLUMN);
                    data[{row + 1, column}]->setNeighbour(data[{row, column}], Direction::PREVIOUS, House::COLUMN);
                }

                if (row % boxHeight == boxHeight - 1) {
                    if ((column % boxWidth) != boxWidth - 1) {
                        data[{row, column}]->setNeighbour(data[{boxHeight * (row / boxHeight), column + 1}], Direction::NEXT, House::BOX);
                        data[{boxHeight * (row / boxHeight), column + 1}]->setNeighbour(data[{row, column}], Direction::PREVIOUS, House::BOX);
                    }
                } else {
                    data[{row, column}]->setNeighbour(data[{row + 1, column}], Direction::NEXT, House::BOX);
                    data[{row + 1, column}]->setNeighbour(data[{row, column}], Direction::PREVIOUS, House::BOX);
                }
            }
        }
        
        for (uint64_t index = 0; index < order; ++index) {
            houses[House::ROW].push_back(getRow(index));
            houses[House::COLUMN].push_back(getColumn(index));
            houses[House::BOX].push_back(getBox(index));
        }
    }

    Element* Grid::getRow(const uint64_t index) {

        return getHouse(House::ROW, index);
    }

    Element* Grid::getColumn(const uint64_t index) {

        return getHouse(House::COLUMN, index);
    }

    Element* Grid::getBox(const uint64_t index) {

        return getHouse(House::BOX, index);
    }

    Element* Grid::getHouse(const House house,
                            const uint64_t index) {
        Element* returnVal;

        switch (house) {
            case House::ROW:
            {
                returnVal = data[{index, 0}];

                break;
            }

            case House::COLUMN:
            {
                returnVal = data[{0, index}];

                break;
            }

            case House::BOX:
            {
                returnVal = data[{boxHeight * (index / boxHeight), boxWidth * (index % boxWidth)}];

                break;
            }
        }

        return returnVal;
    }
    
    std::list<Element*> Grid::getRows() {
        return getHouses(House::ROW);
    }

    std::list<Element*> Grid::getColumns() {
        return getHouses(House::COLUMN);
    }

    std::list<Element*> Grid::getBoxes() {
        return getHouses(House::BOX);
    }

    std::list<Element*> Grid::getHouses(const House house) {
        return houses[house];
    }
    
    bool Grid::isSolved() {
        for (uint64_t row = 0; row < order; ++row) {
            for (uint64_t column = 0; column < order; ++column) {
                if (!data[{row, column}]->isValueSet()) {
                    return false;
                }
            }
        }
        
        return true;
    }

    void Grid::printGridForForum() {
        for (uint64_t row = 0; row < order; ++row) {
            for (uint64_t column = 0; column < order; ++column) {
                if (data[{row, column}]->isValueSet()) {
                    std::cout << (1 + data[{row, column}]->getValue());
                } else {
                    std::cout << '0';
                }
            }
        }

        std::cout << std::endl;
    }

    void Grid::printGrid() {
        for (uint64_t row = 0; row < order; ++row) {
            for (uint64_t column = 0; column < order; ++column) {
                if (data[{row, column}]->isValueSet()) {
                    std::cout << (1 + data[{row, column}]->getValue());
                } else {
                    std::cout << '[';
                    
                    for (uint64_t candidate : data[{row, column}]->getCandidates()) {
                        std::cout << (1 + candidate);
                    }
                    std::cout << ']';
                }
            }

            std::cout << std::endl;
        }
    }
    
    uint64_t Grid::getOrder() const {
        return order;
    }

}