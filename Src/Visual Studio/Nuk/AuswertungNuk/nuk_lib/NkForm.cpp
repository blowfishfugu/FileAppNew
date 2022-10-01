#include "NKForm.h"
namespace nk
{

	NKForm::NKForm(const float & width, const float & height,
		std::string Name, __int64 _id) noexcept
		:
		IComponent(Name, _id),
		Width(width),
		Height(height)
	{
		NamedProperties["Title"] = &title;
	}

	EMyFrameworkType NKForm::ComponentType() const
	{
		return EMyFrameworkType::form;
	}

	void NKForm::draw(struct nk_context* ctx)
	{
		if (nk_begin_titled(ctx, name.c_str(), title.c_str(),
			nk_rect(0.0f, 0.0f, Width*0.8f, Height*0.8f),
			NK_WINDOW_BORDER | NK_WINDOW_TITLE
			| NK_WINDOW_SCALABLE | NK_WINDOW_MOVABLE //<- updates bounds.. fullscreenwindow
			| NK_WINDOW_MINIMIZABLE
		))
		{
			for (IComponent* comp : fields)
			{
				if (comp->ComponentType() != EMyFrameworkType::statusbar
					&& comp->ComponentType() != EMyFrameworkType::form
					)
				{
					comp->draw(ctx);
				}
			}
		}
		nk_end(ctx);

		//other forms, and the statusbar -> after nk_end
		for (IComponent* comp : fields)
		{
			if (comp->ComponentType() == EMyFrameworkType::statusbar
				|| comp->ComponentType() == EMyFrameworkType::form
				)
				comp->draw(ctx);
		}
	}

}