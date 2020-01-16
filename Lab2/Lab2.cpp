#include <string>
#include <iomanip>

#include "Lab2.h"

using namespace std;

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		// 양의 정수, 공백, 문자열만 입력받음
		// 입력은 최소한 하나의 정수가 존재할 것
		// 문자열은 무시해야함

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

			// eof 입력 시
			if (in.eof())
			{
				// fail일 경우 eof이므로 종료 
				if (in.fail())
				{
					break;
				}
				// fail이 아닐 경우 뉴라인 없는 입력
				else
				{
					if (temp < 0)
					{
						continue;
					}
					if (bIsFirst)
					{
						// 첫째, 둘째 줄 출력
						out << setw(OCT_LENGTH) << MY_OCT << setw(DEC_LENGTH) << MY_DEC << setw(HEX_LENGTH) << MY_HEX << endl;
						out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

						// 다음 출력에 알맞게 옵션 설정
						out << right << setfill(' ') << setw(0) << scientific << uppercase;
						bIsFirst = false;
					}

					out << oct << setw(OCT_LENGTH) << temp
						<< dec << setw(DEC_LENGTH) << temp
						<< hex << setw(HEX_LENGTH) << temp << endl;

					continue;
				}
			}

			// 알맞지 않는 형식 입력 시 
			if (in.fail())
			{
				// 입력 스트림을 비웁니다.
				in.clear();

				// 문자는 모두 무시합니다.
				in.ignore(1, '\n');
				continue;
			}

			// 0미만일 경우 무시합니다.
			if (temp < 0)
			{
				continue;
			}

			if (bIsFirst)
			{
				// 첫째, 둘째 줄 출력
				out << setw(OCT_LENGTH) << MY_OCT << setw(DEC_LENGTH) << MY_DEC << setw(HEX_LENGTH) << MY_HEX << endl;
				out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

				// 다음 출력에 알맞게 옵션 설정
				out << right << setfill(' ') << setw(0) << scientific << uppercase;
				bIsFirst = false;
			}

			out << oct << setw(OCT_LENGTH) << temp
				<< dec << setw(DEC_LENGTH) << temp
				<< hex << setw(HEX_LENGTH) << temp << endl;
		} // while
		in.clear();

		// 옵션 리셋
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

		// max 출력
		out << left << setw(FRONT_SPACES) << "max:" << internal << setw(SECOND_SPACES) << max << endl;

		// 출력 옵션 리셋
		out << noshowpos << noshowpoint << setprecision(0) << right;
	}
}