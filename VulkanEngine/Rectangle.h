#pragma once
namespace Engine
{
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(int left, int top, int width, int height);
		virtual ~Rectangle();

		const int GetLeft() const { return Left; }
		const int GetTop() const { return Top; }
		const int GetWidth() const { return Width; }
		const int GetHeight() const { return Height; }
		const int GetRight() const { return Left + Width; }
		const int GetBottom() const { return Top + Height; }

	private:
		int Left;
		int Top;
		int Width;
		int Height;
	};
}