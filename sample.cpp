#include <iostream>
#include <string>

int main() {
    // Prompt the user for their name
    std::cout << "Enter your name: ";
    std::string name;
    std::getline(std::cin, name);

    // Print the name as a pattern
    int len = name.length();
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::cout << name[j];
        }
        std::cout << std::endl;
    }

    return 0;
}
