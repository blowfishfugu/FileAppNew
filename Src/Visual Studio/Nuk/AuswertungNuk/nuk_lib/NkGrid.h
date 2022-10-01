#pragma once
#include "Component.h"
namespace nk
{
	struct TGrid : public Component
	{
		TGrid(std::string Name, __int64 _id) noexcept;
		struct THeadItem {
			std::string caption;
			int width = 10;
			nk_text_alignment nk_alignment = nk_text_alignment::NK_TEXT_LEFT; //translated, ref in MyForm.h
			EMyAlignmentType alignment = EMyAlignmentType::left; //<-framework
		};
		std::vector<THeadItem> Columns;
		std::vector<std::vector<std::string>> Rows;
		std::vector<int> selected; // 0,1
		void clear()
		{
			Columns.clear();
			Rows.clear();
		}
		int rowCount() const
		{
			return static_cast<int>(Rows.size());
		}
		int colCount() const
		{
			return static_cast<int>(Columns.size());
		}

		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::listview;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

}