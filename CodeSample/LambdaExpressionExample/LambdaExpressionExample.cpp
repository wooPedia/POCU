#include <string>
#include <iostream>

#include "LambdaExpressionExample.h"

using namespace std;

namespace samples
{
	void LambdaExpressionExample()
	{
		int i = 0;
		float f = 1.0f;
		char c = 'b';

		auto noCapturing = []()
		{
			cout << "No capture:" << endl;


			/*
				아래 코드는 컴파일 에러를 발생시킵니다.
				람다 함수 내부에서 선언된 지역변수 또는 매개변수 또는 
				캡쳐 블럭에 있는 변수만 read 가능합니다.
			*/

			//cout << "i: " << i << endl;
			//cout << "f: " << f << endl;
			//cout << "c: " << c << endl;
		};

		auto captureByValue = [=]()
		{
			cout << "Capture by value:" << endl;

			cout << "i: " << i << endl;
			cout << "f: " << f << endl;
			cout << "c: " << c << endl;


			/*
				아래 코드는 컴파일 에러를 발생시킵니다.
				캡쳐 블럭의 '='는 람다식이 속한 scope의 모든 지역 변수를
				사용하되, value 타입으로 복사된 값이며 read only입니다.
			*/

			//i++;
			//f = 2.0f;
			//c = 'a';
		};

		auto captureByRef = [&]()
		{
			/*
				캡쳐 블럭에 '&'는 람다식이 속한 scope의 모든 지역 변수를
				참조 타입으로 set되며 read/write 모두 가능합니다.
			*/

			cout << "Capture by reference:" << endl;

			cout << "i: " << i << endl;
			cout << "f: " << f << endl;
			cout << "c: " << c << endl;

			i++;
			f++;
			c++;

			cout << "i: " << i << endl;
			cout << "f: " << f << endl;
			cout << "c: " << c << endl;

			i--;
			f--;
			c--;
		};

		auto captureByVariableNames = [i, f]()
		{
			cout << "Capture by variable names value:" << endl;

			cout << "i: " << i << endl;
			cout << "f: " << f << endl;

			/*
				아래 코드는 컴파일 에러를 발생시킵니다.
				캡쳐 블럭에 포함된 변수는 모두 read only한 value 타입입니다.
			*/

			//i++;
			//f++;
		};

		auto captureByVariableRef = [&i, &f]()
		{
			cout << "Capture by variable names reference:" << endl;

			// 캡쳐 블럭에 포함되지 않은 변수는 읽을 수 없습니다.
			//cout << "c: " << c << endl;


			// 참조로 받으므로 read/write 가능합니다.
			i++;
			f++;

			cout << "i: " << i << endl;
			cout << "f: " << f << endl;

			i--;
			f--;
		};
		
		auto captureByMix = [=, &f, &c]()
		{
			cout << "Capture by value by default, then by variable names reference" << endl;

			// 기본적으로 모든 지역 변수를 read only인 value 타입으로 받지만
			// f, c에 대해선 read/write 가능한 참조 타입으로 받습니다.

			// Compile error.
			// i++;

			f++;
			c++;

			cout << "i: " << i << endl;
			cout << "f: " << c << endl;
			cout << "c: " << f << endl;

			f--;
			c--;
		};

		auto captureByValueMutable = [=]() mutable
		{
			cout << "Capture by value with mutable specifier" << endl;

			// specifier로 mutable을 설정하면 value 타입의 변수라도
			// read/write 할 수 있습니다. 단, value 타입이므로 원본은 변경되지 않습니다.

			i++;
			f++;
			c++;
		};

		captureByValue();
		captureByRef();
		captureByVariableNames();
		captureByVariableRef();
		captureByMix();
		captureByValueMutable();

		cout << "i: " << i << endl;
		cout << "f: " << f << endl;
		cout << "c: " << c << endl;
	}
}