#include "NkButton.h"
namespace nk
{
	TButton::TButton(std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id)
	{
		NamedProperties["Text"] = &text;
	}

	void TButton::draw(struct nk_context* ctx)
	{
	}

}