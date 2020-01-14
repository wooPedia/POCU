#include <string>
#include <iomanip>
#include <sstream>

#include "Lab2.h"

using namespace std;

namespace lab2
{
	void PrintIntegers(std::istream& in, std::ostream& out)
	{
		// 양의 정수, 공백, 문자열만 입력받음
		// 입력은 최소한 하나의 정수가 존재할 것
		// 문자열은 무시해야함

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

			// eof 입력 시 입력 종료
			if (in.eof())
			{
				break;
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

			// 양의 정수가 아닐 경우 무시합니다.
			if (temp < 1)
			{
				//// 개행없이 EOF가 입력될 경우 멈춥니다.
				//if (temp == 0)
				//{
				//	break;
				//}
				continue;
			}

			//if (isFirst)
			//{
			//	// 첫째, 둘째 줄 출력
			//	out << setw(OCT_LENGTH) << myOCT << setw(DEC_LENGTH) << myDEC << setw(HEX_LENGTH) << myHEX << endl;
			//	out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

			//	// 다음 출력에 알맞게 옵션 설정
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
		// 첫째, 둘째 줄 출력
		out << setw(OCT_LENGTH) << myOCT << setw(DEC_LENGTH) << myDEC << setw(HEX_LENGTH) << myHEX << endl;
		out << setfill('-') << setw(OCT_LENGTH) << "" << left << setw(DEC_LENGTH) << " " << setw(HEX_LENGTH) << " " << endl;

		// 다음 출력에 알맞게 옵션 설정
		out << right << setfill(' ') << setw(0) << scientific << uppercase;
		for (int i = 0; i != currentSize; ++i)
		{
			out << oct << setw(OCT_LENGTH) << number[i]
				<< dec << setw(DEC_LENGTH) << number[i]
				<< hex << setw(HEX_LENGTH) << number[i] << endl;
		}

		// 옵션 리셋
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

		// 출력 옵션 설정
		//cout << showpos << showpoint << fixed << setprecision(3) << internal;

		// max 제외 출력 부분
		/*for (int i = 0; i != currentSize; ++i)
		{
			cout << setw(FRONT_SPACES) << " " << setw(SECOND_SPACES) << myDecimal[i] << endl;
			max = ((max > myDecimal[i]) ? max : myDecimal[i]);
		}*/

		// max 출력
		buffer << left << setw(FRONT_SPACES) << "max:" << internal << setw(SECOND_SPACES) << max << endl;
		out << buffer.str();

		// 출력 옵션 리셋
		out << noshowpos << noshowpoint << setprecision(0) << right;
	}
}