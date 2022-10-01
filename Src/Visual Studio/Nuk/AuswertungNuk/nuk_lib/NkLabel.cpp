#include "NkLabel.h"
namespace nk
{

	TLabel::TLabel(std::string Name, std::string Text, __int64 _id) noexcept
		:
		IComponent(Name, _id),
		text(Text)
	{
		NamedProperties["Text"] = &text;
	}

	void TLabel::draw(struct nk_context* ctx)
	{
		nk_label(ctx, text.c_str(), nk_alignment);
	}


}