#include <iostream>

#include "object_processor.h"
#include "request_handler.h"

void PrintUsage(std::ostream& output = std::cerr) {
    output << "The run argument must be the input file name and the output file name\n"s;
}

void RunProgram(const std::string& input_file_name, const std::string& output_file_name, object_processor::ObjectProcessor& object_processor) {
    std::ifstream input_file(input_file_name, std::ios::in);
    if(!input_file.good()) {
        input_file.close();
        throw std::runtime_error("Can not open file "s + input_file_name);
    }

    object_processor.ReadFromFile(input_file);

    input_file.close();

    request_handler::RequestHandler request_handler(object_processor);

    while(true) {

        std::cout << "Выберите действие "s << std::endl;

        std::cout << "1. Сортировка по имени"s << std::endl;
        std::cout << "2. Сортировка по типу"s << std::endl;
        std::cout << "3. Сортировка по расстоянию"s << std::endl;
        std::cout << "4. Сортировка по времени"s << std::endl;
        std::cout << "Для выхода нажмите любую другую клавишу"s << std::endl;

        int choice;
        std::cin >> choice;

        std::ofstream output_file(output_file_name, std::ios::out);

        if(!output_file.good()) {
            input_file.close();
            throw std::runtime_error("Can not open file "s + output_file_name);
        }

        std::cout << '\n';

        switch (choice) {
            case 1:
                request_handler.OutputSortedByNameData(output_file);
                std::cout << "Сортировка по имени завершена\n\n"s;
                break;
            case 2:
                request_handler.OutputSortedByTypeData(output_file);
                std::cout << "Сортировка по типу завершена\n\n"s;
                break;
            case 3:
                request_handler.OutputSortedByDistanceData(output_file);
                std::cout << "Сортировка по расстоянию завершена\n\n"s;
                break;
            case 4:
                request_handler.OutputSortedByTimeData(output_file);
                std::cout << "Сортировка по времени завершена\n\n"s;
                break;
            default:
                output_file.close();
                std::cout << "Выход из программы\n"s;
                return;
        }
        output_file.close();
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    if(argc != 3) {
        PrintUsage();
        return 1;
    }
    object_processor::ObjectProcessor object_processor;

    RunProgram(argv[1], argv[2], object_processor);

    return 0;
}