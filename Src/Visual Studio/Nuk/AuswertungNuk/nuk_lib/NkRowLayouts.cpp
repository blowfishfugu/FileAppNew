#include "NKRowLayouts.h"
namespace nk
{

	EMyFrameworkType NKRowDynamic::ComponentType() const
	{
		return EMyFrameworkType::dynamic_row;
	}

	void NKRowDynamic::draw(struct nk_context * ctx)
	{
		nk_layout_row_dynamic(ctx, height, cols);
		this->drawChilds(ctx);
	}

	EMyFrameworkType NKRowStatic::ComponentType() const
	{
		return EMyFrameworkType::static_row;
	}

	void NKRowStatic::draw(struct nk_context * ctx)
	{
		nk_layout_row_static(ctx, height, item_width, cols);
		this->drawChilds(ctx);
	}

}