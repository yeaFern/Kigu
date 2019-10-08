#pragma once

#define KIGU_FATAL(msg) \
	std::cout << __FUNCSIG__ << std::endl; \
	std::cout << msg << std::endl; \
	std::exit(1);
