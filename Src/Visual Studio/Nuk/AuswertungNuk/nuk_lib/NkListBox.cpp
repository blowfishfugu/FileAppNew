#include "NkListBox.h"
namespace nk
{

	TListbox::TListbox(std::string Name, __int64 _id) noexcept
		:
		item_height(30.0f),
		Component(Name, _id)
	{
		NamedProperties["item_height"] = &item_height;
	}

	void TListbox::draw(struct nk_context* ctx)
	{
		syncSelectionSize();
		nk_layout_row_dynamic(ctx, item_height, 1);

		for (int i = 0; i < items.size(); ++i)
		{
			std::string& txt = items[i];
			nk_selectable_label(ctx, txt.c_str(), nk_text_alignment::NK_TEXT_LEFT, &selected[i]);
		}
	}

	void TListbox::syncSelectionSize()
	{
		if (items.size() > selected.size())
		{
			for (int b = selected.size(); b < items.size(); ++b)
			{
				selected.push_back(0);
			}
		}
	}

	void TListbox::selectIndex(int index)
	{
		syncSelectionSize();
		std::fill(selected.begin(), selected.end(), 0);
		if (index >= 0 && index < selected.size())
		{
			selected[index] = 1;
		}
	}

	std::string TListbox::firstSelectedValue()
	{
		int sel = -1;
		for (int i = 0; i < selected.size(); ++i)
		{
			if (selected[i])
			{
				return items[i];
			}
		}
		return "";
	}

}