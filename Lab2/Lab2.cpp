#include <string>
#include <iomanip>

#include "Lab2.h"

using namespace std;

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		// ���� ����, ����, ���ڿ��� �Է¹���
		// �Է��� �ּ��� �ϳ��� ������ ������ ��
		// ���ڿ��� �����ؾ���

		// 12 11 9
		const string MY_OCT("oct");
		const string MY_DEC("dec");
		const string MY_HEX("hex");
		const size_t OCT_LENGTH = 12;
		const size_t DEC_LENGTH = 11;
		const size_t HEX_LENGTH = 9;

		int temp = 0;
		bool bIsFirst = true;
		while (true)
		{
			in >> temp;

			// eof �Է� ��
			if (in.eof())
			{
				// fail�� ��� eof�̹Ƿ� ���� 
				if (in.fail())
				{
					break;
				}
				// fail�� �ƴ� ��� ������ ���� �Է�
				else
				{
					if (temp < 0)
					{
						continue;
					}
					if (bIsFirst)
					{
						// ù°, ��° �� ���
						out << setw(OCT_LENGTH) << MY_OCT << setw(DEC_LENGTH) << MY_DEC << setw(HEX_LENGTH) << MY_HEX << endl;
						out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

						// ���� ��¿� �˸°� �ɼ� ����
						out << right << setfill(' ') << setw(0) << scientific << uppercase;
						bIsFirst = false;
					}

					out << oct << setw(OCT_LENGTH) << temp
						<< dec << setw(DEC_LENGTH) << temp
						<< hex << setw(HEX_LENGTH) << temp << endl;

					continue;
				}
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

			// 0�̸��� ��� �����մϴ�.
			if (temp < 0)
			{
				continue;
			}

			if (bIsFirst)
			{
				// ù°, ��° �� ���
				out << setw(OCT_LENGTH) << MY_OCT << setw(DEC_LENGTH) << MY_DEC << setw(HEX_LENGTH) << MY_HEX << endl;
				out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

				// ���� ��¿� �˸°� �ɼ� ����
				out << right << setfill(' ') << setw(0) << scientific << uppercase;
				bIsFirst = false;
			}

			out << oct << setw(OCT_LENGTH) << temp
				<< dec << setw(DEC_LENGTH) << temp
				<< hex << setw(HEX_LENGTH) << temp << endl;
		} // while
		in.clear();

		// �ɼ� ����
		out << setw(0) << fixed << nouppercase;
	}

	void PrintMaxFloat(std::istream& in, std::ostream& out)
	{
		const size_t FRONT_SPACES = 5;
		const size_t SECOND_SPACES = 15;

		out << showpos << showpoint << fixed << setprecision(3) << internal;

		float temp = 0.0f;
		float max = 0.0f;
		bool bIsFirst = true;
		while (true)
		{
			in >> temp;

			if (in.eof())
			{
				if (in.fail())
				{
					break;
				}
				else
				{
					if (bIsFirst)
					{
						max = temp;
						bIsFirst = false;
					}
					else
					{
						max = ((max > temp) ? max : temp);
					}

					out << setw(FRONT_SPACES) << " " << setw(SECOND_SPACES) << temp << endl;
					continue;
				}
			}

			if (in.fail())
			{
				in.clear();
				in.ignore(1, '\n');
				continue;
			}

			if (bIsFirst)
			{
				max = temp;
				bIsFirst = false;
			}
			else
			{
				max = ((max > temp) ? max : temp);
			}

			out << setw(FRONT_SPACES) << " " << setw(SECOND_SPACES) << temp << endl;
		}
		in.clear();

		// max ���
		out << left << setw(FRONT_SPACES) << "max:" << internal << setw(SECOND_SPACES) << max << endl;

		// ��� �ɼ� ����
		out << noshowpos << noshowpoint << setprecision(0) << right;
	}
}