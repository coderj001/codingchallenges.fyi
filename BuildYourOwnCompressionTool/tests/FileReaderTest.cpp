#include <gtest/gtest.h>

#include "../include/FileReader.h"

class FileReaderTest : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(FileReaderTest, GetFrequenciesTest) {

  string input_filepath = "test.txt";

  FileReader reader(input_filepath.c_str());
  auto freqs = reader.getFrequencies();

  EXPECT_EQ(freqs['X'], 333);
  EXPECT_EQ(freqs['t'], 223000);
}
