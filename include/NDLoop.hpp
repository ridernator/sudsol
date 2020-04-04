#pragma once

#include <vector>
#include <cstdint>

namespace DataStructures {
    class NDLoop {
        private:
            class Iterator {
                private:
                    class Holder {
                        public:
                            Holder(std::vector<uint64_t> heldItem);

                            std::vector<uint64_t> operator*();

                        private:
                            std::vector<uint64_t> heldItem;
                    };

                    std::vector<uint64_t> set;

                    uint64_t max;

                public:
                    typedef std::vector<uint64_t> value_type;
                    
                    typedef std::ptrdiff_t difference_type;
                    
                    typedef std::vector<uint64_t>* pointer;
                    
                    typedef std::vector<uint64_t>& reference;
                    
                    typedef std::input_iterator_tag iterator_category;

                    explicit Iterator(std::vector<uint64_t> value, uint64_t max);

                    std::vector<uint64_t> operator*() const;

                    bool operator==(const Iterator& other) const;

                    bool operator!=(const Iterator& other) const;

                    Holder operator++(int);
                    
                    Iterator& operator++();

                    void update(std::vector<uint64_t>& values);
            };

        public:
            NDLoop(const uint64_t dimensions,
                    const uint64_t max);

            NDLoop::Iterator begin();

            NDLoop::Iterator end();

        private:
            const uint64_t dimensions;

            const uint64_t max;
    };
}