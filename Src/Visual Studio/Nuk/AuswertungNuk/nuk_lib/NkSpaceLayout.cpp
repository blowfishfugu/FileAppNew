#include "NKSpaceLayout.h"
namespace nk
{

	EMyFrameworkType NKSpace::ComponentType() const
	{
		return EMyFrameworkType::space_layout;
	}

	void NKSpace::draw(struct nk_context * ctx)
	{
		nk_layout_space_begin(ctx, format, height, widget_count);
		this->drawChilds(ctx);
		nk_layout_space_end(ctx);
	}

	EMyFrameworkType NKSpaceChild::ComponentType() const
	{
		return EMyFrameworkType::space_layout_child;
	}

	void NKSpaceChild::draw(nk_context * ctx)
	{
		nk_layout_space_push(ctx, bounds);
		this->drawChilds(ctx);
	}

}