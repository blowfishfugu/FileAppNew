#include "NkButton.h"
namespace nk
{
	TButton::TButton(std::string Name, std::string text, __int64 _id) noexcept
		:
		text(text),
		Component(Name, _id)
	{
		NamedProperties["Text"] = &this->text;
	}

	TButton::TButton(std::string Name, __int64 _id) noexcept
		:
		TButton(Name,"",_id)
	{
	}

	void TButton::draw(struct nk_context* ctx)
	{
		if (nk_button_label(ctx, text.c_str()))
		{
			if (this->onClick)
			{
				onClick();
			}
		}
	}

}