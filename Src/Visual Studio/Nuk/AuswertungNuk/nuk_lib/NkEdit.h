#pragma once
#ifndef NK_EDIT_H
#define NK_EDIT_H
#include "Component.h"
namespace nk
{
	struct TEdit : public Component
	{
		TEdit(std::string Name, __int64 _id) noexcept;

		//TODO: text+cursorpos in "spanning-struct" packen, für reflect werden beide werte gebraucht
		std::string text;
		int cursorpos = 0;

		nk_text_alignment nk_alignment = NK_TEXT_LEFT;
		void setText(std::string const& txt);
		void setText(const char* txt);
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::edit;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}
#endif