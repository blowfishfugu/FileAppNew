#include "NkGroupBox.h"
namespace nk
{ 

	TGroupBox::TGroupBox(std::string Name, float height, int width, __int64 _id) noexcept
		:
		height(height), width(width), rowHeight(height),
		Component(Name, _id)
	{
		NamedProperties["height"] = &this->height;
		NamedProperties["width"] = &this->width;
		NamedProperties["cols"] = &this->cols;
		NamedProperties["rowheight"] = &this->rowHeight;
	}

	void TGroupBox::draw(struct nk_context* ctx)
	{
		if (!visible) { return; }
		nk_layout_row_static(ctx, height, width, cols);
		if (nk_group_begin(ctx, name.c_str(), nk_panel_flags::NK_WINDOW_BORDER))
		{
			nk_layout_row_begin(ctx, nk_layout_format::NK_DYNAMIC, rowHeight, 1);
			nk_label(ctx, this->title.c_str(), nk_text_alignment::NK_TEXT_LEFT);
			this->drawChilds(ctx);
			nk_layout_row_end(ctx);
			nk_group_end(ctx);
		}
	}


}