#include "lib/field/field.h"
#include <iostream>
#include <vector>
#include "lib/visualization/visualization.h"
#include <cstring>

int main(int argc, char** argv) {
    Parameters parameters_field;
    int i = 1;
    while (i <= argc - 1) {
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--length") == 0) {
            parameters_field.length = std::stoi(argv[i + 1]);
            i += 2;
        } else {
            if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) {
                parameters_field.width = std::stoi(argv[i + 1]);
                i += 2;
            } else {
                if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
                    parameters_field.input_way = argv[i + 1];
                    i += 2;
                } else {
                    if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                        parameters_field.output_way = argv[i + 1];
                        i += 2;
                    } else {
                        if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--max-iter") == 0) {
                            parameters_field.max_count_it = std::stoi(argv[i + 1]);
                            i += 2;
                        } else {
                            if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--freq") == 0) {
                                parameters_field.freq = std::stoi(argv[i + 1]);
                                i += 2;
                            }
                        }
                    }
                }
            }
        }
    }
    std::vector<uint16_t> a(parameters_field.width * parameters_field.length);
    fill(a, parameters_field);
    Field field(a, parameters_field.width, parameters_field.length);
    scattering(field, parameters_field);
    return 0;
}
