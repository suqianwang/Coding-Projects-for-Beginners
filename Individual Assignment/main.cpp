//
//  main.cpp
//

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>

#include "Database.h"
#include "Course.h"
#include "Book.h"
#include "CmdLineHandler.h"

using namespace std;

int main(int argc, char *argv[]) {
    
    // create a database
    Database database;
    
    CmdLineHandler cmd_line_handler;
    
    // create a string to read each command line
    string cmd_line;
    int i = 0;
    while (!cin.eof()) {
        getline(cin, cmd_line);
        cout << endl << ++i << ": " << cmd_line << endl;
        // process every commmand line
        cmd_line_handler.cmd_line_handler(database, cmd_line);
    }
    cout << endl << "FINISHED" << endl;
    return 1;
}

