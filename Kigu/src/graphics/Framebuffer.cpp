#include "graphics/Framebuffer.h"

namespace Kigu
{
	FramebufferPtr Framebuffer::Create()
	{
		return std::unique_ptr<Framebuffer>();
	}
}
