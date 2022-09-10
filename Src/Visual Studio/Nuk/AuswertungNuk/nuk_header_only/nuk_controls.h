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

	class IComponent
	{
	public:
		IComponent(std::string Name, __int64 _id) noexcept;
		IComponent(const IComponent&) = delete;
		IComponent() = delete;
		
		std::string name;
		__int64 id = 0; //<- if name is empty we need a unique id
		
		using BoundProp = std::variant<std::string*,__int64*,int*,float*>;
		std::map<std::string, BoundProp> NamedProperties;

		virtual ~IComponent() = default;
		virtual EMyFrameworkType ComponentType() const = 0;

		//should draw the component
		//should redirect "events" -- in case of nuklear onClick is just a bool, discovered while painting
		//should walk subcomponents, and draw them in specific order
		virtual void draw(struct nk_context* ctx) = 0;

		void reflect(struct nk_context* ctx)
		{
			for (auto& pp : NamedProperties)
			{
				auto& prop = pp.second;
				if( std::holds_alternative<std::string*>(prop))
				{ 
					std::string* pStr = std::get<std::string*>(prop);
					if (pStr->capacity() < pStr->length() + 10)
					{
						pStr->resize(pStr->capacity() + 64);
					}
					int pos = pStr->length();
					nk_edit_string_zero_terminated(ctx, NK_EDIT_SIMPLE, pStr->data(), pStr->capacity(), nk_filter_default);
				}
				if (std::holds_alternative<__int64*>(prop))
				{
					__int64* pInt64 = std::get<__int64*>(prop);
				}
				if (std::holds_alternative<int*>(prop))
				{
					int* pInt = std::get<int*>(prop);
				}
				if (std::holds_alternative<float*>(prop))
				{
					float* pFloat = std::get<float*>(prop);
				}
			}
			
		}

		std::function<void(struct nk_context*)> applyLayout;
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
}
#endif