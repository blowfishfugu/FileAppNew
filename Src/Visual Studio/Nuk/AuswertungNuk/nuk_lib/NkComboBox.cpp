#include "NkComboBox.h"
namespace nk
{

	TCombobox::TCombobox(std::string Name, float w, float h, __int64 _id) noexcept
		:
		bounds{ w,h },
		Component(Name, _id)
	{
		NamedProperties["width"] = &this->bounds.x;
		NamedProperties["height"] = &this->bounds.y;
		NamedProperties["itemindex"] = &this->itemindex;
	}

	TCombobox::~TCombobox()
	{
		if (itemptrs)
		{
			delete[] itemptrs;
			itemptrs = nullptr;
		}
	}

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

	void TCombobox::assignPtrs()
	{
		if ( itemptrs==nullptr 
			|| _lastPtrCapacity==0 
			|| _lastPtrCapacity < items.size()
			)
		{
			if (itemptrs != nullptr)
			{
				delete[] itemptrs;
				itemptrs = nullptr;
			}
			_lastPtrCapacity = items.size() + 16;
			itemptrs = new const char*[_lastPtrCapacity];
			memset(itemptrs, 0, sizeof(const char*) * _lastPtrCapacity);
		}

		int itemidx = 0;
		for (const std::string& str : items)
		{
			itemptrs[itemidx++] = str.c_str();
		}
	}

	void TCombobox::draw(struct nk_context* ctx)
	{
		//hmm. nk_combo_begin_label + nk_selectable_label, vermutlich sicherer als char**
		if (items.size() == 0)
		{
			nk_label(ctx, this->text.c_str(), nk_text_alignment::NK_TEXT_LEFT);
			return;
		}
		
		if (itemindex < 0 ) { itemindex = 0; }
		if (itemindex >= items.size()) { itemindex = static_cast<int>(items.size()) - 1; }
		this->assignPtrs();
		//std::ssize ->erst ab c++20
		itemindex = nk_combo(ctx, itemptrs, static_cast<int>(items.size()), itemindex, 30, bounds);
	}
}