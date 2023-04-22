#include "gtest/gtest.h"
#include "FileSignature.h"

#include <vector>
#include <random>


constexpr auto testFilePath = "test.txt";
constexpr auto signatureFilePath = "signature.txt";
constexpr auto testsCount = 100;
constexpr auto numsMaxCount = 10000;
constexpr auto blockSizeMax = 1024;


// read ready signature from file line by line
std::vector<std::string> getReadySignature(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::string line;
    std::vector<std::string> signatureArr;

    if ( !file.is_open() )
    {
        throw std::runtime_error("can't open file");
    }

    while ( std::getline(file, line) )
    {
        signatureArr.emplace_back(line);
    }

    return signatureArr;
}

// convert number to hex string
std::string toHex(size_t num)
{
    std::stringstream stream;
    stream << std::hex << num;
    return stream.str();
}

// test using random file generation
TEST(Signature, Test1)
{
    // setting up random generator
    std::random_device seed;
    std::default_random_engine generator(seed());
    std::uniform_int_distribution distribution(0, INT_MAX);
    auto dice = std::bind(distribution, generator);

    for (size_t i = 0; i < testsCount; ++i)
    {
        std::string line;
        size_t blockSize = dice() % blockSizeMax;
        unsigned long numsCount = dice() % numsMaxCount;

        // generate random line
        for (size_t j = 0; j < numsCount; ++j)
        {
            line += std::to_string( dice() );
        }

        // white random line to file
        std::ofstream file(testFilePath);
        ASSERT_TRUE(file.is_open());
        file << line;
        file.close();

        // generate signature
        FileSignature signature(testFilePath, signatureFilePath, blockSize);
        signature.generate();

        // get signature from file
        std::vector<std::string> signatureFromFile = getReadySignature(signatureFilePath);

        boost::crc_32_type crc;
        size_t index = 0;
        char* p = line.data();

        // compare signatures from file and generated in loop
        for (; p + blockSize < line.data() + line.size(); p += blockSize)
        {
            crc.process_bytes(p, blockSize);
            ASSERT_EQ(toHex(crc.checksum()), signatureFromFile.at(index));

            crc.reset();
            ++index;
        }

        // compare last block
        crc.process_block(p, line.data() + line.size());
        ASSERT_EQ(toHex(crc.checksum()), signatureFromFile.at(index));
    }
}

// simple test
TEST(Signature, Test2)
{
    std::string line = "123456789";
    size_t blockSize = 9;

    std::ofstream file(testFilePath);
    ASSERT_TRUE(file.is_open());
    file << line;
    file.close();

    FileSignature signature(testFilePath, signatureFilePath, blockSize);
    signature.generate();

    // get signature from file
    std::vector<std::string> signatureFromFile = getReadySignature(signatureFilePath);

    boost::crc_32_type crc;

    // compare block
    crc.process_block(line.data(), line.data() + line.size());
    ASSERT_EQ(toHex(crc.checksum()), signatureFromFile.front());
}