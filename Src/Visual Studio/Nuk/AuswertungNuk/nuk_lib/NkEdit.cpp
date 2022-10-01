#include "NkEdit.h"
namespace nk
{

	TEdit::TEdit(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{
		text.resize(_MAX_PATH);
		NamedProperties["Text"] = &text;
	}

	void TEdit::setText(std::string const & txt)
	{
		text = txt;
		cursorpos = static_cast<int>(text.length());
	}

	void TEdit::setText(const char * txt)
	{
		text = txt;
		cursorpos = static_cast<int>(text.length());
	}

	void TEdit::draw(struct nk_context* ctx)
	{
		nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, text.data(), static_cast<int>(text.capacity()), nk_filter_default);
	}

}