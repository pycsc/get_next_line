*This project has been created as part of the 42 curriculum by lutsiara.*

# get_next_line

## Description

`get_next_line` is a C function that reads and returns one line at a time from a given
file descriptor. Each successive call returns the next line, including the terminating
`\n` character (except at EOF when the file does not end with one). It returns `NULL`
when there is nothing left to read or on error.

The bonus version supports reading from multiple file descriptors simultaneously
without losing track of each descriptor's reading state.

## Instructions

### Compilation

Compile the mandatory part with any `BUFFER_SIZE`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Omitting `-D BUFFER_SIZE` uses the default value of 42.

For the bonus (multi-fd) version:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

Using the Makefile:

```sh
make                     # builds mandatory (default BUFFER_SIZE=42)
make BUFFER_SIZE=1       # builds with BUFFER_SIZE=1
make BUFFER_SIZE=9999    # builds with BUFFER_SIZE=9999
make bonus               # builds bonus (default BUFFER_SIZE=42)
make bonus BUFFER_SIZE=5 # builds bonus with custom BUFFER_SIZE
make re                  # clean rebuild
```

Omitting `BUFFER_SIZE` from the `make` command uses the default value defined in the
header file (42).

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char  *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Multi-fd Usage (Bonus)

The bonus version tracks each file descriptor independently, so you can interleave
reads from multiple files without losing your place in any of them:

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd1 = open("file_a.txt", O_RDONLY);
    int   fd2 = open("file_b.txt", O_RDONLY);
    char  *line;

    line = get_next_line(fd1);     // reads line 1 from file_a
    printf("A: %s", line);
    free(line);

    line = get_next_line(fd2);     // reads line 1 from file_b
    printf("B: %s", line);
    free(line);

    line = get_next_line(fd1);     // resumes at line 2 of file_a
    printf("A: %s", line);
    free(line);

    line = get_next_line(fd2);     // resumes at line 2 of file_b
    printf("B: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

Each fd has its own stash, so switching between descriptors never mixes up their
reading positions.

## Algorithm

### Overview

The implementation uses a **stash-based buffered reading** strategy built around a
single static variable per file descriptor. The algorithm is split into three phases
that execute on every call to `get_next_line`:

### Phase 1 — Read and Accumulate (`read_and_stash`)

A temporary buffer of `BUFFER_SIZE` bytes is allocated. The function enters a loop
that calls `read()` and appends each chunk to the stash via `ft_strjoin` (which
reallocates). The loop terminates as soon as a newline character is found in the stash
or `read()` returns 0 (EOF). This ensures we read **only as much as needed** to
produce the next line — never the entire file.

### Phase 2 — Extract the Line (`extract_line`)

The stash now contains at least one complete line (or the final unterminated segment).
`extract_line` scans for `\n`, allocates a new string of exactly `len + 1` bytes
(including the newline if present), copies the characters, and returns it.

### Phase 3 — Trim the Stash (`update_stash`)

Everything after the extracted line remains relevant for subsequent calls.
`update_stash` allocates a new string holding only the remainder, frees the old stash,
and returns the remainder (or `NULL` if the stash is fully consumed). The static
variable then holds this remainder for the next invocation.

### Why This Approach

| Criterion | Justification |
|-----------|---------------|
| **Minimal reads** | The loop stops at the first newline, so no unnecessary `read()` calls are made. |
| **Arbitrary BUFFER_SIZE** | Works with 1, 42, 9999, or 10000000 because the stash dynamically grows via reallocation. |
| **No global variables** | State is preserved in a `static` local variable, satisfying the 42 constraint. |
| **Multi-fd support (bonus)** | Replacing the single static pointer with a static array indexed by fd (`stash[OPEN_MAX]`) isolates each descriptor's state with zero extra complexity. |
| **Memory safety** | Every allocation path has a corresponding `free`. On `read()` error the stash is freed immediately and `NULL` is returned, preventing leaks. |

### Complexity

- **Time per call**: O(n) where n is the length of the returned line.
- **Space**: O(BUFFER_SIZE + line_length) — one read buffer plus the stash.

## Resources

- `man 2 read` — POSIX read system call documentation
- `man 3 malloc` / `man 3 free` — Dynamic memory management
- [The C Programming Language (K&R)](https://en.wikipedia.org/wiki/The_C_Programming_Language) —
  Reference for static variables, file I/O, and pointer arithmetic
- [42 Norm v4](https://github.com/42School/norminette) — Coding style enforced by
  the project
- [Understanding File Descriptors](https://www.bottomupcs.com/file_descriptors.xhtml) —
  How UNIX file descriptors work under the hood
