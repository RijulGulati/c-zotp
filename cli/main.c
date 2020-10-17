#include "cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

const char help_message[] = "\nzotp (cli) - https://gitlab.com/grijul/zotp\n\n"
                            "Usage: zotp <file_type> file\n"

                            "File Types:\n"
                            " --encrypted-file          Use Encrypted file.\n"
                            " --decrypted-file          Use Decrypted file.\n\n"
                            "Misc. Options\n"
                            " --help                    Show help\n"
                            " --version                 Show version\n\n";

int main(int argc, char *argv[]) {

  int is_file_encrypted = 0;
  struct stat buffer;

  if (argc == 1) {
    fprintf(stderr, "\nError: No file specified. Use --help for options\n\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], "--help") == 0) {
    printf(help_message);
    exit(EXIT_SUCCESS);
  }

  if (strcmp(argv[1], "--encrypted-file") == 0) {
    is_file_encrypted = 1;
  } else if (strcmp(argv[1], "--decrypted-file") == 0) {
    is_file_encrypted = 0;
  } else {
    fprintf(stderr, "Invalid argument: %s\n\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (stat(argv[2], &buffer) == -1) {
    fprintf(stderr, "\nError: Invalid input file\n");
    exit(EXIT_FAILURE);
  }

  zotp_cli(is_file_encrypted, argv[2]);

  return 0;
}
