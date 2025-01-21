#include <gtest/gtest.h>
#include "../include/FileReader.h"

class FileReaderTest : public ::testing::Test {
protected:
  void SetUp() override {
    test_file = "test_file.txt";
    FILE *file = fopen(test_file, "w");
    fprintf(file, "Hello, World!");
    fclose(file);
  }

  void TearDown() override {
    remove(test_file);
  }

  const char *test_file;
};

TEST_F(FileReaderTest, GetFrequenciesTest) {
  FileReader reader(test_file);
  auto freqs = reader.getFrequencies();

  EXPECT_EQ(freqs['H'], 1);
  EXPECT_EQ(freqs['e'], 1);
  EXPECT_EQ(freqs['l'], 3);
  EXPECT_EQ(freqs['!'], 1);
}

TEST(FileReaderErrorTest, InvalidFileTest) {
  EXPECT_THROW(FileReader("nonexistent.txt"), std::runtime_error);
}

