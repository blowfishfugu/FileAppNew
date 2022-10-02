#pragma once
#ifndef NK_LISTBOX_H
#define NK_LISTBOX_H
#include "Component.h"
namespace nk
{
	struct TListbox : public Component
	{
		TListbox(std::string Name, __int64 _id) noexcept;
		std::vector<std::string> items;
		std::vector<nk_bool> selected;
		
		size_t count() const { return items.size(); }
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::listbox;
		}
		virtual void draw(struct nk_context* ctx) override;

		void syncSelectionSize();
		void selectIndex(int index);
		std::string firstSelectedValue();
	};
}
#endif