#pragma once
#include "Component.h"
namespace nk
{
	struct TCheckbox : public Component
	{
		TCheckbox(std::string Name, __int64 _id) noexcept;
		std::string text;
		int checkstate = 0; //tristate?
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::checkbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}