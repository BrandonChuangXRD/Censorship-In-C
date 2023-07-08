# Censorship in C
This is a project I had in a class in UC Santa Cruz. It's
a file parser that determines what words are in a file and gives 1984 style response messages for any undesired words/phrases, implemented using a bloom filter and hash table for quick lookup.

## Installation (make commands)
A makefile is included, which will do the following with the given flags:
| Flag | Description |
| ---- | ---------- |
| all | creates all files and banhammer binary |
| banhammer | creates all files/banhammer binary (same as "all" or no flags) |
| tidy | remove all object (*.o) files |
| clean | remove all object (*.o) files, as well as the executable binary |
| format | format all c (\*.c) and c header (\*.h) files with clang-format |

Takes stdin as input and sends correctional messages to the writer about their transgressions on speech/thought ordinances

## Usage
```banhammer``` Takes stdin as input and sends correctional messages to the writer about their transgressions on speech/thought ordinances. the flags are as follows:

```./banhammer [-h] [-t] [-f] [-s]```
| Flag | Description |
| ---- | ----------- |
| -h | prints help message |
| -t | allows you to change the hash table size (default: 2^16)|
| -f | allows you to change the bloom filter size (default: 2^20) |
| -s | print statistics around the bloom filter instead of correctional messages |

## Credits
Many of the specified functions (none of the code behind it, but the names and parameters), the assignment idea, the salts, and 
the hash function are made by the professor and not my functions. He's asked to include the message below on other assignments so I will include it here:

```
BSD 2-Clause License
Copyright (c) 2021, Darrell Long
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```

## Known Errors
I recall having issues with valgrind finding memory leaks, but I couldn't figure out why this was the case, and I could not replicate it.
