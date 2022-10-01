#include "NkMemo.h"
namespace nk
{

	TMemo::TMemo(std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id),
		box_len(data.size())
	{
		NamedProperties["Text"] = &data;
	}

	void TMemo::setText(const std::string& txt)
	{
		data.clear();
		data = txt;
		box_len = static_cast<int>(data.size());
		height = 200;
	}

	void TMemo::draw(struct nk_context* ctx)
	{
		if (data.capacity() < (data.size() + 10))
		{
			data.resize(data.capacity() + 64);
		}
		//nk_layout_row_static(ctx, this->height, ctx->current->bounds.w, 1); //height?
		nk_edit_string(ctx, NK_EDIT_BOX, data.data(), &box_len, data.capacity(), nk_filter_default);
	}

}