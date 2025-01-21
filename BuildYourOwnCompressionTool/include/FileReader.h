#ifndef FILE_READER_H
#define FILE_READER_H

#include <cstddef>
#include <unordered_map>

using namespace std;

class FileReader {
private:
  const size_t BUFFER_SIZE = 4096;
  int fd;
  size_t file_size;
  size_t chunk_size;
  size_t offset = 0;

public:
  explicit FileReader(const char *filename);
  ~FileReader();
  unordered_map<char, size_t> getFrequencies();
};

#endif // FILE_READER_H
