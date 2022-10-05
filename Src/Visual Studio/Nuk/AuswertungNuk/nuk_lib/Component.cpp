#include "Component.h"
#include "ComponentPool.h"
namespace nk
{
	Pool componentPool; //static

	Component::Component(std::string Name, __int64 _id) noexcept
		: name(Name), id(_id)
	{
		name.reserve(64);
		if (!name.length())
		{
			name = std::to_string(id);
		}
		NamedProperties["Name"] = &name;
		NamedProperties["Visible"] = &visible;
	}

	void Component::drawChilds(struct nk_context* ctx)
	{
		for (Component* comp : fields)
		{
			comp->draw(ctx);
		}
	}

	void Component::reflect(struct nk_context * ctx)
	{
		auto buildPropName = [](const std::string& compName, const std::string& propName)
		{
			std::string uniqueName("#");
			uniqueName.append(compName);
			uniqueName.append(propName);
			return uniqueName;
		};

		for (auto& pp : NamedProperties)
		{
			auto& prop = pp.second;
			nk_layout_row_begin(ctx, NK_DYNAMIC, 0, 2);
			nk_layout_row_push(ctx, 0.25f);
			nk_label(ctx, pp.first.c_str(), NK_TEXT_LEFT);
			nk_layout_row_push(ctx, 0.75f);
			if (std::holds_alternative<std::string*>(prop))
			{
				std::string* pStr = std::get<std::string*>(prop);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, pStr->data(), static_cast<int>(pStr->capacity()), nk_filter_default);
			}
			else if (std::holds_alternative<int*>(prop))
			{
				std::string propName = buildPropName(name, pp.first);
				int* pInt = std::get<int*>(prop);
				*pInt = nk_propertyi(ctx, propName.c_str(), 0, *pInt, 1920, 1, 1);
			}
			else if (std::holds_alternative<float*>(prop))
			{
				std::string propName = buildPropName(name, pp.first);
				float* pFloat = std::get<float*>(prop);
				*pFloat = nk_propertyf(ctx, propName.c_str(), 0.0f, *pFloat, 1920.0f, 0.5f, 0.5f);
			}
			else if (std::holds_alternative<double*>(prop))
			{
				std::string propName = buildPropName(name, pp.first);
				double* pDouble = std::get<double*>(prop);
				*pDouble = nk_propertyd(ctx, propName.c_str(), 0.0, *pDouble, 1920.0, 0.5, 0.5);
			}
			nk_layout_row_end(ctx);
		}

	}

	Component* Component::FindComponent(std::string const & strField)
	{
		for (Component* c : fields)
		{
			if (!c) { continue; }
			Component* subChild = c->FindComponent(strField);
			if (subChild) { return subChild; }

			if (c->name != strField) { continue; }
			return c;
		}
		return nullptr;
	}

}