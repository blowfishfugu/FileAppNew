#pragma once
#ifndef NK_SPACELAYOUT_H
#define NK_SPACELAYOUT_H
#include "Component.h"
namespace nk
{
	struct NKSpaceChild : public Component
	{
		struct nk_rect bounds;
		NKSpaceChild(struct nk_rect rect, std::string Name, __int64 _id);

		// Inherited via Component
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
	};

	struct NKSpace : public Component
	{
		nk_layout_format format;
		float height;
		int widget_count = INT_MAX;

		NKSpace(nk_layout_format format, float height, std::string Name, __int64 _id);


		// Inherited via Component
		virtual EMyFrameworkType ComponentType() const override;

		virtual void draw(struct nk_context * ctx) override;

	};
}
#endif