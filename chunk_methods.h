#ifndef CHUNK_METHODS_H
#define CHUNK_METHODS_H

#define ERROR_OPEN_R    2

#define ERROR       -1

extern void chunk_file_by_lines(int input_fd, int line_count, char* prefix, char* suffix);
extern void chunk_file_by_words(int input_fd, int word_count, char* prefix, char* suffix);
extern void chunk_file_by_characters(int input_fd, int character_count, char* prefix, char* suffix);

#endif
