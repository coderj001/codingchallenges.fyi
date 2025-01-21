#include <fcntl.h>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/FileReader.h"

using namespace std;

FileReader::FileReader(const char *filename) : fd(-1) {
  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    throw runtime_error("Cannot open file.");
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    close(fd);
    throw runtime_error("Error getting file size.");
  }

  file_size = sb.st_size;
}

FileReader::~FileReader() {
  if (fd != -1) {
    close(fd);
  }
}

unordered_map<char, size_t> FileReader::getFrequencies() {
  unordered_map<char, size_t> freqs;

  while (offset < file_size) {
    size_t chunk_size = min(BUFFER_SIZE, file_size - offset);
    char *mapped_data = static_cast<char *>(
        mmap(NULL, chunk_size, PROT_READ, MAP_SHARED, fd, offset));

    if (mapped_data == MAP_FAILED) {
      throw runtime_error("Error mapping file.");
    }

    for (size_t i = 0; i < chunk_size; i++) {
      freqs[mapped_data[i]]++;
    }

    if (munmap(mapped_data, chunk_size) == -1) {
      throw runtime_error("Error unmapping file.");
    }

    offset += chunk_size;
  }
  return freqs;
}
