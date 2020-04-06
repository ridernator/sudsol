#include <iostream>

#include "Solver.hpp"

Solver::Solver(DataStructures::Grid* grid) : grid(grid) {

}

void Solver::addRule(Rules::Rule* rule) {
    rules.push_back(rule);
}

void Solver::removeRule(Rules::Rule* rule) {
    rules.remove(rule);
}

bool Solver::solve() {
    bool didSomething;

    while (!grid->isSolved()) {
        didSomething = false;
        
        for (auto rule : rules) {
            std::cout << "Running rule \"" << rule->getName() << "..." ;
            if (rule->solve()) {
                std::cout << " Changes made : " << std::endl;
                grid->printGrid();
                std::cout << std::endl;
                
                didSomething = true;
                
                break;
            } else {
                std::cout << " No change" << std::endl;
            }
        }

        if (!didSomething) {
            break;
        }
    }

    return grid->isSolved();
}

