#pragma once

#include <memory>

namespace Kigu
{
    class Window
    {
    public:
        virtual ~Window() = default;
    public:
        static std::shared_ptr<Window> New();
    };
    using WindowPtr = std::shared_ptr<Window>;
}
