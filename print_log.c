
#include <stdio.h>
  FILE *testfile;
  testfile = fopen("/TEST_LOG", "a");
  fprintf(testfile, "point 1");
  fclose(testfile);

