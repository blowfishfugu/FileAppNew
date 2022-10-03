#pragma once
#ifndef NK_GROUPBOX_H
#define NK_GROUPBOX_H
#include "Component.h"
namespace nk
{
	struct TGroupBox : public Component
	{
		TGroupBox(std::string Name, float height, int width, __int64 _id) noexcept;
		std::string title;
		float height = 200.0f;
		int width = 200;
		int cols = 1;
		float rowHeight = 200.0f;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::groupbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}
#endif