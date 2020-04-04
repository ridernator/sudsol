#include <iostream>
#include "Grid.hpp"
#include "Solver.hpp"
#include "NakedSingle.hpp"
#include "HiddenSingle.hpp"
#include "BoxLineReduction.hpp"

int main(int, char** argv) {
    DataStructures::Grid grid(*(argv + 1));

    std::cout << std::endl<< "Initial grid :" << std::endl;
    grid.printGrid();
    std::cout << std::endl;
    
    Solver solver(&grid);
    Rules::NakedSingle nakedSingle(&grid);
    Rules::HiddenSingle hiddenSingle(&grid);
    Rules::BoxLineReduction boxLineReduction(&grid);
    
    solver.addRule(&nakedSingle);
    solver.addRule(&hiddenSingle);
    solver.addRule(&boxLineReduction);
    
    // Test configuration
    //solver.addRule(&boxLineReduction);
    //solver.addRule(&hiddenSingle);
    //solver.addRule(&nakedSingle);
    
    std::cout << "Running solver" << std::endl << std::endl;
    
    if (solver.solve()) {
        std::cout << "Solved :" << std::endl;
    } else {        
        std::cout << "Not solved :" << std::endl;
    }
    
    grid.printGrid();

    return 0;
}

