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
		if (cols <= 0) { return; }

		if (ratios.size() == 0)
		{
			nk_layout_row_dynamic(ctx, height, cols);
			this->drawChilds(ctx);
			return;
		}
		
		bool open = false;
		int colidx = 0;
		size_t ratioidx = 0ul;
		for (size_t i = 0; i < fields.size(); ++i)
		{
			Component* comp = fields[i];
			if (colidx == 0)
			{
				nk_layout_row_begin(ctx, NK_DYNAMIC, height, cols);
				open = true;
			}

			nk_layout_row_push(ctx, ratios[ratioidx]);
			comp->draw(ctx);

			colidx++;
			if (colidx == cols)
			{
				nk_layout_row_end(ctx);
				colidx = 0; //colidx = i % cols
			}
			ratioidx++;
			if (ratioidx == ratios.size())
			{
				ratioidx = 0; //ratioidx= i % ratios.size()
			}
		}
		if (open) { nk_layout_row_end(ctx); }
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