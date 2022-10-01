#pragma once
#ifndef NUK_D3D_APP_H
#define NUK_D3D_APP_H
#include <d3d11.h>

#include <nuk_declare.h>

#ifdef NK_D3D11_IMPLEMENTATION //d3d11-struct
#undef NK_D3D11_IMPLEMENTATION
#endif
#define NK_INCLUDE_DEFAULT_FONT
#include <nuklear_d3d11.h>

#include <nuk_controls.h>

#include <string>
#include <assert.h>
struct WindowClass final
{
	WNDCLASSW wc{};
	std::wstring m_className;
	ATOM _registeredClass{};
	WindowClass() = delete;
	WindowClass(const WindowClass&) = delete;
	WindowClass(LPCWSTR className, WNDPROC wndproc)
		: m_className(className)
	{
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = wndproc;
		wc.hInstance = GetModuleHandleW(0);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszClassName = m_className.c_str();
		_registeredClass = RegisterClassW(&wc);
	}
	~WindowClass()
	{
		if (_registeredClass && wc.hInstance)
		{
			UnregisterClassW(wc.lpszClassName, wc.hInstance);
		}
	}
};


#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024

LRESULT CALLBACK
WindowProc(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);


class Application
{
	WindowClass wcClass{ L"NuklearWindowClass", WindowProc };
	struct nk_context* ctx{ nullptr };
public:
	//TODO: WindowProc-Redirection to prevent global statics
	static IDXGISwapChain *swap_chain;
	static ID3D11Device *device;
	static ID3D11DeviceContext *context;
	static ID3D11RenderTargetView* rt_view;
	static void set_swap_chain_size(int width, int height);
public:
	bool running = false;
	Application() {}
	~Application() { this->Release(); }
	void Init(int width, int height);

	const D3D11_VIEWPORT & GetViewport();

	

	

	void Run(nk::NKForm& mainForm);

	void Release();

};

#endif