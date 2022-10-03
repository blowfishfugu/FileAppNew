#include "NkMemo.h"
namespace nk
{

	TMemo::TMemo(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id),
		box_len(static_cast<int>(data.size()))
	{
		data.reserve(64 * 1024); //64K.. genug?
		box_len = data.size();
		NamedProperties["Text"] = &data;
	}

	void TMemo::setText(const std::string& txt)
	{
		data = txt;
		box_len = static_cast<int>(data.size());
		height = 200;
	}

	void TMemo::draw(struct nk_context* ctx)
	{
		//nk_layout_row_static(ctx, this->height, ctx->current->bounds.w, 1); //height?
		nk_edit_string(ctx, NK_EDIT_BOX, data.data(), &box_len, static_cast<int>(data.capacity()), nk_filter_default);
	}

}