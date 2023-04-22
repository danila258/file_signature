#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <string>
#include <stdexcept>
#include <algorithm>
#include <fstream>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/crc.hpp>


constexpr unsigned long defaultBlockSize = 1024ul * 1024ul;  // 1MB by default


class FileSignature
{
public:
    FileSignature(int argc, char* argv[]);
    FileSignature(std::string_view input, std::string_view output, unsigned long long blockSize = defaultBlockSize);

    void generate();

private:
    std::string _inputFilePath;
    std::string _outputFilePath;
    unsigned long long _blockSize = defaultBlockSize;  // 1MB by default
};


#endif //FILESIGNATURE_H
