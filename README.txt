The files for my codebase include:
├── chunk
├── chunk.c
├── chunk_methods
├── chunk_methods.c
├── chunk_methods.h
├── chunk_methods.o
├── chunk.o
├── Makefile
├── README.txt
├── z_answer.jok.txt
├── z_babbage-gutenberg330KB.txt
├── z_goggamal-input.txt
├── z_goggamal-output-byhand.txt
└── z_goggamal-RST-only.txt

In order to compile my program, you need to use the command ./chunk [options] -f filename.txt [-p prefix] [-s suffix] or ./chunk [options] [-p prefix] < filename.txt. [options]in square brackets indicates that the command recognizes both excluding [options], or including options. The options modifies the size of output of the files, as follows (instead of the default 1,000 lines) as it includes -l for line_count, -w for word_count, -c for character_count. You cannot have -l, -w, or -c altogether, it needs to be one of the 3 or none of them. The assumptions is that the user knows the options included with the command as well as knowing if they want to do a prefix or suffix when running the program.

The known limitations and errors is that the user cannot put a negative number for line count, word count, or character count, or else the program will print out a statement. In addition, the user cannot put less than 2 arguments or more than 9 arguments in the command line, or else the program will print out a statement.

