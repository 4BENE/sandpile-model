#include "../visualization/visualization.h"
#include "field.h"
#include <iostream>
#include <algorithm>
#include <fstream>

void fill(std::vector<uint16_t>& a, Parameters& parameters_field) {
    std::ifstream input(parameters_field.input_way);
    freopen(parameters_field.input_way.c_str(), "r", stdin);
    int x, y, z;
    while (std::cin >> x >> y >> z) {
        a[parameters_field.width * x + y] = z;
    }
    input.close();
}

void increase_up(Field& field) {
    Node* last = nullptr;
    for (Node* i = field.head_up_left; i != nullptr; i = i->right) {
        Node* new_element = new Node;
        i->up = new_element;
        new_element->down = i;
        if (i != field.head_up_left) {
            new_element->left = last;
            new_element->left->right = new_element;
        } else {
            field.head_up_left = new_element;
        }
        last = new_element;
    }
    field.head_up_right = last;
}

void increase_left(Field& field) {
    Node* last = nullptr;
    for (Node* i = field.head_up_left; i != nullptr; i = i->down) {
        Node* new_element = new Node;
        i->left = new_element;
        new_element->right = i;
        if (i != field.head_up_left) {
            new_element->up = last;
            new_element->up->down = new_element;
        } else {
            field.head_up_left = new_element;
        }
        last = new_element;
    }
    field.head_down_left = last;
}

void increase_right(Field& field) {
    Node* last = nullptr;
    for (Node* i = field.head_up_right; i != nullptr; i = i->down) {
        Node* new_element = new Node;
        i->right = new_element;
        new_element->left = i;
        if (i != field.head_up_right) {
            new_element->up = last;
            new_element->up->down = new_element;
        } else {
            field.head_up_right = new_element;
        }
        last = new_element;
    }
    field.head_down_right = last;
}

void increase_down(Field& field) {
    Node* last = nullptr;
    for (Node* i = field.head_down_left; i != nullptr; i = i->right) {
        Node* new_element = new Node;
        i->down = new_element;
        new_element->up = i;
        if (i != field.head_down_left) {
            new_element->left = last;
            new_element->left->right = new_element;
        } else {
            field.head_down_left = new_element;
        }
        last = new_element;
    }
    field.head_down_right = last;
}


void scattering_side(Node* side ,Field& field) {
    side->key++;
    if (side->key >= 4) {
        field.new_numbers.insert(side);
    }
}

void scattering(Field& field, Parameters& parameters_field) {
    int iterations = 0;
    for (Node* i = field.head_up_left; i != nullptr; i = i->down) {
        for (Node* j = i; j != nullptr; j = j->right) {
            if (j->key >= 4) {
                field.numbers.insert(j);
            }
        }
    }

    while (!field.numbers.empty()) {
        for (auto x: field.numbers) {
            field.new_numbers.insert(x);

            if (x->down != nullptr) {
                scattering_side(x->down, field);
            } else {
                increase_down(field);
                x->down->key++;
            }

            if (x->up != nullptr) {
                scattering_side(x->up, field);
            } else {
                increase_up(field);
                x->up->key++;
            }

            if (x->right != nullptr) {
                scattering_side(x->right , field);
            } else {
                increase_right(field);
                x->right->key++;
            }

            if (x->left != nullptr) {
                scattering_side(x->left, field);
            } else {
                increase_left(field);
                x->left->key++;
            }

            x->key = x->key - 4;

            if (x->key < 4) {
                field.new_numbers.erase(x);
            }
        }
        iterations += 1;
        if (iterations % parameters_field.freq == 0) {
            int height_map = 0, width_map = 0;
            for (Node* i = field.head_up_left; i != nullptr; i = i->down) {
                height_map += 1;
                for (Node* j = i; j != nullptr; j = j->right) {
                    if (i == field.head_up_left) {
                        width_map++;
                    }
                }
            }
            int count_i = -1, count_j ;
            Image image(width_map, height_map);

            for (Node* p = field.head_up_left; p != nullptr; p = p->down) {
                count_i++;
                count_j = -1;
                for (Node* j = p; j != nullptr; j = j->right) {
                    count_j++;
                    if (j->key == 0) {
                        image.SetColor(Color(255, 255, 255), count_j, count_i);
                    }
                    if (j->key == 1) {
                        image.SetColor(Color(0, 255, 0), count_j, count_i);
                    }
                    if (j->key == 2) {
                        image.SetColor(Color(255, 0, 128), count_j, count_i);
                    }
                    if (j->key == 3) {
                        image.SetColor(Color(255, 215, 0), count_j, count_i);
                    }
                }
            }
            std::string name = parameters_field.output_way + "image" + std::to_string(iterations) + ".bmp";
            image.Export(name.c_str());
        }
        if (iterations >= parameters_field.max_count_it) {
            break;
        }
        field.numbers = field.new_numbers;
    }
}