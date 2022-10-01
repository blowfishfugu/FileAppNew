#pragma once
#include "IComponent.h"
namespace nk
{
	struct TListbox : public IComponent
	{
		TListbox(std::string Name, __int64 _id) noexcept;
		std::vector<std::string> items;
		int itemindex = -1;
		size_t count() const { return items.size(); }
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::listbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}