#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
 
int main()
{
  char *buffer;
  struct stat s;
 
  int fd = open("./memmap_read_entire_file.cpp", O_RDONLY);
  if (fd < 0 ) return EXIT_FAILURE;
  fstat(fd, &s);
  /* PROT_READ disallows writing to buffer: will segv */
  buffer = (char*)mmap(0, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
 
  if ( buffer != (void*)-1 )
  {
    /* do something */
    fwrite(buffer, s.st_size, 1, stdout);
    munmap(buffer, s.st_size);
  }
 
  close(fd);
  return EXIT_SUCCESS;
}