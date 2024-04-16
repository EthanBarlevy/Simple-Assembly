#include "Command.h"

Command::Command(std::string code, std::string registry)
{
	ConditionCode = code;
	Register = registry;
}
