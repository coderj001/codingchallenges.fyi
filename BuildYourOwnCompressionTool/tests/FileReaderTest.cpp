#include <gtest/gtest.h>

#include "../include/FileReader.h"

TEST(FileReaderTest, getFrequencies) {

  string input_filepath = "test.txt";

  FileReader reader(input_filepath.c_str());
  auto freqs = reader.getFrequencies();

  EXPECT_EQ(freqs['X'], 333);
  EXPECT_EQ(freqs['t'], 223000);
}
