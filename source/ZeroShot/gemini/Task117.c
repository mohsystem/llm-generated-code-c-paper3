//  Install libzip, libarchive  before running this code.
//  For example on ubuntu, Debian: sudo apt install libzip-dev libarchive-dev
#include <zip.h>
#include <archive.h>
#include <archive_entry.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>



// Helper function to create directories recursively
int makedir_recursive(const char *dir) {
    char tmp[256];
    char *p = NULL;
    size_t len