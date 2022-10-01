#include "NkCheckBox.h"
namespace nk
{

	TCheckbox::TCheckbox(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{}

	void TCheckbox::draw(struct nk_context* ctx)
	{
	}

}