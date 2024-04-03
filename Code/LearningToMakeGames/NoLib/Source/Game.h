#pragma once

#include <Windows.h>
#include <string>
#include <functional>

namespace Theia
{
	class Game
	{
	public:
		Game();
		Game(const Game&) = delete;
		Game& operator= (const Game&) = delete;

		~Game() {}

		inline static Game& GetInstance()
		{
			static Game game;
			return game;
		}

		inline static void Start()
		{
			GetInstance().StartWindow();
		}

		inline static void SetWindowProperties(const std::wstring& title, const int& width, const int& height)
		{
			GetInstance().windowTitle = title;
			GetInstance().windowWidth = width;
			GetInstance().windowHeight = height;
		}

		inline static void SetGameUpdate(const std::function<void(float delta)>& Update) { GetInstance().Update = Update; }

		inline static std::wstring GetWindowTitle() { return GetInstance().windowTitle; }
		inline static int GetWindowWidth() { return GetInstance().windowWidth; }
		inline static int GetWindowHeight() { return GetInstance().windowHeight; }

		friend LRESULT CALLBACK WindowCallback(
			HWND windowHandle,
			UINT msg,
			WPARAM wParam,
			LPARAM lParam
		);

	private:
		void StartWindow();


	private:
		HINSTANCE hInstance = 0;
		HWND windowHandle = 0;
		bool isRunning = false;
		std::wstring windowTitle;
		std::function<void(float delta)> Update;
		int windowWidth = 0, windowHeight = 0;
		
	};
}