namespace nk
{
	struct NKRowDynamic : public IComponent
	{
		float height;
		int cols;
		NKRowDynamic(float height, int cols,
			std::string Name, __int64 _id) noexcept
			: IComponent(Name, _id), height(height), cols(cols)
		{
			NamedProperties["height"] = &this->height;
			NamedProperties["cols"] = &this->cols;
		}
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
	};

	struct NKRowStatic : public IComponent
	{
		float height;
		int item_width;
		int cols;
		NKRowStatic(float height, int item_width, int cols,
			std::string Name, __int64 _id) noexcept
			: IComponent(Name, _id), height(height), item_width(item_width), cols(cols)
		{
			NamedProperties["height"] = &this->height;
			NamedProperties["cols"] = &this->cols;
			NamedProperties["item_width"] = &this->item_width;
		}

		// Inherited via IComponent
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
	};
}