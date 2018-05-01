#include <stdio.h>
#include "makeSeuss.hpp"

int main(int argc, char** argv) {
    makeSeuss seuss("DrSeuss.txt", "Output.txt");
    seuss.readFile();
    seuss.writeFile();

    return (EXIT_SUCCESS);
}

