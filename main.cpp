/*main.cpp*/

/**
 * @brief simple debugger for nuPython programs.
 *
 * To run:
 *
 *   ./a.out filename.py
 *
 * @author original template by Prof. Joe Hummel
 * @author Carson Apple
 * @author Charlie Du
 * @author Summon Gebrelibanos
 * @note Northwestern University
 */

#include <iostream>
#include <string>
#include <set>

using std::set;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::stoi;
using std::string;

#include "pgutil.h"

//
// Since we are working in C++, we have to tell the
// C++ compiler that the functions in the provided
// nuPython code are C functions:
//
extern "C" {
#include "execute.h"
#include "parser.h"
#include "programgraph.h"
#include "ram.h"
#include "tokenqueue.h"
}

/**
 * @brief help command
 *
 * @return void
 */
void help_command() {
  cout << "Available commands:" << endl;
  cout << "h -> help with list of commands" << endl;
  cout << "q -> quit the debugger" << endl;
  cout << "b n -> set breakpoint at line n" << endl;
  cout << "rb n -> remove breakpoint at line n" << endl;
  cout << "cb -> clear all breakpoints" << endl;
  cout << "lb -> list all breakpoints" << endl;
  cout << "pg -> print entire program graph" << endl;
  cout << "r -> run the program from the current stmt" << endl;
  cout << "s -> step by executing the current stmt" << endl;
  cout << "sm -> show memory contents" << endl;
  cout << "w -> what line will execute next?" << endl;
}


/**
 * @brief print program graph command
 *
 * @return void
 */
void print_graph_command() {
  
}


/**
 * @brief show memory contents command
 *
 * @return void
 */
void show_memory_command() {
  
}


/**
 * @brief set breakpoint at line n command
 *
 * @param n line number to set the breakpoint at
 * @return void
 */
void breakpoint_command(int n) {
  
}


/**
 * @brief remove breakpoint at line n command
 *
 * @param n line number to remove the breakpoint from
 * @return void
 */
void remove_breakpoint_command(int n) {
  
}


/**
 * @brief clear all breakpoint command
 *
 * @return void
 */
void clear_breakpoint_command() {
  
}


/**
 * @brief list breakpoint command
 *
 * @return void
 */
void list_breakpoint_command() {
  
}


/**
 * @brief what line will execute next command
 *
 * @return void
 */
void next_line_command() {
  
}


/**
 * @brief step by executing the current statement command
 *
 * @return void
 */
void step_command() {
  
}


/**
 * @brief run program from current statement command
 *
 * @return void
 */
void run_program_command() {
  
}




/**
 * @brief main
 *
 * usage: ./a.out filename.py
 *
 * If a filename is given, the file is opened and serves as
 * input to the debugger.
 *
 * @param argc # of arguments to program
 * @param argv Array of actual arguments
 * @return 0 Success
 */
int main(int argc, char *argv[]) {
  FILE *input = nullptr;

  cout << "** Simple gdb for nuPython **" << endl;

  if (argc < 2) {
    //
    // missing filename:
    //
    cout << "usage: ./a.out filename.py" << endl;
    return 0;
  }

  //
  // assume 2nd arg is a nuPython file, try to open:
  //
  char *filename = argv[1];

  input = fopen(filename, "r");

  if (input == nullptr) // unable to open:
  {
    cout << "**ERROR: unable to open input file "
         << "'" << filename << "' for input." << endl;

    return 0;
  }

  //
  // command loop:
  //
  string cmd;

  while (true) {

    cout << endl;
    cout << "Enter a command, h for help >" << endl;
    cin >> cmd;

    if (cmd == "q") {
      //
      // quit:
      //
      break;
    } else if (cmd == "h") {
      help_command();
    } else if (cmd == "pg") {
      print_graph_command();
    } else if (cmd == "sm") {
      show_memory_command();
    } else if (cmd == "b") {
      int n;
      cin >> n;
      breakpoint_command(n);
    } else if (cmd == "rb") {
      int n;
      cin >> n;
      remove_breakpoint_command(n);
    } else if (cmd == "cb") {
      clear_breakpoint_command();
    } else if (cmd == "lb") {
      list_breakpoint_command();
    } else if (cmd == "w") {
      next_line_command();
    } else if (cmd == "s") {
      step_command();
    } else if (cmd == "r") {
      run_program_command();
    } else {
      cout << "unknown command" << endl;
    }

  } // while

  //
  // done: free data structures, close file, and return:
  //
  cout << endl;
  cout << "** Done **" << endl;

  fclose(input);

  return 0;
}
