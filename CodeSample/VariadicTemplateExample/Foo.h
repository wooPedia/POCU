#pragma once


namespace samples
{
	class Foo final
	{
	public:
		Foo() = delete;
		~Foo() = default;

		Foo(int x);
		Foo(int x, int y);
		Foo(int x, int y, int z);

	private:
		int mX;
		int mY;
		int mZ;
	};

	Foo::Foo(int x)
		: mX(x)
		, mY(0)
		, mZ(0) 
	{
	}

	Foo::Foo(int x, int y)
		: mX(x)
		, mY(y)
		, mZ(0)
	{
	}

	Foo::Foo(int x, int y, int z)
		: mX(x)
		, mY(y)
		, mZ(z) 
	{
	}
}