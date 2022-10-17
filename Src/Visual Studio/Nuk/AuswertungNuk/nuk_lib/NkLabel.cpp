#include "NkLabel.h"
namespace nk
{

	TLabel::TLabel(std::string Name, std::string Text, __int64 _id) noexcept
		:
		Component(Name, _id),
		text(Text)
	{
		text.reserve(_MAX_PATH);
		NamedProperties["Text"] = &text;
	}

	void TLabel::draw(struct nk_context* ctx)
	{
		if (!visible) { return; }
		nk_label(ctx, text.c_str(), nk_alignment);
	}


}