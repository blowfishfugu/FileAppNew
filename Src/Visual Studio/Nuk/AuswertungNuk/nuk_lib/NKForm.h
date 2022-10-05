#pragma once
#ifndef NK_FORM_H
#define NK_FORM_H
#include "Component.h"
namespace nk
{
	struct NKForm : public Component
	{
		enum class NKResult: int{Ok,Cancel,Close};
		
		const float& Width;
		const float& Height;

		NKForm(const float& width, const float& height, //width=d3d11.ViewPort.Width ->kind of global, should adapt on Resize!
			std::string Name, __int64 _id) noexcept;

		std::string title;
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;

		//singleshot, aufgerufen bei erstem draw
		//kann auch verwendet werden, um fields bei erstem Aufruf zu erzeugen
		//z.B. form->onCreate=[](NKForm& form){ LoadFields(form, filename); };
		std::function<void(NKForm&)> onCreate = nullptr;
		std::function<void(NKForm&, NKResult)> onClose = nullptr;

		//Ruft onClose-Ereignis auf und setzt Form auf visible=0.
		//onClose kann visible auch wieder zurück auf 1 setzen.
		//Aufruf z.B. per Button::onClick=[&mainForm](){ mainForm.doClose(NKResult::Ok);}
		void doClose(NKResult returnValue);
	};
}
#endif