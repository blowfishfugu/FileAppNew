namespace nk 
{
	struct TMemo : public IComponent
	{
		TMemo(std::string Name, __int64 _id) noexcept;
		std::string data;
		float height = 200.0f;
		int box_len;
		void setText(const std::string& txt);

		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::memo;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}