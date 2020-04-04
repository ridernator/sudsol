#pragma once

#include <list>

#include "Grid.hpp"
#include "Rule.hpp"


class Solver {
public:
    Solver(DataStructures::Grid* grid);
    
    void addRule(Rules::Rule* rule);
    
    void removeRule(Rules::Rule* rule);
    
    bool solve();
    
private :
    std::list<Rules::Rule*> rules;
    
    DataStructures::Grid* grid;
};