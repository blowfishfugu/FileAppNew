#include "NkGrid.h"
namespace nk
{

	TGrid::TGrid(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{}

	void TGrid::draw(struct nk_context* ctx)
	{
	}

}