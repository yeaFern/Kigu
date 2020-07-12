#pragma once

#include <memory>

namespace Kigu
{
    class Window
    {
    public:
        virtual ~Window() = default;

		virtual void Update() = 0;

		virtual bool IsOpen() = 0;
    public:
        static std::shared_ptr<Window> New();
    };
    using WindowPtr = std::shared_ptr<Window>;
}
