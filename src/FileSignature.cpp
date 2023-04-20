#include "FileSignature.h"

FileSignature::FileSignature(int argc, char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        throw std::invalid_argument("invalid number of arguments");
    }

    _inputFilePath = argv[0];
    _outputFilePath = argv[1];

    if (argc == 3)
    {
        try
        {
            _blockSize = std::stoul(argv[2]);
        }
        catch (...)
        {
            throw std::invalid_argument("invalid block size argument");
        }
    }
}

void FileSignature::calculate()
{

}
