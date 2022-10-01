#ifndef NUK_CONTROLS_H
#define NUK_CONTROLS_H

#define NK_INCLUDE_FIXED_TYPES
//#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#ifdef NK_IMPLEMENTATION
#undef NK_IMPLEMENTATION
#endif
#include <nuklear.h>


#include <vector>
#include <string>
#include <variant>
#include <functional>
#include <MyStdTypes.h>
struct nk_context;

//OOP-Approach to wrap nk-calls into a classic Dialog-Framework-Hierarchy
//alternatives might be ECS, where each drawable Item has some predefined
//set of Components that contain Meta and Drawing-Data.
//can't wrap my head around building a listview this way.. so oop for a start.

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
		
		using BoundProp = std::variant<std::string*,int*,float*,double*>; //<-- hier fehlt noch nk_layout_format für den Spacer
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

	struct TEdit : public IComponent
	{
		TEdit(std::string Name, __int64 _id) noexcept;
		
		//TODO: text+cursorpos in "spanning-struct" packen, für reflect werden beide werte gebraucht
		std::string text;
		int cursorpos = 0;
		
		nk_text_alignment nk_alignment = NK_TEXT_LEFT;
		void setText(std::string const& txt)
		{
			text = txt;
			cursorpos = static_cast<int>(text.length());
		}
		void setText(const char* txt)
		{
			text = txt;
			cursorpos = static_cast<int>(text.length());
		}
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::edit;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct TLabel : public IComponent
	{
		TLabel(std::string Name, std::string Text, __int64 _id) noexcept;
		std::string text;
		nk_text_alignment nk_alignment = NK_TEXT_LEFT;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::label;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct TGroupBox : public IComponent
	{
		TGroupBox(std::string Name, __int64 _id) noexcept;
		std::string title;
		float height = 200.0f;
		int width = 200;
		int cols = 1;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::groupbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct TButton : public IComponent
	{
		TButton(std::string Name, __int64 _id) noexcept;
		std::string text;
		std::function<void()> onClick = nullptr;
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::button;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct TListbox : public IComponent
	{
		TListbox(std::string Name, __int64 _id) noexcept;
		std::vector<std::string> items;
		int itemindex = -1;
		size_t count() const { return items.size(); }
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::listbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct TCheckbox : public IComponent
	{
		TCheckbox(std::string Name, __int64 _id) noexcept;
		std::string text;
		int checkstate = 0; //tristate?
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::checkbox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct TCombobox : public IComponent
	{
		TCombobox(std::string Name, __int64 _id) noexcept;
		std::string text;
		std::vector<std::string> items;
		int itemindex = -1;
		size_t count() const { return items.size(); }
		std::string setText(std::string text);
		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::combobox;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

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

	struct TGrid : public IComponent
	{
		TGrid(std::string Name, __int64 _id) noexcept;
		struct THeadItem {
			std::string caption;
			int width = 10;
			nk_text_alignment nk_alignment = nk_text_alignment::NK_TEXT_LEFT; //translated, ref in MyForm.h
			EMyAlignmentType alignment = EMyAlignmentType::left; //<-framework
		};
		std::vector<THeadItem> Columns;
		std::vector<std::vector<std::string>> Rows;
		std::vector<int> selected; // 0,1
		void clear()
		{
			Columns.clear();
			Rows.clear();
		}
		int rowCount() const
		{
			return static_cast<int>(Rows.size());
		}
		int colCount() const
		{
			return static_cast<int>(Columns.size());
		}

		virtual EMyFrameworkType ComponentType() const override {
			return EMyFrameworkType::listview;
		}
		virtual void draw(struct nk_context* ctx) override;
	};

	struct NKForm : public IComponent
	{
		const float& Width;
		const float& Height;

		NKForm(const float& width, const float& height, //width=d3d11.ViewPort.Width ->kind of global, should adapt on Resize!
			std::string Name, __int64 _id) noexcept;

		std::string title;
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw(struct nk_context * ctx) override;
		
	};

	struct NKRowDynamic : public IComponent
	{
		float height;
		int cols;
		NKRowDynamic(float height, int cols,
			std::string Name, __int64 _id) noexcept
			: IComponent(Name,_id), height(height),cols(cols)
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
			: IComponent(Name,_id), height(height), item_width(item_width), cols(cols)
		{
			NamedProperties["height"] = &this->height;
			NamedProperties["cols"] = &this->cols;
			NamedProperties["item_width"] = &this->item_width;
		}

		// Inherited via IComponent
		virtual EMyFrameworkType ComponentType() const override;
		virtual void draw( struct nk_context * ctx) override;
	};

	struct NKSpaceChild : public IComponent
	{
		struct nk_rect bounds;
		NKSpaceChild( struct nk_rect rect, std::string Name, __int64 _id)
			: IComponent(Name,_id), bounds(rect)
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

		NKSpace(nk_layout_format format, float height, std::string Name, __int64 _id):
			IComponent(Name,_id),format(format),height(height)
		{
			NamedProperties["height"] = &this->height;
		}


		// Inherited via IComponent
		virtual EMyFrameworkType ComponentType() const override;

		virtual void draw( struct nk_context * ctx) override;

	};
}
#endif