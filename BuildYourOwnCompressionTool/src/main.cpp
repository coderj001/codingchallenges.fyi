#include <cstddef>
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

using namespace std;

class FileReader {
private:
  const size_t BUFFER_SIZE = 4096;

  int fd;
  char *mapped_data;
  size_t file_size;

public:
  explicit FileReader(const char *filename) : fd(-1), mapped_data(nullptr) {
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
      throw runtime_error("Cannot open file.");
    }
  };

  ~FileReader() {
    if (mapped_data) {
      munmap(mapped_data, file_size);
    }
    if (fd != -1) {
      close(fd);
    }
  }

  void readContent();
  unordered_map<char, size_t> getFrequencies();
};

/**
 * Option 1: read() with a Buffer
 * This is implemented in the getFrequencies() method. It reads chunks of the
 * file into a buffer using the read() system call and processes the data
 * iteratively.
 *
 * NOTE: The read() system call copies data from kernel space to user space,
 * which can introduce overhead for large files.
 *
 * Less Efficient for Random Access, more complex and slower.
 * */
unordered_map<char, size_t> FileReader::getFrequencies() {
  unordered_map<char, size_t> freqs;
  char buffer[BUFFER_SIZE];
  ssize_t bytes_read;

  lseek(fd, 0, SEEK_SET);

  while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
    for (ssize_t i = 0; i < bytes_read; i++) {
      freqs[buffer[i]]++;
    }
    if (bytes_read == -1) {
      throw runtime_error("Error reading file");
    }
  }
  return freqs;
}

/**
 * This is implemented in the readContent() method. It maps the file directly
 * into the process's address space, allowing you to treat file contents as if
 * they were part of memory.
 *
 * Note: mmap() may complicate concurrent access by multiple processes.
 * */
void FileReader::readContent() {
  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    throw runtime_error("Error getting file info");
  }

  size_t file_size = sb.st_size;
  size_t offset = 0;

  while (offset < file_size) {
    size_t chunk_size = min(BUFFER_SIZE, file_size - offset);

    char *data = static_cast<char *>(
        mmap(NULL, chunk_size, PROT_READ, MAP_SHARED, fd, offset));

    if (data == MAP_FAILED) {
      throw runtime_error("Error mapping");
    }

    for (size_t i = 0; i < chunk_size; i++) {
      cout << data[i];
    }

    if (munmap(data, chunk_size) == -1) {
      throw runtime_error("Error unmapping");
    }

    offset += chunk_size;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No filename provided." << endl;
    return 1;
  }

  try {
    FileReader reader(argv[argc - 1]);
    auto freqs = reader.getFrequencies();
    cout << "K: " << freqs['K'] << endl;
    cout << "t: " << freqs['t'] << endl;
  } catch (const exception &e) {
    cout << "Error: " << e.what() << endl;
    return 1;
  }

  return 0;
}
