#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <cstdlib>

#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define YELLOW "\x1B[33m"
#define RED "\x1B[31m"

#define LogInfo(msg) std::cout << CYAN "[INFO] " WHITE << msg << std::endl;
#define LogWarn(msg) std::cout << YELLOW "[WARN] " WHITE << msg << std::endl;
#define LogError(msg) std::cout << RED "[ERROR] " WHITE << msg << std::endl;
#define LogFatal(msg) std::cout << RED "[FATAL] " WHITE << msg << std::endl; std::abort();
#define LogRaw(msg) std::cout << msg << std::endl;

#ifdef _DEBUG
#define Assert(expr) if(!(expr)) { LogError("Assertion failed!\n        "#expr"\n        " __FILE__ ":" << __LINE__); std::abort(); }
#define Unreachable() Assert(!"Unreachable code!")
#else
#define Assert(expr)
#define Unreachable()
#endif
