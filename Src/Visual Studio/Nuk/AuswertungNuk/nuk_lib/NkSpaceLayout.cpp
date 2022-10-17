#include "NKSpaceLayout.h"
namespace nk
{
	NKSpace::NKSpace(nk_layout_format format, float height, std::string Name, __int64 _id) :
		Component(Name, _id), format(format), height(height)
	{
		NamedProperties["height"] = &this->height;
	}
	EMyFrameworkType NKSpace::ComponentType() const
	{
		return EMyFrameworkType::space_layout;
	}

	void NKSpace::draw(struct nk_context * ctx)
	{
		if (!visible) { return; }
		nk_layout_space_begin(ctx, format, height, widget_count);
		this->drawChilds(ctx);
		nk_layout_space_end(ctx);
	}

	NKSpaceChild::NKSpaceChild(struct nk_rect rect, std::string Name, __int64 _id)
		: Component(Name, _id), bounds(rect)
	{

		NamedProperties["x"] = &bounds.x;
		NamedProperties["y"] = &bounds.y;
		NamedProperties["w"] = &bounds.w;
		NamedProperties["h"] = &bounds.h;

	}

	EMyFrameworkType NKSpaceChild::ComponentType() const
	{
		return EMyFrameworkType::space_layout_child;
	}

	void NKSpaceChild::draw(nk_context * ctx)
	{
		if (!visible) { return; }
		nk_layout_space_push(ctx, bounds);
		this->drawChilds(ctx);
	}

}