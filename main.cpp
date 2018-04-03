#include <iostream>
#include "test_fcns.h"

int main() {
    std::cout << "Test ctors: " << test_ctors() << std::endl;
    std::cout << "Test destruction: " << test_destruction() << std::endl;
    std::cout << "Test peek: " << test_peek() << std::endl;
    return 0;
}