#include <nuklear.h>
#include "nuk_controls.h"

nk::TStatusBar::TStatusBar(int & h, int & w, std::string Name, __int64 _id) :
	IComponent(Name, _id),
	window_height(h),
	window_width(w),
	status_height(30)
{}

void nk::TStatusBar::draw(nk_context * ctx)
{
	if (nk_begin(ctx, name.c_str(),
		nk_rect(0.0f, (float)(window_height - status_height),
		(float)window_width, (float)status_height),
		NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR
	))
	{
		nk_layout_row_dynamic(ctx, ctx->current->bounds.h, 1);
		nk_label(ctx, text.c_str(), NK_TEXT_CENTERED);
	}
	nk_end(ctx);
}

nk::TGroupBox::TGroupBox(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TGroupBox::draw(nk_context * ctx)
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

nk::IComponent::IComponent(std::string Name, __int64 _id)
	: name(Name), id(_id)
{
	if (!name.length())
	{
		name = std::to_string(id);
	}
}

nk::IComponent * nk::IComponent::FindComponent(std::string const & strField)
{
	for (nk::IComponent* c : fields)
	{
		if (!c) { continue; }
		if (c->name != strField) { continue; }
		nk::IComponent* subChild = c->FindComponent(strField);
		if (subChild) { return subChild; }
		return c;
	}
	return nullptr;
}



nk::NKForm::NKForm(
	const float & width,
	const float & height, 
	std::string Name, 
	__int64 _id)
	:
	IComponent(Name, _id),
	Width(width),
	Height(height)
{}

EMyFrameworkType nk::NKForm::ComponentType() const
{
	return EMyFrameworkType::form;
}

void nk::NKForm::draw(nk_context * ctx)
{
	float width = Width * 0.8f;
	if (nk_begin(ctx, name.c_str(), nk_rect(0, 0, width, Height*0.8f),
		NK_WINDOW_BORDER | NK_WINDOW_TITLE
		//| NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE //<- updates bounds.. fullscreenwindow
		| NK_WINDOW_MINIMIZABLE
	))
	{
		
		for (nk::IComponent* comp : fields)
		{
			if (comp->ComponentType() != EMyFrameworkType::statusbar)
			{
				if (comp->applyLayout)
				{
					comp->applyLayout(ctx);
				}
				comp->draw(ctx);
			}
		}
		for (nk::IComponent* comp : fields)
		{
			if (comp->ComponentType() == EMyFrameworkType::statusbar)
				comp->draw(ctx);
		}
	}
	nk_end(ctx);
}

nk::TEdit::TEdit(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{
	
}

void nk::TEdit::draw(nk_context * ctx)
{
	if (text.capacity() < (text.size() + 10) )
	{
		text.resize(text.capacity() + 64);
	}
	nk_edit_string(ctx, NK_EDIT_SIMPLE, text.data(), &cursorpos, text.capacity(), nk_filter_default);
}

nk::TLabel::TLabel(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TLabel::draw(nk_context * ctx)
{
}

nk::TButton::TButton(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TButton::draw(nk_context * ctx)
{
}

nk::TListbox::TListbox(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TListbox::draw(nk_context * ctx)
{
}

nk::TCheckbox::TCheckbox(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TCheckbox::draw(nk_context * ctx)
{
}

nk::TCombobox::TCombobox(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TCombobox::draw(nk_context * ctx)
{
}

nk::TMemo::TMemo(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TMemo::draw(nk_context * ctx)
{
}

nk::TGrid::TGrid(std::string Name, __int64 _id) :
	IComponent(Name, _id)
{}

void nk::TGrid::draw(nk_context * ctx)
{
}
