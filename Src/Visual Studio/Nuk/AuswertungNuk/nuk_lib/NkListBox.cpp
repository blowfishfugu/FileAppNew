#include "NkListBox.h"
namespace nk
{

	TListbox::TListbox(std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id)
	{}

	void TListbox::draw(struct nk_context* ctx)
	{
	}

}