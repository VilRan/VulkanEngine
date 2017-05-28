#pragma once
class Rectangle
{
public:
	Rectangle();
	Rectangle(int left, int top, int width, int height);
	virtual ~Rectangle();

	inline const int GetLeft() const { return Left; }
	inline const int GetTop() const { return Top; }
	inline const int GetWidth() const { return Width; }
	inline const int GetHeight() const { return Height; }
	inline const int GetRight() const { return Left + Width; }
	inline const int GetBottom() const { return Top + Height; }

private:
	int Left;
	int Top;
	int Width;
	int Height;
};
