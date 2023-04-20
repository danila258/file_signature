#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <string>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/crc.hpp>


class FileSignature
{
public:
    FileSignature(int argc, char* argv[]);
    void calculate();

private:
    std::string _inputFilePath;
    std::string _outputFilePath;
    unsigned long long _blockByteCount = 1024ul * 1024ul;  // 1MB by default
};


#endif //FILESIGNATURE_H
