#include "NkCheckBox.h"
namespace nk
{

	TCheckbox::TCheckbox(std::string Name, std::string text, __int64 _id) noexcept
		:
		text(text),
		Component(Name, _id)
	{
		NamedProperties["Checked"] = &this->checkstate;
		NamedProperties["Text"] = &this->text;
	}

	TCheckbox::TCheckbox(std::string Name, __int64 _id) noexcept
		:
		TCheckbox(Name,"",_id)
	{}

	void TCheckbox::draw(struct nk_context* ctx)
	{
		if (!visible) { return; }
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