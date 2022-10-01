#pragma once
#include "IComponent.h"
namespace nk
{
	struct NKForm : public IComponent
	{
		const float& Width;
		const float& Height;

		NKForm(const float& width, const float& height, //width=d3d11.ViewPort.Width ->kind of global, should adapt on Resize!
			std::string Name, __int64 _id) noexcept;

		std::string title;
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;

	};
}