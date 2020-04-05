#include "NDLoop.hpp"

#include <algorithm>
#include <iostream>
#include <set>

namespace DataStructures {
    NDLoop::NDLoop(uint64_t dimensions, 
                   uint64_t max) : dimensions(dimensions), 
                                   max(max) {
    }

    NDLoop::Iterator NDLoop::begin() {
        std::vector<uint64_t> set;

        for (uint64_t dimension = 0; dimension < dimensions; ++dimension) {
            set.push_back(dimension);
        }

        return Iterator(set, max);
    }

    NDLoop::Iterator NDLoop::end() {
        std::vector<uint64_t> set;

        return Iterator(set, max);
    }

    NDLoop::Iterator::Iterator(std::vector<uint64_t> value, 
                                uint64_t max) : set(value),
                                                max(max) {
    }

    std::vector<uint64_t> NDLoop::Iterator::operator*() const {
        return set;
    }

    bool NDLoop::Iterator::operator==(const Iterator& other) const {
        return set == other.set;
    }

    bool NDLoop::Iterator::operator!=(const Iterator& other) const {
        return !(*this == other);
    }

    NDLoop::Iterator::Holder NDLoop::Iterator::operator++(int) {
        NDLoop::Iterator::Holder ret(set);
        ++*this;
        return ret;
    }

    NDLoop::Iterator& NDLoop::Iterator::operator++() {
        update(set);

        return *this;
    }

    void NDLoop::Iterator::update(std::vector<uint64_t>& values) {
        do {
            for (uint64_t index = 0; index <= values.size(); ++index) {
                if (index == values.size()) {
                    values.clear();
                } else if (++values[index] == max) {
                    values[index] = 0;
                } else {
                    break;
                }
            } 
        } while (!unique(values));
    }
    
    bool NDLoop::Iterator::unique(std::vector<uint64_t>& values) {
        bool returnVal = true;
        std::set<uint64_t> temp;
        
        for (auto value : values) {
            if (temp.find(value) != temp.end()) {
                returnVal = false;
                
                break;
            }
            
            temp.insert(value);
        }
        
        return returnVal;
    }

    NDLoop::Iterator::Holder::Holder(std::vector<uint64_t> heldItem) : heldItem(heldItem) {
    }

    std::vector<uint64_t> NDLoop::Iterator::Holder::operator*() {
        return heldItem;
    }
}