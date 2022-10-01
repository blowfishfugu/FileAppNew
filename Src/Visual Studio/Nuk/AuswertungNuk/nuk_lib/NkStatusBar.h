namespace nk
{
	struct TStatusBar : public IComponent
	{
		const float& window_height;
		const float& window_width;

		TStatusBar(const float& w, const float& h, std::string Name, __int64 _id) noexcept;

		std::string text;
		float status_height;

		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::statusbar;
		}
		virtual void draw(struct nk_context* ctx) override;
	};
}