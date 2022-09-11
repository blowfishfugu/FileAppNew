#include <nuklear.h>
#include "nuk_controls.h"

nk::Pool nk::IComponent::componentPool; //static

nk::IComponent::IComponent(std::string Name, __int64 _id) noexcept
	: name(Name), id(_id)
{
	name.reserve(64);
	if (!name.length())
	{
		name = std::to_string(id);
	}
	NamedProperties["Name"] = &name;
}

void nk::IComponent::reflect(nk_context * ctx)
{
	auto buildPropName = [](const std::string& compName, const std::string& propName)
	{
		std::string uniqueName("#");
		uniqueName.append(compName);
		uniqueName.append(propName);
		return uniqueName;
	};

	for (auto& pp : NamedProperties)
	{
		auto& prop = pp.second;
		nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
		nk_layout_row_push(ctx, 0.25f);
		nk_label(ctx, pp.first.c_str(), NK_TEXT_LEFT);
		nk_layout_row_push(ctx, 0.75f);
		if (std::holds_alternative<std::string*>(prop))
		{
			std::string* pStr = std::get<std::string*>(prop);
			if (pStr->capacity() < pStr->length() + 10)
			{
				pStr->resize(pStr->capacity() + 64);
			}
			int pos = pStr->length(); //TODO: cursorpos pStr sollte struct (oder span) sein!
			nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, pStr->data(), pStr->capacity(), nk_filter_default);
		}
		else if (std::holds_alternative<int*>(prop))
		{
			std::string propName = buildPropName(name, pp.first);
			int* pInt = std::get<int*>(prop);
			*pInt= nk_propertyi(ctx, propName.c_str(), 0, *pInt, 1920, 1, 1);
		}
		else if (std::holds_alternative<float*>(prop))
		{
			std::string propName = buildPropName(name, pp.first);
			float* pFloat = std::get<float*>(prop);
			*pFloat = nk_propertyf(ctx, propName.c_str(), 0.0f, *pFloat, 1920.0f, 0.5f, 0.5f);
		}
		else if (std::holds_alternative<double*>(prop))
		{
			std::string propName = buildPropName(name, pp.first);
			double* pDouble = std::get<double*>(prop);
			*pDouble = nk_propertyd(ctx, propName.c_str(), 0.0, *pDouble, 1920.0, 0.5, 0.5);
		}
		nk_layout_row_end(ctx);
	}

}

nk::IComponent* nk::IComponent::FindComponent(std::string const & strField)
{
	for (nk::IComponent* c : fields)
	{
		if (!c) { continue; }
		nk::IComponent* subChild = c->FindComponent(strField);
		if (subChild) { return subChild; }

		if (c->name != strField) { continue; }
		return c;
	}
	return nullptr;
}


nk::TStatusBar::TStatusBar(const float& w, const float& h,
	std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id),
	window_height(h),
	window_width(w),
	status_height(30),
	text("statustext")
{
	NamedProperties["Text"] = &text;
}

void nk::TStatusBar::draw(struct nk_context* ctx)
{
	if (nk_begin(ctx, name.c_str(),
		nk_rect(2.0f, window_height - status_height, window_width - 2.0f, status_height),
		NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, status_height, 1);
		nk_label(ctx, text.c_str(), NK_TEXT_CENTERED);
	}
	nk_end(ctx);

}

nk::TGroupBox::TGroupBox(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TGroupBox::draw(struct nk_context* ctx)
{
	nk_layout_row_static(ctx, height, width, cols);
	nk_group_begin_titled(ctx, name.c_str(), title.c_str(), nk_panel_flags::NK_WINDOW_BORDER);
	nk_layout_row_begin(ctx, nk_layout_format::NK_DYNAMIC, 20, 1);
	for (nk::IComponent* comp : fields)
	{
		comp->draw(ctx);
	}
	nk_layout_row_end(ctx);
	nk_group_end(ctx);
}




nk::NKForm::NKForm(const float & width, const float & height,
	std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id),
	Width(width),
	Height(height)
{
	NamedProperties["Title"] = &title;
}

EMyFrameworkType nk::NKForm::ComponentType() const
{
	return EMyFrameworkType::form;
}

void nk::NKForm::draw(struct nk_context* ctx)
{
	if (nk_begin_titled(ctx, name.c_str(), title.c_str(),
		nk_rect(0.0f, 0.0f, Width*0.8f, Height*0.8f),
		NK_WINDOW_BORDER | NK_WINDOW_TITLE
		| NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE //<- updates bounds.. fullscreenwindow
		| NK_WINDOW_MINIMIZABLE
	))
	{
		for (nk::IComponent* comp : fields)
		{
			if (comp->ComponentType() != EMyFrameworkType::statusbar
				&& comp->ComponentType() != EMyFrameworkType::form
				)
			{
				if (comp->applyLayout)
				{
					comp->applyLayout(ctx);
				}
				comp->draw(ctx);
			}
		}
	}
	nk_end(ctx);

	//other forms, and the statusbar -> after nk_end
	for (nk::IComponent* comp : fields)
	{
		if (comp->ComponentType() == EMyFrameworkType::statusbar
			|| comp->ComponentType() == EMyFrameworkType::form
			)
			comp->draw(ctx);
	}
}

nk::TEdit::TEdit(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{
	NamedProperties["Text"] = &text;
}

void nk::TEdit::draw(struct nk_context* ctx)
{
	if (text.capacity() < (text.size() + 10))
	{
		text.resize(text.capacity() + 64);
	}
	nk_edit_string(ctx, NK_EDIT_SIMPLE, text.data(), &cursorpos, static_cast<int>(text.capacity()), nk_filter_default);
}

nk::TLabel::TLabel(std::string Name, std::string Text, __int64 _id) noexcept
	:
	IComponent(Name, _id),
	text(Text)
{
	NamedProperties["Text"] = &text;
}

void nk::TLabel::draw(struct nk_context* ctx)
{
	nk_label(ctx, text.c_str(), nk_alignment);
}

nk::TButton::TButton(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{
	NamedProperties["Text"] = &text;
}

void nk::TButton::draw(struct nk_context* ctx)
{
}

nk::TListbox::TListbox(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TListbox::draw(struct nk_context* ctx)
{
}

nk::TCheckbox::TCheckbox(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TCheckbox::draw(struct nk_context* ctx)
{
}

nk::TCombobox::TCombobox(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

std::string nk::TCombobox::setText(std::string text)
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

void nk::TCombobox::draw(struct nk_context* ctx)
{
}

nk::TMemo::TMemo(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id),
	box_len(data.size())
{
	NamedProperties["Text"] = &data;
}

void nk::TMemo::setText(const std::string& txt)
{
	data.clear();
	data = txt;
	box_len = static_cast<int>(data.size());
	height = 200;
}

void nk::TMemo::draw(struct nk_context* ctx)
{
	if (data.capacity() < (data.size() + 10))
	{
		data.resize(data.capacity() + 64);
	}
	//nk_layout_row_static(ctx, this->height, ctx->current->bounds.w, 1); //height?
	nk_edit_string(ctx, NK_EDIT_BOX, data.data(), &box_len, data.capacity(), nk_filter_default);
}

nk::TGrid::TGrid(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TGrid::draw(struct nk_context* ctx)
{
}


