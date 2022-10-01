#pragma once
#include <nuk_declare.h>
#include <MyStdTypes.h>

#include <vector>
#include <string>
#include <variant>
#include <functional>

#include "ComponentPool.h"

namespace nk
{
	extern Pool componentPool;
	//TODO: PropDescriptor{min,max,&current,step,stepPerPixel)

	class Component
	{
	public:
		Component(std::string Name, __int64 _id) noexcept;
		Component(const Component&) = delete;
		Component() = delete;

		std::string name;
		__int64 id = 0; //<- if name is empty we need a unique id

		using BoundProp = std::variant<std::string*, int*, float*, double*>; //<-- hier fehlt noch nk_layout_format f�r den Spacer
		std::map<std::string, BoundProp> NamedProperties;
		void reflect(struct nk_context* ctx);

		virtual ~Component() = default;
		virtual EMyFrameworkType ComponentType() const = 0;

		//should draw the component
		//should redirect "events" -- in case of nuklear onClick is just a bool, discovered while painting
		//should walk subcomponents, and draw them in specific order
		virtual void draw(struct nk_context* ctx) = 0;
		void drawChilds(struct nk_context* ctx);

		std::vector<Component*> fields;
		Component* FindComponent(std::string const& strField);

		template<typename fw_Type, class... Args>
		fw_Type* AddField(Args&&... ctor_args)
		{
			fw_Type* comp = componentPool.Add<fw_Type>(
				std::forward<Args>(ctor_args)...
				);
			this->fields.push_back(comp);
			return comp;
		}
	};
}