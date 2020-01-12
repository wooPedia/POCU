#include "MyString.h"

namespace assignment1
{
	// 추가한 생성자
	MyString::MyString(size_t size)
	{
		// default argument: 0

		mString = createString(size);
	}

	MyString::MyString(const char* s)
	{
		if (s == nullptr)
		{
			s = "";
		}

		size_t size = myStrlen(s) + 1;
		mString = createString(size);

		myMemcpy(mString, s, size);
	}

	MyString::MyString(const MyString& other)
	{
		// Copy constructor

		const size_t size = other.GetLength() + 1;
		mString = createString(size);

		myMemcpy(mString, other.mString, size);
	}

	MyString::~MyString()
	{
		// deallocate this->mString  

		deleteString(*this);
	}

	unsigned int MyString::GetLength() const
	{
		return myStrlen(mString);
	}

	const char* MyString::GetCString() const
	{
		// return a string

		if (mString != nullptr)
		{
			return mString;
		}
		else
		{
			return "";
		}
	}

	void MyString::Append(const char* s)
	{
		// 해당 객체의 문자열에 인자로 받은 문자열을 추가합니다.

		if (mString == nullptr || s == nullptr)
		{
			return;
		}

		size_t sSize = myStrlen(s);
		if (sSize == 0)
		{
			return;
		}
		size_t thisSize = GetLength();
		size_t newSize = thisSize + sSize + 1;

		MyString temp(mString);
		deleteString(*this);

		mString = createString(newSize);
		myMemcpy(mString, temp.mString, thisSize);
		myMemcpy(mString + thisSize, s, sSize + 1);
	}

	MyString MyString::operator+(const MyString& other) const
	{
		/*
			1. this->mString의 크기 + other.mString의 크기 + 1('\0') 만큼을 newSize로 만듦
			2. char* temp 생성 후 newSize만큼 메모리 할당
			3. temp에 this->mString, other.mString 추가
			4. 함수 종료 시 temp 객체가 소멸자를 호출하며 mString에 할당된 메모리를 해제할 것임
		*/
		size_t thisSize = myStrlen(this->mString);
		size_t otherSize = myStrlen(other.mString);
		size_t newSize = thisSize + otherSize + 1;

		MyString temp(newSize);

		myMemcpy(temp.mString, this->mString, thisSize);
		myMemcpy(temp.mString + thisSize, other.mString, otherSize + 1);

		return MyString(temp.GetCString());
	}

	int MyString::IndexOf(const char* s)
	{
		/*
		   해당 객체의 문자열이 s를 포함한다면 첫 인덱스를 반환합니다.
		   여러번 등장한다면 처음으로 등장한 곳의 첫 인덱스를 반환합니다.
		*/

		int thisSize = myStrlen(mString);
		int sSize = myStrlen(s);
		int ret = -1;

		// 탐색 대상 문자열의 크기가 더 크다면 -1 반환
		if (sSize > thisSize)
		{
			return ret;
		}
		if (sSize == 0)
		{
			return 0;
		}

		int iTemp = 0;
		int     j = 0;

		for (int i = 0; i != thisSize; ++i)
		{
			// 일치하는 문자를 찾았을 경우
			if (mString[i] == s[j])
			{
				// j가 s의 마지막 인덱스일 경우 함수 종료
				if (j == sSize - 1)
				{
					ret = i - j;
					return ret;
				}
				else // 마지막 인덱스가 아닐 경우 다음 문자 비교
				{
					++j;
					continue;
				}
			}

			// 위 조건문에서 일부만 일치했을 경우 적절한 위치부터 비교 시작
			if (j > 0)
			{
				i = iTemp + 1;
				j = 0;
			}

			// 일부만 일치했을 경우 적절한 시작 위치로 돌아오기 위한 변수
			iTemp = i;
		}

		return ret;
	}

	int MyString::LastIndexOf(const char* s)
	{
		/*
			해당 객체의 문자열이 s를 포함한다면 첫 인덱스를 반환합니다.
			여러번 등장한다면 마지막으로 등장한 곳의 첫 인덱스를 반환합니다.
		*/

		int thisSize = myStrlen(mString);
		int sSize = myStrlen(s);
		int ret = -1;

		// 탐색 대상 문자열의 크기가 더 크다면 -1 반환
		if (sSize > thisSize)
		{
			return ret;
		}
		if (sSize == 0)
		{
			return thisSize;
		}

		// 탐색 시작 위치
		int iTemp = thisSize - 1;
		int     j = sSize - 1;

		// 역순으로 탐색
		for (int i = thisSize - 1; i >= 0; --i)
		{
			// 일치하는 문자를 찾았을 경우
			if (mString[i] == s[j])
			{
				// j가 s의 첫 인덱스일 경우 i 반환 후 함수 종료
				if (j == 0)
				{
					ret = i;
					return ret;
				}
				else // 첫 인덱스가 아닐 경우 다음 문자 비교
				{
					--j;
					continue;
				}
			}

			// 위 조건문에서 일부만 일치했을 경우 적절한 위치부터 비교 시작
			if (j != sSize - 1)
			{
				i = iTemp - 1;
				j = sSize - 1;
			}

			// 일부만 일치했을 경우 적절한 시작 위치로 돌아오기 위한 변수
			iTemp = i;
		}

		return ret;
	}

	void MyString::Interleave(const char* s)
	{
		/*
			객체가 가리키는 문자열과 s를 한글자씩 번갈아 가며 결합합니다.
			ex) abc, defgh -> adbecfgh
		*/

		size_t thisSize = myStrlen(mString);
		size_t sSize = myStrlen(s);
		// s가 빈문자열이라면 현재 객체는 변하지 않습니다.
		if (sSize == 0)
		{
			return;
		}
		else if (thisSize == 0)
		{
			// 할당 연산자 호출 
			*this = MyString(s);
			return;
		}

		size_t newSize = thisSize + sSize + 1;
		size_t smallerSize = (thisSize > sSize) ? sSize : thisSize;

		// mString을 temp에 복사 후 mString 메모리 해제 후 newSize로 재할당
		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(newSize);

		// 먼저 같은 개수만큼의 문자열만 서로 결합합니다.
		size_t x = 0;
		size_t y = 0;
		for (size_t i = 0; i != smallerSize * 2; ++i)
		{
			// i가 짝수일 경우
			if ((i & 1) == 0)
			{
				mString[i] = temp.mString[x++];
			}
			else
			{
				mString[i] = s[y++];
			}
		}

		// 나머지 문자열을 추가합니다.
		if (thisSize > sSize)
		{
			for (size_t i = smallerSize * 2; i < newSize; ++i)
			{
				mString[i] = temp.mString[x++];
			}
		}
		else if (thisSize < sSize)
		{
			for (size_t i = smallerSize * 2; i < newSize; ++i)
			{
				mString[i] = s[y++];
			}
		}
		else
		{
			mString[newSize - 1] = '\0';
		}
	}

	bool MyString::RemoveAt(unsigned int index)
	{
		// index 위치의 문자를 제거합니다.

		size_t thisSize = myStrlen(mString);
		if (index >= thisSize)
		{
			return false;
		}

		// 임시 객체에 해당 객체를 복사 후 해당 객체 메모리 해제 및 재할당
		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(thisSize);

		for (size_t i = 0; i != thisSize; ++i)
		{
			if (i < index)
			{
				mString[i] = temp.mString[i];
			}
			else
			{
				mString[i] = temp.mString[i + 1];
			}
		}

		return true;
	}

	void MyString::PadLeft(unsigned int totalLength)
	{
		// 문자열의 길이가 totalLength가 되도록 왼쪽에 공백을 추가합니다.

		size_t thisSize = myStrlen(mString);
		if (thisSize >= totalLength)
		{
			return;
		}
		size_t addedSize = totalLength - thisSize;
		size_t newSize = totalLength + 1;

		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(newSize);

		size_t x = 0;
		for (size_t i = 0; i != newSize; ++i)
		{
			if (i < addedSize)
			{
				mString[i] = ' ';
			}
			else
			{
				mString[i] = temp.mString[x++];
			}
		}
	}

	void MyString::PadLeft(unsigned int totalLength, const char c)
	{
		// 문자열의 길이가 totalLength가 되도록 왼쪽에 문자 c를 추가합니다.

		size_t thisSize = myStrlen(mString);
		if (thisSize >= totalLength)
		{
			return;
		}
		size_t addedSize = totalLength - thisSize;
		size_t newSize = totalLength + 1;

		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(newSize);

		size_t x = 0;
		for (size_t i = 0; i != newSize; ++i)
		{
			if (i < addedSize)
			{
				mString[i] = c;
			}
			else
			{
				mString[i] = temp.mString[x++];
			}
		}
	}

	void MyString::PadRight(unsigned int totalLength)
	{
		// 문자열의 길이가 totalLength가 되도록 오른쪽에 공백을 추가합니다.

		size_t thisSize = myStrlen(mString);
		if (thisSize >= totalLength)
		{
			return;
		}
		size_t newSize = totalLength + 1;

		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(newSize);

		size_t x = 0;
		for (size_t i = 0; i != newSize - 1; ++i)
		{
			if (i < thisSize)
			{
				mString[i] = temp.mString[x++];
			}
			else
			{
				mString[i] = ' ';
			}
		}
		mString[newSize - 1] = '\0';
	}

	void MyString::PadRight(unsigned int totalLength, const char c)
	{
		// 문자열의 길이가 totalLength가 되도록 오른쪽에 문자 c를 추가합니다.

		size_t thisSize = myStrlen(mString);
		if (thisSize >= totalLength)
		{
			return;
		}
		size_t newSize = totalLength + 1;

		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(newSize);

		size_t x = 0;
		for (size_t i = 0; i != newSize - 1; ++i)
		{
			if (i < thisSize)
			{
				mString[i] = temp.mString[x++];
			}
			else
			{
				mString[i] = c;
			}
		}
		mString[newSize - 1] = '\0';
	}

	void MyString::Reverse()
	{
		// 문자열을 역순으로 변경합니다.

		size_t size = myStrlen(mString);
		size_t num = size / 2;

		char temp;
		for (int i = 0; i != num; ++i)
		{
			temp = mString[i];
			mString[i] = mString[size - (i + 1)];
			mString[size - (i + 1)] = temp;
		}
	}

	bool MyString::operator==(const MyString& rhs) const
	{
		// 문자열의 일치 여부를 반환합니다.

		size_t thisSize = myStrlen(mString);
		size_t rhsSize = myStrlen(rhs.mString);

		if (thisSize != rhsSize)
		{
			return false;
		}

		for (int i = 0; i != thisSize; ++i)
		{
			if (mString[i] != rhs.mString[i])
			{
				return false;
			}
		}

		return true;
	}

	MyString& MyString::operator=(const MyString& rhs)
	{
		// 할당(대입) 연산자

		// 자가 할당일 경우 자기 자신을 반환합니다.
		if (this == &rhs)
		{
			return *this;
		}

		// mString에 메모리가 할당되었을 경우 해제
		if (this->mString != nullptr)
		{
			deleteString(*this);
		}

		const size_t newSize = rhs.GetLength() + 1;
		this->mString = createString(newSize);
		myMemcpy(mString, rhs.mString, newSize);

		return *this;
	}

	void MyString::ToLower()
	{
		// 문자열의 대문자를 모두 소문자로 변경합니다.

		size_t thisSize = myStrlen(mString);
		for (size_t i = 0; i != thisSize; ++i)
		{
			// 'A'~'Z'일 경우
			if (mString[i] >= 65 && mString[i] <= 90)
			{
				mString[i] = static_cast<char>(mString[i] + 32);
			}
		}
	}

	void MyString::ToUpper()
	{
		// 문자열의 소문자를 모두 대문자로 변경합니다.

		size_t thisSize = myStrlen(mString);
		for (size_t i = 0; i != thisSize; ++i)
		{
			// 'a'~'z'일 경우
			if (mString[i] >= 97 && mString[i] <= 122)
			{
				mString[i] = static_cast<char>(mString[i] - 32);
			}
		}
	}


	/*
		추가한 private 함수
	*/

	char* MyString::createString(size_t size)
	{
		return new char[size];
	}

	void MyString::deleteString(MyString& obj)
	{
		if (obj.mString != nullptr)
		{
			delete[] obj.mString;
		}
	}

	char* MyString::myMemcpy(char* destination, const char* source, size_t num)
	{
		for (int i = 0; i != num; ++i)
		{
			destination[i] = source[i];
		}

		return destination;
	}

	char* MyString::myMemcpy(char* destination, const char* source, size_t num) const
	{
		for (int i = 0; i != num; ++i)
		{
			destination[i] = source[i];
		}

		return destination;
	}

	size_t MyString::myStrlen(const char* s) const
	{
		size_t i = 0;
		while (s[i] != '\0')
		{
			++i;
		}

		return i;
	}

}