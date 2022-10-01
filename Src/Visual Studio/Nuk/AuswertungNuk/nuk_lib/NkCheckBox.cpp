#include "NkCheckBox.h"
namespace nk
{

	TCheckbox::TCheckbox(std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id)
	{}

	void TCheckbox::draw(struct nk_context* ctx)
	{
	}

}