#include "NkCheckBox.h"
namespace nk
{

	TCheckbox::TCheckbox(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{}

	void TCheckbox::draw(struct nk_context* ctx)
	{
		int oldstate = checkstate;
		nk_checkbox_label(ctx, text.c_str(), &this->checkstate);
		if (checkstate != oldstate)
		{
			if (onCheckChanged)
			{
				onCheckChanged(this, checkstate);
			}
		}
	}

}