#include <bits/stdc++.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unordered_map>

using namespace std;

unordered_map<char, size_t> getFrequencies(const string &input) {
  unordered_map<char, size_t> freqs;
  for (auto c : input) {
    freqs[c]++;
  }
  return freqs;
}

string getFileContents(const string &filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    throw runtime_error("Unable to open file.");
  }
  ostringstream oss;
  oss << file.rdbuf();
  return oss.str();
}

const size_t CHUNK_SIZE = 4096;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Error: No command provided." << endl;
    return 1;
  }
  string filename = argv[argc - 1];

  int fd = open(filename.c_str(), O_RDONLY);
  if (fd == -1) {
    perror("Error opening file");
    return 1;
  }

  struct stat sb;
  if (fstat(fd, &sb) == -1) {
    perror("Error getting file info");
    close(fd);
    return 1;
  }

  size_t file_size = sb.st_size;
  size_t offset = 0;

  while (offset < file_size) {
    size_t chunk_size = min(CHUNK_SIZE, file_size - offset);
    char *data = static_cast<char *>(
        mmap(NULL, chunk_size, PROT_READ, MAP_SHARED, fd, offset));
    if (data == MAP_FAILED) {
      perror("Error mapping");
      close(fd);
      return 1;
    }

    for (size_t i = 0; i < chunk_size; i++) {
      cout << data[i];
    }

    if (munmap(data, chunk_size) == -1) {
      perror("Error unmapping file");
    }
    offset += chunk_size;
  }

  close(fd);
  return 0;

  // auto freqs = getFrequencies(getFileContents(filename));
  //
  // cout << freqs['X'] << endl;

  return 0;
}
