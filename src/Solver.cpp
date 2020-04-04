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
            std::cout << "Running rule \"" << rule->getName() << '\"' << std::endl;
            if (rule->solve()) {
                //grid->printGrid();
                didSomething = true;
                
                break;
            }
        }

        if (!didSomething) {
            break;
        }
    }

    return grid->isSolved();
}

