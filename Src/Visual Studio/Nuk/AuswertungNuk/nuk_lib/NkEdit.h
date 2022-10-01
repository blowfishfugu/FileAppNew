#pragma once
#include "IComponent.h"
namespace nk
{
	struct TEdit : public IComponent
	{
		TEdit(std::string Name, __int64 _id) noexcept;

		//TODO: text+cursorpos in "spanning-struct" packen, für reflect werden beide werte gebraucht
		std::string text;
		int cursorpos = 0;

		nk_text_alignment nk_alignment = NK_TEXT_LEFT;
		void setText(std::string const& txt)
		{
			text = txt;
			cursorpos = static_cast<int>(text.length());
		}
		void setText(const char* txt)
		{
			text = txt;
			cursorpos = static_cast<int>(text.length());
		}
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::edit;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}