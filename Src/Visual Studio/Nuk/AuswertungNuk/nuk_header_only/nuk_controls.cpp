#include <nuklear.h>
#include "nuk_controls.h"

nk::Pool nk::IComponent::componentPool; //static

nk::IComponent::IComponent(std::string Name, __int64 _id) noexcept
	: name(Name), id(_id)
{
	if (!name.length())
	{
		name = std::to_string(id);
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
	status_height(30)
{}

void nk::TStatusBar::draw(struct nk_context* ctx)
{
	if (nk_begin(ctx, name.c_str(),
		nk_rect(2.0f, window_height - status_height, window_width - 2.0f, status_height),
		NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR))
	{
		nk_layout_row_dynamic(ctx, status_height, 1);
		nk_label(ctx, "statustext", NK_TEXT_CENTERED);
	}
	nk_end(ctx);

}

nk::TGroupBox::TGroupBox(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TGroupBox::draw(struct nk_context* ctx)
{
	nk_group_begin_titled(ctx, name.c_str(), title.c_str(), nk_panel_flags::NK_WINDOW_BORDER);
	nk_layout_row_begin(ctx, nk_layout_format::NK_STATIC, 20, 1);
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
{}

EMyFrameworkType nk::NKForm::ComponentType() const
{
	return EMyFrameworkType::form;
}

void nk::NKForm::draw(struct nk_context* ctx)
{
	if (nk_begin(ctx, name.c_str(), nk_rect(0.0f, 0.0f, Width*0.8f, Height*0.8f),
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

}

void nk::TEdit::draw(struct nk_context* ctx)
{
	if (text.capacity() < (text.size() + 10))
	{
		text.resize(text.capacity() + 64);
	}
	nk_edit_string(ctx, NK_EDIT_SIMPLE, text.data(), &cursorpos, text.capacity(), nk_filter_default);
}

nk::TLabel::TLabel(std::string Name, std::string Text, __int64 _id) noexcept
	:
	IComponent(Name, _id),
	text(Text)
{
}

void nk::TLabel::draw(struct nk_context* ctx)
{
	nk_label(ctx, text.c_str(), NK_TEXT_ALIGN_LEFT);
}

nk::TButton::TButton(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

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

void nk::TCombobox::draw(struct nk_context* ctx)
{
}

nk::TMemo::TMemo(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TMemo::draw(struct nk_context* ctx)
{
}

nk::TGrid::TGrid(std::string Name, __int64 _id) noexcept
	:
	IComponent(Name, _id)
{}

void nk::TGrid::draw(struct nk_context* ctx)
{
}


