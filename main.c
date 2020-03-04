#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  writeConstant(&chunk, 1.2, 123);
  // for (int i = 0; i < 260; i++) {
  //   writeConstant(&chunk, i, i);
  // }

  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "test chunk");
  freeChunk(&chunk);

  return 0;
}