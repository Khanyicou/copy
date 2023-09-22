#include "my_shell.h"

/**
 * validate_input - Validates the input buffer.
 * @buf: Buffer to validate.
 * @fd: File descriptor.
 *
 * Return: 0 for success, 2 for syntax errors, or negative numbers for errors.
 */
int validate_input(char **buf, int fd) {
    char *newbuf, *bufgl, *bufptr = *buf;
    ssize_t lenr;
    size_t lenbuf;
    int start = 1;
    int complete = 0;

    linecount(1);
    if (*bufptr == 0)
        return 0;

    while (*bufptr) {
        while ((*bufptr == ' ' || *bufptr == '\n') && !(complete & 3))
            bufptr++;

        if (*bufptr == 0)
            break;

        if (start) {
            if (*bufptr == ';' && *(bufptr + 1) == ';') {
                free(*buf);
                print_error(": Syntax error \";;\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }

            if (*bufptr == ';') {
                free(*buf);
                print_error(": Syntax error \";\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }

            if (*bufptr == '&' && *(bufptr + 1) == '&') {
                free(*buf);
                print_error(": Syntax error \"&&\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }

            if (*bufptr == '&') {
                free(*buf);
                print_error(": Syntax error \"&\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }

            if (*bufptr == '|' && *(bufptr + 1) == '|') {
                free(*buf);
                print_error(": Syntax error \"||\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }

            if (*bufptr == '|') {
                free(*buf);
                print_error(": Syntax error \"|\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }

            start = 0;
        }

        if (bufptr[0] == '\n' && bufptr[1] == 0)
            break;

        if (*bufptr == '#' && !(complete & 3) && (bufptr == *buf || *(bufptr - 1) == ' ')) {
            *bufptr = 0;
            break;
        }

        complete &= ~4;

        if (*bufptr == '"' && !(complete & 3)) {
            complete |= 2;
            bufptr++;
            continue;
        }

        if (*bufptr == '"' && complete & 2)
            complete &= ~2;

        if (*bufptr == '\'' && !(complete & 3)) {
            complete |= 1;
            bufptr++;
            continue;
        }

        if (*bufptr == '\'' && complete & 1)
            complete &= ~1;

        if (bufptr[0] == '&' && !(complete & 3)) {
            if (bufptr[1] == '&') {
                complete |= 4;
                start = 1;
                bufptr++;
            } else if (bufptr[1] == '|') {
                free(*buf);
                print_error(": Syntax error \"|\" unexpected\n");
                setsvar("0", "2");
                return 2;
            } else if (bufptr[1] == ';') {
                free(*buf);
                print_error(": Syntax error \";\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }
        }

        if ((bufptr[0] == '|') && !(complete & 3)) {
            if (bufptr[1] == '|') {
                complete |= 4;
                start = 1;
                bufptr++;
            } else if (bufptr[1] == ';') {
                free(*buf);
                print_error(": Syntax error \";\" unexpected\n");
                setsvar("0", "2");
                return 2;
            } else if (bufptr[1] == '&') {
                free(*buf);
                print_error(": Syntax error \"&\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }
        }

        if (*bufptr == ';') {
            if (*(bufptr + 1) == ';') {
                free(*buf);
                print_error(": Syntax error \";;\" unexpected\n");
                setsvar("0", "2");
                return 2;
            }
            start = 1;
        }

        bufptr++;
    }

    if (complete & 7) {
        bufgl = NULL;

        if (isatty(fd))
            fprintstrs(1, ">", NULL);

        lenr = _getline(&bufgl, fd);

        if (lenr == 0 && !isatty(fd)) {
            free(*buf);
            free(bufgl);
            print_error(": Syntax error: unterminated quoted string\n");
            return -1;
        }

        if (lenr == -1) {
            /* Handle any error here if

