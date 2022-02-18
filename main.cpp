#include <iostream>
#include "UsefulTools.h"
#include "Test.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    UsefulTools myTools;
    std::cout << myTools.RandomInt(3, 4) << std::endl;

    return 0;
}
