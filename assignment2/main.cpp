#include <iostream>
#include <vector>
#include <string>

/*
	// CORE
Prompt user
Take in command line
Parse commands
Execute commands
Loop back
*/

/*
	// EXTRA

*/

class Command{
	public:
		std::string cmd;
		std::vector <std::string> arg;
		std::string connect;
		bool ran;
		bool valid;
		void execvp();
		void fork();
		void waitpid();
		void clear(){
			cmd.clear();
			arg.clear();
			connect.clear();
			ran = false;
			valid = false;
		}
};
// Holds the data values for a command
// Containts the functions to execute said commands

class connector{
	public:
		bool semi(bool ran);
		bool andAnd(bool ran);
		bool orOr(bool ran);
		bool comment(bool ran);
};
// Different connectors require different implementations
// Implementations can be added or removed here

void parse(std::string& rawCmd, std::vector<Command>& cmdList){
	std::string tempString;		// string to build cmd/arg as they come in
	Command tempCommand;	// Command object to be pushed into the vector

	for(int i=0; i<rawCmd.size(); i++){		// loops through the whole string
		if(rawCmd.at(i) != ' '){				// if the char at curr. index is not a space
			if(rawCmd.at(i) == ';'){			// if the char is a semicolon
				tempCommand.connect = rawCmd.at(i);	// save the connector as ;
				cmdList.push_back(tempCommand);	// save the command
				tempCommand.clear();			// clear the temp command
			}
			else if((rawCmd.at(i) == '|') && (i != rawCmd.size()-1)){		// if the char is a vertical bar and NOT the last char in the string
				if(rawCmd.at(i+1) == '|'){		// if the next char is also a vertical bar
					if(tempCommand.connect.size() != 0){	// if there's already a value in tempCommand's connector
						cmdList.push_back(tempCommand);		// then pushback the old command 
						tempCommand.clear();				// clear the old command
					}
					tempCommand.connect = "||";	// set the connector
					i++;						// update the value of i
				}
			}
			else if((rawCmd.at(i) == '&') && (i != rawCmd.size()-1)){		// if the char is an ampersand and NOT the last char in the string
				if(rawCmd.at(i+1) == '&'){		// if the next char is also an ampersand
					if(tempCommand.connect.size() != 0){	// if there's already a value in tempCommand's connector
						cmdList.push_back(tempCommand);		// then pushback the old command
						tempCommand.clear();				// clear he old command
					}
					tempCommand.connect = "&&";	// set the connector
					i++;						// update the value of i
				}
			}
			else if(rawCmd.at(i) == '#'){		// if the curr char is a comment sign
				i=rawCmd.size();				// cut to the end of the loop
			}
			else{
				tempString += rawCmd.at(i);		// build the command/argument in tempString
				std::cout << tempString << std::endl;
			}
		}
		else{									// the current char is a space
			if(tempString.size() != 0){			// if the tempstring isn't currently zero
				if(tempCommand.cmd.size() == 0){	// if the cmd string in Command is empty
					tempCommand.cmd = tempString;	// then set cmd to tempString
					tempString.clear();			// clear the tempString
				}
				else{// if there is a value in cmd then it must be an arg
					std::cout << "arg added" << std::endl;
					tempCommand.arg.push_back(tempString); // add it to the list of arg
					tempString.clear();			// reset the temp string
				}
			}
		}	// else the space gets ignored
	}
	if(tempString.size() != 0){		// if tempString isn't empty
		if(tempCommand.cmd.size() == 0){	// if tempCommand cmd is empty
			tempCommand.cmd = tempString;	// set tempCommand cmd to tempString
		}
		else{
			tempCommand.arg.push_back(tempString); // else its an argument and add it to the arg list
		}
	}
	cmdList.push_back(tempCommand); // the string ended and whaever's left is pushed back
}

void testMain1(std::vector<Command> cmdList){
	for(int i=0; i<cmdList.size(); ++i){
		std::cout << "Command object #: " << i+1 << std::endl;
		std::cout << "Command: ";
		if(cmdList.at(i).cmd.size() != 0){
			std::cout << cmdList.at(i).cmd << std::endl;
		}
		else{
			std::cout << "No command" << std::endl;
		}

		std::cout << "Arguments list:" << std::endl;
		if(cmdList.at(i).arg.size() != 0){
			for(int o=0; o<cmdList.at(i).arg.size(); ++o){
				std::cout << "Arg: ";
				if(cmdList.at(i).arg.at(o).size() != 0){
					std::cout << cmdList.at(i).arg.at(o) << std::endl;
				}
				else{
					std::cout << "No Arg" << std::endl;
				}
			}
		}
		else{
			std::cout << "No arguments" << std::endl;
		}

		std::cout << "Ran is: ";
		if(cmdList.at(i).ran == 0){
			std::cout << "False" << std::endl;
		}
		else{
			std::cout << "True" << std::endl;
		}

		std::cout << "Valid is: ";
		if(cmdList.at(i).valid == 0){
			std::cout << "False" << std::endl;
		}
		else{
			std::cout << "True" << std::endl;
		}
	}
}
int main(){
	std::string rawCmd;			// Raw input from user
	std::vector<Command> cmdList;			// Vector to store commands after they've been parsed

	std::cout << "$ ";			// Prompt user
	std::getline(std::cin, rawCmd); // Receive command line

	parse(rawCmd, cmdList);		// Parse the command line

	testMain1(cmdList);
	return 0;
}
