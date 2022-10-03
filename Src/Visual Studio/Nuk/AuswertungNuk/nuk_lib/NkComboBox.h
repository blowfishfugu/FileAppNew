#pragma once
#ifndef NK_COMBOBOX_H
#define NK_COMBOBOX_H
#include "Component.h"
namespace nk
{
	struct TCombobox : public Component
	{
		TCombobox(std::string Name, float w, float h, __int64 _id) noexcept;
		virtual ~TCombobox();
		struct nk_vec2 bounds;// { 200.0f, 200.0f };
		std::string text;
		std::vector<std::string> items;
		int itemindex = -1;
		size_t count() const { return items.size(); }
		std::string setText(std::string text);
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::combobox;
		}
		virtual void draw(struct nk_context* ctx) override;
	private:
		const char** itemptrs = nullptr;
		size_t _lastPtrCapacity = 0ull;
		void assignPtrs();
	};
}
#endif