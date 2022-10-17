#include "NkEdit.h"
namespace nk
{

	TEdit::TEdit(std::string Name, __int64 _id) noexcept
		:
		Component(Name, _id)
	{
		text.reserve(_MAX_PATH);
		NamedProperties["Text"] = &this->text;
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
		if (!visible) { return; }
		nk_edit_string(ctx, NK_EDIT_SIMPLE, text.data(), &cursorpos, static_cast<int>(text.capacity()), nk_filter_default);
	}

}