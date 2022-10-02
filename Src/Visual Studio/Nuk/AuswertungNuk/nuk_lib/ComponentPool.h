#pragma once
#ifndef NK_COMPONENT_POOL_H
#define NK_COMPONENT_POOL_H
#include <vector>
#include <memory>

namespace nk
{
	class Component;
	class Pool
	{
		__int64 id = 100;
		std::vector< std::unique_ptr<Component> > _owned;
	public:
		template<typename fw_Type, class... Args>
		fw_Type* Add(Args&&... ctor_args)
		{
			std::unique_ptr<fw_Type> comp
				= std::make_unique<fw_Type>(
					std::forward<Args>(ctor_args)...,
					++id
					);

			fw_Type* result = comp.get();
			_owned.emplace_back(std::move(comp));
			return result;
		}
	};
}
#endif