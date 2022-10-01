namespace nk
{
	class IComponent;
	struct Pool
	{
		__int64 id = 100;
		std::vector< std::unique_ptr<IComponent> > _owned;
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

	//TODO: PropDescriptor{min,max,&current,step,stepPerPixel)

	class IComponent
	{
	public:
		IComponent(std::string Name, __int64 _id) noexcept;
		IComponent(const IComponent&) = delete;
		IComponent() = delete;

		std::string name;
		__int64 id = 0; //<- if name is empty we need a unique id

		using BoundProp = std::variant<std::string*, int*, float*, double*>; //<-- hier fehlt noch nk_layout_format für den Spacer
		std::map<std::string, BoundProp> NamedProperties;
		void reflect(struct nk_context* ctx);

		virtual ~IComponent() = default;
		virtual EMyFrameworkType ComponentType() const = 0;

		//should draw the component
		//should redirect "events" -- in case of nuklear onClick is just a bool, discovered while painting
		//should walk subcomponents, and draw them in specific order
		virtual void draw(struct nk_context* ctx) = 0;
		void drawChilds(struct nk_context* ctx);

		std::vector<IComponent*> fields;
		IComponent* FindComponent(std::string const& strField);

		static Pool componentPool;
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