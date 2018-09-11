//
// CmdLineHandler.h
//

#ifndef CMD_LINE_HANDLER_H_
#define CMD_LINE_HANDLER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Database.h"

using namespace std;

class CmdLineHandler {
public:
	CmdLineHandler() {};
	~CmdLineHandler() {};

	void cmd_line_handler(Database& database, string cmd_line);
};

#endif
