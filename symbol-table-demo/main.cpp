#include <iostream>
#include "TranslateLibrary.h"

std::string source = "{ int x; char y; { bool y; x; y; } x; y; }";

int main(int argc, char *argv[]) {

    std::cout << "---------------- Code ----------------" << std::endl
              << source << std::endl
              << "---------------- Code ----------------" << std::endl;

    // do translate
    Translate::Initialize(source);
    Translate::program();

    std::cout << std::endl << "End of compile" << std::endl;

    Translate::output_cache();

    return 0;
}