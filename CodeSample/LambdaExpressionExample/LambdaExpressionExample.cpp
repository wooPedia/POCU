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
				�Ʒ� �ڵ�� ������ ������ �߻���ŵ�ϴ�.
				���� �Լ� ���ο��� ����� �������� �Ǵ� �Ű����� �Ǵ� 
				ĸ�� ���� �ִ� ������ read �����մϴ�.
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
				�Ʒ� �ڵ�� ������ ������ �߻���ŵ�ϴ�.
				ĸ�� ���� '='�� ���ٽ��� ���� scope�� ��� ���� ������
				����ϵ�, value Ÿ������ ����� ���̸� read only�Դϴ�.
			*/

			//i++;
			//f = 2.0f;
			//c = 'a';
		};

		auto captureByRef = [&]()
		{
			/*
				ĸ�� ���� '&'�� ���ٽ��� ���� scope�� ��� ���� ������
				���� Ÿ������ set�Ǹ� read/write ��� �����մϴ�.
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
				�Ʒ� �ڵ�� ������ ������ �߻���ŵ�ϴ�.
				ĸ�� ���� ���Ե� ������ ��� read only�� value Ÿ���Դϴ�.
			*/

			//i++;
			//f++;
		};

		auto captureByVariableRef = [&i, &f]()
		{
			cout << "Capture by variable names reference:" << endl;

			// ĸ�� ���� ���Ե��� ���� ������ ���� �� �����ϴ�.
			//cout << "c: " << c << endl;


			// ������ �����Ƿ� read/write �����մϴ�.
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

			// �⺻������ ��� ���� ������ read only�� value Ÿ������ ������
			// f, c�� ���ؼ� read/write ������ ���� Ÿ������ �޽��ϴ�.

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

			// specifier�� mutable�� �����ϸ� value Ÿ���� ������
			// read/write �� �� �ֽ��ϴ�. ��, value Ÿ���̹Ƿ� ������ ������� �ʽ��ϴ�.

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