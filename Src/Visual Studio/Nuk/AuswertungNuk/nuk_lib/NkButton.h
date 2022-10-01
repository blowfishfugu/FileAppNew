#pragma once
#include "IComponent.h"
namespace nk
{
	struct TButton : public IComponent
	{
		TButton(std::string Name, __int64 _id) noexcept;
		std::string text;
		std::function<void()> onClick = nullptr;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::button;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}