#include "FileSignature.h"

#include <iostream>


int main(int argc, char* argv[])
{
    try
    {
        FileSignature fs(argc, argv);
        fs.generate();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}