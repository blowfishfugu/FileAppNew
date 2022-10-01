namespace nk
{
	struct NKSpaceChild : public IComponent
	{
		struct nk_rect bounds;
		NKSpaceChild(struct nk_rect rect, std::string Name, __int64 _id)
			: IComponent(Name, _id), bounds(rect)
		{

			NamedProperties["x"] = &bounds.x;
			NamedProperties["y"] = &bounds.y;
			NamedProperties["w"] = &bounds.w;
			NamedProperties["h"] = &bounds.h;

		}

		// Inherited via IComponent
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
	};

	struct NKSpace : public IComponent
	{
		nk_layout_format format;
		float height;
		int widget_count = INT_MAX;

		NKSpace(nk_layout_format format, float height, std::string Name, __int64 _id) :
			IComponent(Name, _id), format(format), height(height)
		{
			NamedProperties["height"] = &this->height;
		}


		// Inherited via IComponent
		virtual EMyFrameworkType ComponentType() const override;

		virtual void draw(struct nk_context * ctx) override;

	};
}