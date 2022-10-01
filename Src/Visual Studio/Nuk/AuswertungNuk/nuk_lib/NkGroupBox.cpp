#include "NkGroupBox.h"
namespace nk
{ 

	TGroupBox::TGroupBox(std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id)
	{}

	void TGroupBox::draw(struct nk_context* ctx)
	{
		nk_layout_row_static(ctx, height, width, cols);
		nk_group_begin_titled(ctx, name.c_str(), title.c_str(), nk_panel_flags::NK_WINDOW_BORDER);
		nk_layout_row_begin(ctx, nk_layout_format::NK_DYNAMIC, 20, 1);
		this->drawChilds(ctx);
		nk_layout_row_end(ctx);
		nk_group_end(ctx);
	}


}