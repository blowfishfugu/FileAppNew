#include "NKRowLayouts.h"
namespace nk
{
	NKRowDynamic::NKRowDynamic(float height, int cols, std::string Name, __int64 _id) noexcept
		: Component(Name, _id), height(height), cols(cols)
	{
		NamedProperties["height"] = &this->height;
		NamedProperties["cols"] = &this->cols;
	}
	EMyFrameworkType NKRowDynamic::ComponentType() const
	{
		return EMyFrameworkType::dynamic_row;
	}

	void NKRowDynamic::draw(struct nk_context * ctx)
	{
		nk_layout_row_dynamic(ctx, height, cols);
		this->drawChilds(ctx);
	}

	NKRowStatic::NKRowStatic(float height, int item_width, int cols, std::string Name, __int64 _id) noexcept
		: Component(Name, _id), height(height), item_width(item_width), cols(cols)
	{
		NamedProperties["height"] = &this->height;
		NamedProperties["cols"] = &this->cols;
		NamedProperties["item_width"] = &this->item_width;
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