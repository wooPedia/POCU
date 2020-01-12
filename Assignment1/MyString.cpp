#include "MyString.h"

namespace assignment1
{
	// �߰��� ������
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
		// �ش� ��ü�� ���ڿ��� ���ڷ� ���� ���ڿ��� �߰��մϴ�.

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
			1. this->mString�� ũ�� + other.mString�� ũ�� + 1('\0') ��ŭ�� newSize�� ����
			2. char* temp ���� �� newSize��ŭ �޸� �Ҵ�
			3. temp�� this->mString, other.mString �߰�
			4. �Լ� ���� �� temp ��ü�� �Ҹ��ڸ� ȣ���ϸ� mString�� �Ҵ�� �޸𸮸� ������ ����
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
		   �ش� ��ü�� ���ڿ��� s�� �����Ѵٸ� ù �ε����� ��ȯ�մϴ�.
		   ������ �����Ѵٸ� ó������ ������ ���� ù �ε����� ��ȯ�մϴ�.
		*/

		int thisSize = myStrlen(mString);
		int sSize = myStrlen(s);
		int ret = -1;

		// Ž�� ��� ���ڿ��� ũ�Ⱑ �� ũ�ٸ� -1 ��ȯ
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
			// ��ġ�ϴ� ���ڸ� ã���� ���
			if (mString[i] == s[j])
			{
				// j�� s�� ������ �ε����� ��� �Լ� ����
				if (j == sSize - 1)
				{
					ret = i - j;
					return ret;
				}
				else // ������ �ε����� �ƴ� ��� ���� ���� ��
				{
					++j;
					continue;
				}
			}

			// �� ���ǹ����� �Ϻθ� ��ġ���� ��� ������ ��ġ���� �� ����
			if (j > 0)
			{
				i = iTemp + 1;
				j = 0;
			}

			// �Ϻθ� ��ġ���� ��� ������ ���� ��ġ�� ���ƿ��� ���� ����
			iTemp = i;
		}

		return ret;
	}

	int MyString::LastIndexOf(const char* s)
	{
		/*
			�ش� ��ü�� ���ڿ��� s�� �����Ѵٸ� ù �ε����� ��ȯ�մϴ�.
			������ �����Ѵٸ� ���������� ������ ���� ù �ε����� ��ȯ�մϴ�.
		*/

		int thisSize = myStrlen(mString);
		int sSize = myStrlen(s);
		int ret = -1;

		// Ž�� ��� ���ڿ��� ũ�Ⱑ �� ũ�ٸ� -1 ��ȯ
		if (sSize > thisSize)
		{
			return ret;
		}
		if (sSize == 0)
		{
			return thisSize;
		}

		// Ž�� ���� ��ġ
		int iTemp = thisSize - 1;
		int     j = sSize - 1;

		// �������� Ž��
		for (int i = thisSize - 1; i >= 0; --i)
		{
			// ��ġ�ϴ� ���ڸ� ã���� ���
			if (mString[i] == s[j])
			{
				// j�� s�� ù �ε����� ��� i ��ȯ �� �Լ� ����
				if (j == 0)
				{
					ret = i;
					return ret;
				}
				else // ù �ε����� �ƴ� ��� ���� ���� ��
				{
					--j;
					continue;
				}
			}

			// �� ���ǹ����� �Ϻθ� ��ġ���� ��� ������ ��ġ���� �� ����
			if (j != sSize - 1)
			{
				i = iTemp - 1;
				j = sSize - 1;
			}

			// �Ϻθ� ��ġ���� ��� ������ ���� ��ġ�� ���ƿ��� ���� ����
			iTemp = i;
		}

		return ret;
	}

	void MyString::Interleave(const char* s)
	{
		/*
			��ü�� ����Ű�� ���ڿ��� s�� �ѱ��ھ� ������ ���� �����մϴ�.
			ex) abc, defgh -> adbecfgh
		*/

		size_t thisSize = myStrlen(mString);
		size_t sSize = myStrlen(s);
		// s�� ���ڿ��̶�� ���� ��ü�� ������ �ʽ��ϴ�.
		if (sSize == 0)
		{
			return;
		}
		else if (thisSize == 0)
		{
			// �Ҵ� ������ ȣ�� 
			*this = MyString(s);
			return;
		}

		size_t newSize = thisSize + sSize + 1;
		size_t smallerSize = (thisSize > sSize) ? sSize : thisSize;

		// mString�� temp�� ���� �� mString �޸� ���� �� newSize�� ���Ҵ�
		MyString temp = *this;
		deleteString(*this);
		this->mString = createString(newSize);

		// ���� ���� ������ŭ�� ���ڿ��� ���� �����մϴ�.
		size_t x = 0;
		size_t y = 0;
		for (size_t i = 0; i != smallerSize * 2; ++i)
		{
			// i�� ¦���� ���
			if ((i & 1) == 0)
			{
				mString[i] = temp.mString[x++];
			}
			else
			{
				mString[i] = s[y++];
			}
		}

		// ������ ���ڿ��� �߰��մϴ�.
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
		// index ��ġ�� ���ڸ� �����մϴ�.

		size_t thisSize = myStrlen(mString);
		if (index >= thisSize)
		{
			return false;
		}

		// �ӽ� ��ü�� �ش� ��ü�� ���� �� �ش� ��ü �޸� ���� �� ���Ҵ�
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
		// ���ڿ��� ���̰� totalLength�� �ǵ��� ���ʿ� ������ �߰��մϴ�.

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
		// ���ڿ��� ���̰� totalLength�� �ǵ��� ���ʿ� ���� c�� �߰��մϴ�.

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
		// ���ڿ��� ���̰� totalLength�� �ǵ��� �����ʿ� ������ �߰��մϴ�.

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
		// ���ڿ��� ���̰� totalLength�� �ǵ��� �����ʿ� ���� c�� �߰��մϴ�.

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
		// ���ڿ��� �������� �����մϴ�.

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
		// ���ڿ��� ��ġ ���θ� ��ȯ�մϴ�.

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
		// �Ҵ�(����) ������

		// �ڰ� �Ҵ��� ��� �ڱ� �ڽ��� ��ȯ�մϴ�.
		if (this == &rhs)
		{
			return *this;
		}

		// mString�� �޸𸮰� �Ҵ�Ǿ��� ��� ����
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
		// ���ڿ��� �빮�ڸ� ��� �ҹ��ڷ� �����մϴ�.

		size_t thisSize = myStrlen(mString);
		for (size_t i = 0; i != thisSize; ++i)
		{
			// 'A'~'Z'�� ���
			if (mString[i] >= 65 && mString[i] <= 90)
			{
				mString[i] = static_cast<char>(mString[i] + 32);
			}
		}
	}

	void MyString::ToUpper()
	{
		// ���ڿ��� �ҹ��ڸ� ��� �빮�ڷ� �����մϴ�.

		size_t thisSize = myStrlen(mString);
		for (size_t i = 0; i != thisSize; ++i)
		{
			// 'a'~'z'�� ���
			if (mString[i] >= 97 && mString[i] <= 122)
			{
				mString[i] = static_cast<char>(mString[i] - 32);
			}
		}
	}


	/*
		�߰��� private �Լ�
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