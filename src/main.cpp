
// created by abhilekh on Oct 12, 2023

/*

   To Quickly move through the source program this lexer maintains 2 input
   buffers each 4096 bytes, Instead of going character by character we read in a
   block of characters. The source program is read into the buffer
   alternatively.

   Two pointers - begin and forward are used to keep track of the lexemes

*/
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

/*

TODO: 1. Maintain a symbol table for reserved keywords
      2. Maintain States for look ahead operation

*/

namespace fs = std::filesystem;

// TODO: to be implemented
namespace Lexer {
std::vector<char> buf1(4096);
std::vector<char> buf2(4096);
char *lexemeBegin;
char *forward;
const int buffer_size = 4096;

std::vector<char> &writeBuf(std::vector<char> &buf, std::FILE *f);
void readLexeme(std::FILE *f);
} // namespace Lexer

std::vector<char> &Lexer::writeBuf(std::vector<char> &buf, std::FILE *f) {
  size_t bytes_read = std::fread(&buf[0], sizeof(buf[0]), buf.size(), f);

  if (bytes_read < buffer_size) {
    buf[bytes_read] = EOF;
  }

  return buf;
}

// RISK: This function has high chances of causing a SegFault.
// TODO: Test the below function, works exactly how I want thoug..
void Lexer::readLexeme(std::FILE *f) {
  // alternatively write to each buffer first and then read
  auto buf = writeBuf(buf1, f);
  lexemeBegin = &buf[0];
  forward = lexemeBegin;
  // counting no of characters read, helps in determing the time to switch the
  // buffer.
  int count = 0;
  // flag to decide which buffer to write next
  bool bufOneTurn = false;
  while (*forward != EOF) {

    count++;
    forward++;
    if (count == buffer_size - 1) {
      // switch buffers..
      count = 0;
      if (bufOneTurn) {
        buf = writeBuf(buf1, f);
      } else {
        buf = writeBuf(buf2, f);
      }
      bufOneTurn = !bufOneTurn;
      // switch to next buffer..
      forward = &buf[0];
    }
    std::cout << *forward;
  }
}

// pass in a filename, outputs lexemes
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Error: Invalid Arguments\n";
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    // exit maybe
    return -1;
  }
  // I want std::strings.
  const char *file_path = argv[1];
  // check if the file exists or not.
  if (!fs::exists(file_path)) {
    std::cerr << "Error: " << file_path << " No such Files  exist";
    // exit maybe?
    return -1;
  }
  // why cannot the filename be a std::string
  std::FILE *f = std::fopen(file_path, "r");

  Lexer::readLexeme(f);

  return 0;
}
