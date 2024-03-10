#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "chunk_methods.c"

int main ( int argc, char * argv[] )
{

    if( (argc < 2) || (argc > 9))
    {
        printf("Usage: %s [options] -f filename.txt [-p prefix] [-s suffix]\n",argv[0]);
        printf("Usage: %s [options] [-p prefix] < filename.txt\n",argv[0]);
        return ERROR;
    }

    int input_fd = 0;
    int opt = 0;
    int line_count = 0;
    int word_count = 0;
    int character_count = 0;
    char* prefix = "x";
    char* suffix = "aa";
    char* file_name;

    while ((opt = getopt(argc, argv, "l:w:c:f:p:s:")) != -1) {
        switch(opt) {
        case 'l':
            line_count = atoi(optarg);
            break;
        case 'w':
            word_count = atoi(optarg);
            line_count = 0;
            character_count = 0;
            break;
        case 'c':
            character_count = atoi(optarg);
            line_count = 0;
            word_count = 0;
            break;
        case 'f':
            file_name = optarg;
            break;
        case 'p':
            prefix = optarg;
            break;
        case 's':
            suffix = optarg;
            break;
        }
    }



    if (character_count == 0 && word_count == 0 && line_count == 0) {
        line_count = 1000;
    }

    if (line_count < 0 || word_count < 0 || character_count < 0) {
        printf("Please input a new word count, line count, or character count above 0.\n");
        return ERROR;
    }

    if (open(file_name, O_RDONLY ) == -1) {
        input_fd = STDIN_FILENO;
    } else {
        input_fd = open(file_name, O_RDONLY );
    }
    if( input_fd ==  ERROR )
    {
        /* perror prints a system error message along the argument */
        perror( "open" ) ;
        return ERROR_OPEN_R;
    }

    if (line_count > 0) {
        chunk_file_by_lines(input_fd, line_count, prefix, suffix);
    } else if (word_count > 0) {
        chunk_file_by_words(input_fd, word_count, prefix, suffix);
    } else if (character_count > 0) {
        chunk_file_by_characters(input_fd, character_count, prefix, suffix);
    }

    close(input_fd);


}
