#include <iostream>
#include "NDLoop.hpp"
#include "Grid.hpp"
#include "Solver.hpp"
#include "NakedSingle.hpp"
#include "HiddenSingle.hpp"

int main(int, char** argv) {
    DataStructures::Grid grid(*(argv + 1));

    grid.printGrid();
    
    Solver solver(&grid);
    Rules::NakedSingle nakedSingle(&grid);
    Rules::HiddenSingle hiddenSingle(&grid);
    
    solver.addRule(&nakedSingle);
    solver.addRule(&hiddenSingle);
    
    std::cout << "Solving" << std::endl;
    solver.solve();
    
    grid.printGrid();
    
//    for (auto a : DataStructures::NDArray(4, 9)) {
//        for (auto b : a) {
//            std::cerr << b << ", ";
//        }
//        
//        std::cerr << std::endl;
//    }

    return 0;
}

