#include "FileSignature.h"

FileSignature::FileSignature(int argc, char* argv[])
{
    if (argc != 3 && argc != 4)
    {
        throw std::invalid_argument("invalid number of arguments");
    }

    _inputFilePath = argv[1];
    _outputFilePath = argv[2];

    // by default the block byte count is 1024 * 1024 = 1 MB
    if (argc == 4)
    {
        try
        {
            _blockByteCount = std::stoull(argv[3]);

            if (_blockByteCount == 0)
            {
                throw std::invalid_argument("");
            }
        }
        catch (...)
        {
            throw std::invalid_argument("invalid block size argument");
        }
    }
}

void FileSignature::calculate()
{
    // create and open input file
    boost::iostreams::mapped_file_source inputFile;

    try
    {
        inputFile.open(_inputFilePath);
    }
    catch (...)
    {
        throw std::runtime_error("can't open input file");
    }

    // create and open output file
    std::ofstream outputFile;
    outputFile.open(_outputFilePath, std::ios_base::binary);

    if ( !outputFile.is_open() )
    {
        throw std::runtime_error("can't open output file");
    }

    // calculate file signature using two pointers to the beginning and end of the block and the CRC-16 algorithm
    auto startBlock = inputFile.begin();
    auto endBlock = startBlock + _blockByteCount;

    boost::crc_16_type crc;

    while (endBlock < inputFile.end())
    {
        crc.process_block(startBlock, endBlock);

        std::cout << crc.checksum() << std::endl;
        outputFile << crc.checksum() << std::endl;

        startBlock += _blockByteCount;
        endBlock += _blockByteCount;
        crc.reset();
    }

    // calculate signature of the final block of the file
    crc.process_block(startBlock, inputFile.end() - 1);
    std::cout << crc.checksum() << std::endl;
}
