#include "FileSignature.h"

FileSignature::FileSignature(int argc, char* argv[])
{
    // check number of arguments
    if (argc != 3 && argc != 4)
    {
        throw std::invalid_argument("invalid number of arguments");
    }

    _inputFilePath = argv[1];
    _outputFilePath = argv[2];

    // by default the block size is 1 MB
    if (argc == 4)
    {
        try
        {
            _blockSize = std::stoull(argv[3]);

            if (_blockSize == 0)
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

FileSignature::FileSignature(std::string_view input, std::string_view output, unsigned long long blockSize)
                             : _inputFilePath(input), _outputFilePath(output), _blockSize(blockSize)
{
    if (blockSize == 0)
    {
        throw std::invalid_argument("invalid block size argument");
    }
}

void FileSignature::generate()
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

    // generate file signature using pointer to the beginning of the block and the CRC-32 algorithm
    auto startBlock = inputFile.begin();
    boost::crc_32_type crc;

    for (; startBlock + _blockSize < inputFile.end(); startBlock += _blockSize)
    {
        crc.process_bytes(startBlock, _blockSize);
        outputFile << std::hex << crc.checksum() << std::endl;
        crc.reset();
    }

    // generate signature of the final block of the file
    crc.process_block(startBlock, inputFile.end());
    outputFile << std::hex << crc.checksum() << std::endl;
}