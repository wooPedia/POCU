#include <string>
#include <iomanip>
#include <sstream>

#include "Lab2.h"

using namespace std;

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		// ���� ����, ����, ���ڿ��� �Է¹���
		// �Է��� �ּ��� �ϳ��� ������ ������ ��
		// ���ڿ��� �����ؾ���

		int number[1000];
		size_t currentSize = 0;
		size_t i = 0;

		// 12 11 9
		const string myOCT("oct");
		const string myDEC("dec");
		const string myHEX("hex");
		const size_t OCT_LENGTH = 12;
		const size_t DEC_LENGTH = 11;
		const size_t HEX_LENGTH = 9;

		//stringstream buffer;
		//buffer << setw(OCT_LENGTH) << myOCT << setw(DEC_LENGTH) << myDEC << setw(HEX_LENGTH) << myHEX << endl;
		//buffer << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;
		//buffer << right << setfill(' ') << setw(0) << scientific << uppercase;

		int temp = 0;
		//bool isFirst = true;
		while (true)
		{
			in >> temp;

			// eof �Է� �� �Է� ����
			if (in.eof())
			{
				break;
			}

			// �˸��� �ʴ� ���� �Է� �� 
			if (in.fail())
			{
				// �Է� ��Ʈ���� ���ϴ�.
				in.clear();

				// ���ڴ� ��� �����մϴ�.
				in.ignore(1, '\n');
				continue;
			}

			// ���� ������ �ƴ� ��� �����մϴ�.
			if (temp < 1)
			{
				//// ������� EOF�� �Էµ� ��� ����ϴ�.
				//if (temp == 0)
				//{
				//	break;
				//}
				continue;
			}

			//if (isFirst)
			//{
			//	// ù°, ��° �� ���
			//	out << setw(OCT_LENGTH) << myOCT << setw(DEC_LENGTH) << myDEC << setw(HEX_LENGTH) << myHEX << endl;
			//	out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

			//	// ���� ��¿� �˸°� �ɼ� ����
			//	out << right << setfill(' ') << setw(0) << scientific << uppercase;
			//	isFirst = false;
			//}

			//buffer << oct << setw(OCT_LENGTH) << temp
			//	<< dec << setw(DEC_LENGTH) << temp
			//	<< hex << setw(HEX_LENGTH) << temp << endl;
			//out << oct << setw(OCT_LENGTH) << temp
			//	<< dec << setw(DEC_LENGTH) << temp
			//	<< hex << setw(HEX_LENGTH) << temp << endl;

			number[i] = temp;
			++i;
			++currentSize;
		} // while
		in.clear();

		//std::cout << buffer.str();
		// ù°, ��° �� ���
		out << setw(OCT_LENGTH) << myOCT << setw(DEC_LENGTH) << myDEC << setw(HEX_LENGTH) << myHEX << endl;
		out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

		// ���� ��¿� �˸°� �ɼ� ����
		out << right << setfill(' ') << setw(0) << scientific << uppercase;
		for (int i = 0; i != currentSize; ++i)
		{
			out << oct << setw(OCT_LENGTH) << number[i]
				<< dec << setw(DEC_LENGTH) << number[i]
				<< hex << setw(HEX_LENGTH) << number[i] << endl;
		}

		// �ɼ� ����
		out << setw(0) << fixed << nouppercase;
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		const size_t FRONT_SPACES = 5;
		const size_t SECOND_SPACES = 15;

		//float myDecimal[1000];
		//size_t currentSize = 0;
		//size_t i = 0;

		stringstream buffer;
		buffer << showpos << showpoint << fixed << setprecision(3) << internal;


		float temp = 0.0f;
		float max = 0.0f;
		while (true)
		{
			in >> temp;

			if (in.eof())
			{
				break;
			}

			if (in.fail())
			{
				in.clear();
				in.ignore(1, '\n');
				continue;
			}

			buffer << setw(FRONT_SPACES) << " " << setw(SECOND_SPACES) << temp << endl;
			max = ((max > temp) ? max : temp);
			/*myDecimal[i] = temp;
			++i;
			++currentSize;*/
		}
		in.clear();

		// ��� �ɼ� ����
		//cout << showpos << showpoint << fixed << setprecision(3) << internal;

		// max ���� ��� �κ�
		/*for (int i = 0; i != currentSize; ++i)
		{
			cout << setw(FRONT_SPACES) << " " << setw(SECOND_SPACES) << myDecimal[i] << endl;
			max = ((max > myDecimal[i]) ? max : myDecimal[i]);
		}*/

		// max ���
		buffer << left << setw(FRONT_SPACES) << "max:" << internal << setw(SECOND_SPACES) << max << endl;
		out << buffer.str();

		// ��� �ɼ� ����
		out << noshowpos << noshowpoint << setprecision(0) << right;
	}
}