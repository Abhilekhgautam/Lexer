
// created by abhilekh on Oct 12, 2023

/*

   To Quickly move through the source program this lexer maintains 2 input buffers each 4096 bytes,
   Instead of going character by character we read in a block of characters.
   The source program is read into the buffer alternatively.

   Two pointers - begin and forward are used to keep track of the lexemes

*/
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

/*

TODO: 1. Maintain a symbol table for reserved keywords
      2. Maintain States for look ahead operation

*/


namespace fs = std::filesystem;

// TODO: to be implemented
class InputBuffer{
  public:
    	  
};

// pass in a filename, outputs lexemes
int main(int argc, char* argv[]){
  if (argc < 2 ){
    std::cerr << "Error: Invalid Arguments\n";
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    // exit maybe
    return -1;
  }
  // I want std::strings.
  const char* file_path = argv[1];
  // check if the file exists or not.
  if(!fs::exists(file_path)){
     std::cerr << "Error: " << file_path << " No such Files  exist";
     // exit maybe?
     return -1;
  }
  // create a input file stream
  std::ifstream input_file(file_path);
  // why cannot the filename be a std::string
  std::FILE* f = std::fopen(file_path, "r");

  // no macros..
  const int buffer_size = 4096;

  // two buffer should be fine.
  std::vector<char> buf1(buffer_size);
  std::vector<char> buf2(buffer_size);

  // alternatively fills in the buffer 

  // TODO: maintain pointers to keep track of the lexemes.
  for(;;){
   size_t bytes_read = std::fread(&buf1[0], sizeof(buf1[0]), buf1.size(), f);
   if(bytes_read < buffer_size){ // what to do for equality??
     buf1[bytes_read - 1] = EOF;
     break;
   } else {
    size_t bytes_read = std::fread(&buf2[0], sizeof(buf2[0]), buf2.size(), f); 	   
    if(bytes_read < buffer_size){
      buf2[bytes_read - 1] = EOF;
      break;
    } 
   }
  }
}
