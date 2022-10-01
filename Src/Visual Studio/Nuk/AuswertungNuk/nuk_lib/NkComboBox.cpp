#include "NkComboBox.h"
namespace nk
{

	TCombobox::TCombobox(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{}

	std::string TCombobox::setText(std::string text)
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i] == text)
			{
				this->text = text;
				this->itemindex = i;
				return this->text;
			}
		}
		items.push_back(text);
		this->text = text;
		itemindex = (static_cast<int>(items.size()) - 1);
		return this->text;
	}


	void TCombobox::draw(struct nk_context* ctx)
	{
	}

}