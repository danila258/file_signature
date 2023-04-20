#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <string>
#include <stdexcept>
#include <fstream>


class FileSignature
{
public:
    FileSignature(int argc, char* argv[]);
    void calculate();

private:
    std::string _inputFilePath;
    std::string _outputFilePath;
    unsigned long _blockSize = 1024ul;  // 1MB
};


#endif //FILESIGNATURE_H
