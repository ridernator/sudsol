#include <iostream>
#include "Grid.hpp"
#include "Solver.hpp"
#include "NakedSingle.hpp"
#include "HiddenSingle.hpp"
#include "BoxLineReduction.hpp"
#include "IntersectionRemoval.hpp"
#include "NakedN.hpp"
#include "HiddenN.hpp"
#include "NFish.hpp"

int main(int, char** argv) {
    DataStructures::Grid grid(*(argv + 1));

    std::cout << std::endl<< "Initial grid :" << std::endl;
    grid.printGrid();
    std::cout << std::endl;
    
    Solver solver(&grid);
    Rules::NakedSingle nakedSingle(&grid);
    Rules::HiddenSingle hiddenSingle(&grid);
    Rules::BoxLineReduction boxLineReduction(&grid);
    Rules::IntersectionRemoval intersectionRemoval(&grid);
    Rules::NakedN naked2(&grid, 2);
    Rules::NakedN naked3(&grid, 3);
    Rules::NakedN naked4(&grid, 4);
    Rules::HiddenN hidden2(&grid, 2);
    Rules::HiddenN hidden3(&grid, 3);
    Rules::HiddenN hidden4(&grid, 4);
    Rules::NFish fish2(&grid, 2);
    Rules::NFish fish3(&grid, 3);
    Rules::NFish fish4(&grid, 4);
    
    solver.addRule(&nakedSingle);
    solver.addRule(&hiddenSingle);
    solver.addRule(&boxLineReduction);
    solver.addRule(&intersectionRemoval);
    solver.addRule(&naked2);
    solver.addRule(&naked3);
    solver.addRule(&naked4);
    solver.addRule(&hidden2);
    solver.addRule(&hidden3);
    solver.addRule(&hidden4);
    solver.addRule(&fish2);
    solver.addRule(&fish3);
    solver.addRule(&fish4);
    
    // Test configuration
//    solver.addRule(&fish4);
//    solver.addRule(&fish3);
//    solver.addRule(&fish2);
//    solver.addRule(&hidden4);
//    solver.addRule(&hidden3);
//    solver.addRule(&hidden2);
//    solver.addRule(&naked4);
//    solver.addRule(&naked3);
//    solver.addRule(&naked2);
//    solver.addRule(&intersectionRemoval);
//    solver.addRule(&boxLineReduction);
//    solver.addRule(&hiddenSingle);
//    solver.addRule(&nakedSingle);
    
    std::cout << "Running solver" << std::endl << std::endl;
    
    if (solver.solve()) {
        std::cout << "Solved :" << std::endl;
    } else {        
        std::cout << "Not solved :" << std::endl;
    }
    
    grid.printGrid();

    return 0;
}

