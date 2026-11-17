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
#include <set>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::set;
using std::stoi;
using std::string;

#include "pgutil.h"

//
// Since we are working in C++, we have to tell the
// C++ compiler that the functions in the provided
// nuPython code are C functions:
//
extern "C"
{
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
void help_command()
{
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
void print_graph_command(struct STMT *program)
{
  programgraph_print(program);
}

/**
 * @brief show memory contents command
 *
 * @return void
 */
void show_memory_command(struct RAM *memory)
{
  ram_print_map(memory);
  return;
}

/**
 * @brief set breakpoint at line n command
 *
 * @param n line number to set the breakpoint at
 * @return void
 */
void breakpoint_command(set<int> &breakpoints, int n)
{
  breakpoints.insert(n);
  return;
}

/**
 * @brief remove breakpoint at line n command
 *
 * @param n line number to remove the breakpoint from
 * @return void
 */
void remove_breakpoint_command(set<int> &breakpoints, int n)
{
  breakpoints.erase(n);
  return;
}

/**
 * @brief clear all breakpoint command
 *
 * @return void
 */
void clear_breakpoint_command(set<int> &breakpoints)
{
  breakpoints.clear();
}

/**
 * @brief list breakpoint command
 *
 * @return void
 */
void list_breakpoint_command(set<int> &breakpoints)
{
  for (int bp : breakpoints)
    cout << bp << endl;
  return;
}

/**
 * @brief what line will execute next command
 *
 * @return void
 */
void next_line_command(struct STMT *cur)
{
  cout << "Next line is: " << cur->line << endl;
  return;
}

/**
 * @brief step by executing the current statement command
 *
 * @return void
 */
void step_command(struct STMT *&cur, struct RAM *memory, set<int> &breakpoints,
                  bool &at_breakpoint) {}

/**
 * @brief run program from current statement command
 *
 * @return void
 */
void run_program_command(struct STMT *&cur, struct RAM *memory,
                         set<int> &breakpoints, bool &at_breakpoint)
{
  // TODO:
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
int main(int argc, char *argv[])
{
  FILE *input = nullptr;

  cout << "** Simple gdb for nuPython **" << endl;

  if (argc < 2)
  {
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
  // TODO (A): parse input, build program graph, ram_init
  //
  TokenQueue *tokens = parser_parse(input);
  if (tokens == NULL)
  {
    cout << "ERROR:An error occured while parsing." << endl;
    fclose(input);
    tokenqueue_destroy(tokens);
    return 0;
  }
  struct STMT *program = programgraph_build(tokens);
  if (program == NULL)
  {
    cout << "ERROR: An error occured while building the program." << endl;
    tokenqueue_destroy(tokens);
    fclose(input);
    return 0;
  }
  struct RAM *memory = ram_init();
  struct STMT *cur = program;
  set<int> breakpoints;
  bool at_breakpoint = false;

  //
  // command loop:
  //
  string cmd;

  while (true)
  {

    cout << endl;
    cout << "Enter a command, h for help >" << endl;
    cin >> cmd;

    if (cmd == "q")
    {
      //
      // quit:
      //
      break;
    }
    else if (cmd == "h")
    {
      help_command();
    }
    else if (cmd == "pg")
    {
      print_graph_command(program);
    }
    else if (cmd == "sm")
    {
      show_memory_command(memory);
    }
    else if (cmd == "b")
    {
      int n;
      cin >> n;
      breakpoint_command(breakpoints, n);
    }
    else if (cmd == "rb")
    {
      int n;
      cin >> n;
      remove_breakpoint_command(breakpoints, n);
    }
    else if (cmd == "cb")
    {
      clear_breakpoint_command(breakpoints);
    }
    else if (cmd == "lb")
    {
      list_breakpoint_command(breakpoints);
    }
    else if (cmd == "w")
    {
      next_line_command(cur);
    }
    else if (cmd == "s")
    {
      step_command(cur, memory, breakpoints, at_breakpoint);
    }
    else if (cmd == "r")
    {
      run_program_command(cur, memory, breakpoints, at_breakpoint);
    }
    else
    {
      cout << "unknown command" << endl;
    }

  } // while

  //
  // done: free data structures, close file, and return:
  //
  ram_destroy(memory);
  programgraph_destroy(program);
  tokenqueue_destroy(tokens);

  cout << endl;
  cout << "** Done **" << endl;

  fclose(input);

  return 0;
}
