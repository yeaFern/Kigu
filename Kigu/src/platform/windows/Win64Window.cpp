#include "Win64Window.h"
#ifdef KIGU_WINDOWS

namespace Kigu
{
    Win64Window::Win64Window()
    {
        std::cout << "Creating Win64Window." << std::endl;
    }

    Win64Window::~Win64Window()
    {
        std::cout << "Destroying Win64Window." << std::endl;
    }
    
    WindowPtr Window::New()
    {
        return std::make_shared<Win64Window>();
    }
}

#endif
