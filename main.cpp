#include <iostream>

#include "object_processor.h"


void PrintUsage(std::ostream& output = std::cerr) {
    output << "The run argument must be the file name\n";
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        PrintUsage();
        return 1;
    }
    object_processor::ObjectProcessor object_processor;
    object_processor.ReadFromFile(argv[1]);



    std::cout << std::endl;
    return 0;
}