#pragma once
#include "Component.h"
namespace nk
{
	struct TGroupBox : public Component
	{
		TGroupBox(std::string Name, __int64 _id) noexcept;
		std::string title;
		float height = 200.0f;
		int width = 200;
		int cols = 1;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::groupbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}