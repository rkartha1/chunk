#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "chunk_methods.h"

void chunk_file_by_lines(int input_fd, int line_count, char* prefix, char* suffix) {
    char buffer[4096];
    int output_fd = 0;
    int line = 0;
    int count;
    int return_num_bytes_read = 0;
    int return_num_bytes_written = 0;
    char output_name[256];
    int suffix_one = 0;
    if (suffix[0] == '0') {
        suffix_one = 48;
        count = 48;
    } else if (suffix[0] == 'a') {
        count = 97;
        suffix_one = 97;
    }

    /* read returns characters read, then this value is checked to
     *  see if it is greater than 0, if not breaks out of the loop  */
    while ((return_num_bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < return_num_bytes_read; i++) {
            // starts a new file after line count has been exceeded
            if (line >= line_count) {
                close(output_fd);
                line = 0;
                count++;
            }
            // creates the new file
            if (line == 0) {
                sprintf(output_name, "%s%c%c", prefix, (char)suffix_one, (char)count);
                output_fd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                // if created file cannot open, then it will exit automatically
                if (output_fd == ERROR) {
                    perror("open");
                    exit(0);
                }
                // deals with suffix of the new file
                if (count == 57) {
                    suffix_one++;
                    count = 48;
                } else if (count == 122) {
                    suffix_one++;
                    count = 97;
                }

            }
            if ((return_num_bytes_written = (write(output_fd, &buffer[i], 1))) == ERROR) {
                perror("write");
                exit(0);
            }
            // if buffer finds a \n character, then number of lines for the created file will go up
            if (buffer[i] == '\n') {
                line++;
            }
        }
    }
    close(output_fd);
    close(input_fd);
}



void chunk_file_by_words(int input_fd, int word_count, char* prefix, char* suffix) {
    int return_num_bytes_read = 0;
    int return_num_bytes_written = 0;
    char buffer[4096];
    int output_fd = 0;
    char output_name[256];
    int count = 0;
    int word = 0;
    int suffix_one;
    if (suffix[0] == '0') {
        suffix_one = 48;
        count = 48;
    } else if (suffix[0] == 'a') {
        count = 97;
        suffix_one = 97;
    }

    /* read returns characters read, then this value is checked to
     *  see if it is greater than 0, if not breaks out of the loop  */
    while ((return_num_bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
        for (int i = 0; i < return_num_bytes_read; i++) {
            // if word_count is reached, then new file has started
            if (word - 1 >= word_count) {
                close(output_fd);
                word = 0;
                count++;
            }
            // creating the new file due to the amount of words needed
            if (word == 0) {
                sprintf(output_name, "%s%c%c", prefix, (char)suffix_one, (char)count);
                output_fd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                // if created file cannot open, then it will exit automatically
                if (output_fd == ERROR) {
                    perror("open");
                    exit(0);
                }

                // deals with suffix of new file
                if (count == 57) {
                    suffix_one++;
                    count = 48;
                } else if (count == 122) {
                    suffix_one++;
                    count = 97;
                }

            }
            if ((return_num_bytes_written = (write(output_fd, &buffer[i], 1))) == ERROR) {
                perror("write");
                exit(0);
            }
            /* if buffer finds a \n, space, \t, or if it is the first word or part of the loop,
               then number of words for the created file will go up */
            if (buffer[i] == ' ' ||  buffer[i] == '\n' || buffer[i] == '\t'
            || i == 0 || word == 0) {
                word++;
            }
        }
    }
    close(output_fd);
    close(input_fd);
}


void chunk_file_by_characters(int input_fd, int character_count, char* prefix, char* suffix) {
    int return_num_bytes_read;
    int return_num_bytes_written;
    char buffer[1024];
    int output_fd;
    char output_name[256];
    int count = 0;
    int character = 0;
    int suffix_one;
    if (suffix[0] == '0') {
        suffix_one = 48;
        count = 48;
    } else if (suffix[0] == 'a') {
        count = 97;
        suffix_one = 97;
    }

    /* read returns characters read, then this value is checked to
     *  see if it is greater than 0, if not breaks out of the loop  */
     while ((return_num_bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0) {
         for (int i = 0; i < return_num_bytes_read; i++) {
             // starts a new file when character number is reached
             if (character >= character_count) {
                 close(output_fd);
                 character = 0;
                 count++;
             }
             // creates the new file
             if (character == 0) {
                 sprintf(output_name, "%s%c%c", prefix, (char)suffix_one, (char)count);
                 output_fd = open(output_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                 if (output_fd < 0) {
                     perror("open");
                     exit(0);
                 }
                 // deals with suffix of the new file
                 if (count == 57) {
                     suffix_one++;
                     count = 48;
                 } else if (count == 122) {
                     suffix_one++;
                     count = 97;
                 }

             }
             if ((return_num_bytes_written = (write(output_fd, &buffer[i], 1))) == ERROR) {
                 perror("write");
                 exit(0);
             }
             character++;
         }
     }
     close(output_fd);
     close(input_fd);
}
