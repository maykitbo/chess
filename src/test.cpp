#include <iostream>

int main () {
    for (int i = 0; i < 8; i++) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}