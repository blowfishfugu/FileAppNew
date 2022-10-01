#include "NkStatusBar.h"
namespace nk
{

	TStatusBar::TStatusBar(const float& w, const float& h,
		std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id),
		window_height(h),
		window_width(w),
		status_height(30),
		text("statustext")
	{
		NamedProperties["Text"] = &text;
	}

	void TStatusBar::draw(struct nk_context* ctx)
	{
		if (nk_begin(ctx, name.c_str(),
			nk_rect(2.0f, window_height - status_height, window_width - 2.0f, status_height),
			NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
		{
			nk_layout_row_dynamic(ctx, status_height, 1);
			nk_label(ctx, text.c_str(), NK_TEXT_CENTERED);
		}
		nk_end(ctx);

	}

}