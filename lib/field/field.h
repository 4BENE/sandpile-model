#include <vector>
#include <iostream>
#include <cinttypes>
#include <set>
struct Node {
    uint64_t key = 0;
    Node* down = nullptr;
    Node* up = nullptr;
    Node* right = nullptr;
    Node* left = nullptr;
};
struct Parameters {
    uint16_t length = 0;
    uint16_t width = 0;
    std::string input_way;
    std::string output_way;
    uint16_t max_count_it = 0;
    uint16_t freq = 0;
};

struct Field {
    Node* head_up_left = nullptr;
    Node* head_up_right = nullptr;
    Node* head_down_left = nullptr;
    Node* head_down_right = nullptr;
    uint16_t width;
    uint16_t height;
    std::set<Node*> numbers;
    std::set<Node*> new_numbers;

    Field(std::vector<uint16_t>& a, const uint16_t& width, const uint16_t& height) : width(width), height(height) {
        Node* last;
        Node* last_i;
        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                Node* new_element = new Node;
                if (i == 0 && j == 0) {
                    new_element->key = a[width * i + j];
                    head_up_left = new_element;
                    last_i = new_element;
                } else {
                    if (i == 0) {
                        new_element->left = last;
                        new_element->left->right = new_element;
                        new_element->key = a[width * i + j];
                        head_up_right = new_element;
                    } else {
                        if (j != 0) {
                            new_element->left = last;
                            new_element->left->right = new_element;
                            new_element->up = new_element->left->up->right;
                            new_element->up->down = new_element;
                            new_element->key = a[width * i + j];
                        } else {
                            new_element->up = last_i;
                            new_element->up->down = new_element;
                            new_element->key = a[width * i + j];
                            last_i = new_element;
                        }
                    }
                }
                last = new_element;
                head_down_right = last;
            }
            head_down_left = last;
        }
    }

};

void fill(std::vector<uint16_t>& a, Parameters& parameters_field);

void increase_up(Field& field);

void increase_down(Field& field);

void increase_right(Field& field);

void increase_left(Field& field);

void scattering(Field& field, Parameters& parameters_field);