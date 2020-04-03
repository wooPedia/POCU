#include "VariadicTemplateFunctionExample.h"
#include "Foo.h"
#include "Goo.h"

namespace samples
{
	void VariadicTemplateFunctionExample()
	{
		//Foo* foo1 = Create<Foo>(); // compile error
		Foo* foo2 = Create<Foo>(1);
		Foo* foo3 = Create<Foo>(1, 3);
		Foo* foo4 = Create<Foo>(1, 3, 5);


		//Goo* goo1 = Create<Goo>(); // compile error
		Goo* goo2 = Create<Goo>("woohyeon", 25);

		delete foo2;
		delete foo3;
		delete foo4;
		delete goo2;
	}
}