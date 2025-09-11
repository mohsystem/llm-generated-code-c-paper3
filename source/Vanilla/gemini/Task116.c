// See the C++ solution.  C code would be very similar, using fork, exec, setuid, etc.
// The primary difference is handling strings (char* instead of std::string) and input (fgets/getch).

/*  Example C code structure (adapt from C++):

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h> // For getch


// ... (getch, get_password functions similar to C++)


void change_password(const char* username, const char* new_password) {
   // ... (fork, execl, setuid, error handling - similar to C++)
}



int main() {
   // ... (Test cases)
   return 0;
}

*/