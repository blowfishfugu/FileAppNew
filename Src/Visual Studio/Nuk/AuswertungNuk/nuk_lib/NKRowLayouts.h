#pragma once
#ifndef NK_ROWLAYOUTS_H
#define NK_ROWLAYOUTS_H
#include "Component.h"
namespace nk
{
	struct NKRowDynamic : public Component
	{
		float height;
		int cols;
		std::vector<float> ratios; //should add up to 1.0f
		NKRowDynamic(float height, int cols,
			std::string Name, __int64 _id) noexcept;
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
	};

	struct NKRowStatic : public Component
	{
		float height;
		int item_width;
		int cols;
		NKRowStatic(float height, int item_width, int cols,
			std::string Name, __int64 _id) noexcept;

		// Inherited via Component
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
	};
}
#endif