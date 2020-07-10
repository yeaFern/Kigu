#pragma once

#include "Conditionals.h"
#ifdef KIGU_WINDOWS

#include <iostream>

#include "engine/Window.h"

namespace Kigu
{
    class Win64Window : public Window
    {
    public:
        Win64Window();
        virtual ~Win64Window();
    };
}


#endif
