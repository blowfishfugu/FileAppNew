#pragma once
#include "IComponent.h"
namespace nk
{
	struct TLabel : public IComponent
	{
		TLabel(std::string Name, std::string Text, __int64 _id) noexcept;
		std::string text;
		nk_text_alignment nk_alignment = NK_TEXT_LEFT;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::label;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}