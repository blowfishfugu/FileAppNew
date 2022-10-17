#include "NkGrid.h"
namespace nk
{

	TGrid::TGrid(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{}

	// 0,1

	void TGrid::clear()
	{
		Columns.clear();
		Rows.clear();
	}

	int TGrid::rowCount() const
	{
		return static_cast<int>(Rows.size());
	}

	int TGrid::colCount() const
	{
		return static_cast<int>(Columns.size());
	}

	void TGrid::draw(struct nk_context* ctx)
	{
		if (!visible) { return; }
	}

}