#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <type_traits>

namespace lab7
{
	template <typename K, class V>
	std::map<K, V> ConvertVectorsToMap(const std::vector<K>& keys, const std::vector<V>& values)
	{
		static_assert(std::is_fundamental<K>::value && std::is_fundamental<V>::value, "Type K, V must be primitive type");

		// keys�� values�� map���� ���� ��ȯ�մϴ�.
		// Ű�� �ߺ��� ��� ù ��° Ű�� ����մϴ�.

		std::map<K, V> m;
		auto keysIter = keys.cbegin();
		auto valuesIter = values.cbegin();
		std::pair<typename std::map<K, V>::iterator, bool> bPair;

		// �� ���� �� �ϳ� �̻� ���� ������ �� ���� �ݺ��մϴ�.
		while (keysIter != keys.end() && valuesIter != values.end())
		{
			bPair = m.insert(std::pair<K, V>(*keysIter, *valuesIter));

			// insert�� ������ ���
			if (bPair.second)
			{
				++valuesIter;
			}
			++keysIter;
		}

		return m;
	}

	template <typename K, class V>
	std::vector<K> GetKeys(const std::map<K, V>& m)
	{
		static_assert(std::is_fundamental<K>::value && std::is_fundamental<V>::value, "Type K, V must be primitive type");

		// map�� keys�� ��� ���Ϳ� �����Ͽ� ��ȯ�մϴ�.

		std::vector<K> v;
		v.reserve(m.size());

		for (const auto& data : m)
		{
			v.push_back(data.first);
		}

		return v;
	}

	template <typename K, class V>
	std::vector<V> GetValues(const std::map<K, V>& m)
	{
		static_assert(std::is_fundamental<K>::value && std::is_fundamental<V>::value, "Type K, V must be primitive type");

		// map�� values�� ��� ���Ϳ� �����Ͽ� ��ȯ�մϴ�.

		std::vector<V> v;
		v.reserve(m.size());

		for (const auto& data : m)
		{
			v.push_back(data.second);
		}

		return v;
	}

	template <typename T>
	std::vector<T> Reverse(const std::vector<T>& v)
	{
		static_assert(std::is_fundamental<T>::value, "Type T must be primitive type");

		// ���͸� �� ���Ϳ� �������� �����Ͽ� ��ȯ�մϴ�.

		std::vector<T> rv;
		rv.reserve(v.size());

		auto rBeginIter = v.crbegin();
		while (rBeginIter != v.crend())
		{
			rv.push_back(*rBeginIter);
			++rBeginIter;
		}

		return rv;
	}

	template <typename T>
	std::vector<T> operator+(const std::vector<T>& v1, const std::vector<T>& v2)
	{
		static_assert(std::is_fundamental<T>::value, "Type T must be primitive type");

		// �� ���͸� ���� ��ȯ�մϴ�.
		// ������ ���Ϳ� �ߺ��Ǵ� ���� �������� �ʵ��� �մϴ�.
		std::vector<T> combined;
		std::map<T, char> filter;
		std::pair<typename std::map<T, char>::iterator, bool> bPair;

		for (const auto& data : v1)
		{
			bPair = filter.insert(std::pair<T, char>(data, NULL));
			if (!bPair.second)
			{
				continue;
			}
			combined.push_back(data);
		}

		for (const auto& data : v2)
		{
			bPair = filter.insert(std::pair<T, char>(data, NULL));
			if (!bPair.second)
			{
				continue;
			}
			combined.push_back(data);
		}

		return combined;
	}

	template <typename K, class V>
	std::map<K, V> operator+(const std::map<K, V>& m1, const std::map<K, V>& m2)
	{
		static_assert(std::is_fundamental<K>::value && std::is_fundamental<V>::value, "Type K, V must be primitive type");

		// �� ���� ���� ��ȯ�մϴ�.
		// �ߺ��Ǵ� Ű�� �����ϸ� �ȵ˴ϴ�.
		std::map<K, V> combined;

		for (const auto& data : m1)
		{
			combined.insert(std::pair<K, V>(data.first, data.second));
		}

		for (const auto& data : m2)
		{
			combined.insert(std::pair<K, V>(data.first, data.second));
		}

		return combined;
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
	{
		static_assert(std::is_fundamental<T>::value, "Type T must be primitive type");

		auto iter = v.cbegin();
		while (iter != v.end() - 1)
		{
			os << *(iter++) << ", ";
		}

		return os << *iter;
	}

	template <typename K, class V>
	std::ostream& operator<<(std::ostream& os, const std::map<K, V>& m)
	{
		static_assert(std::is_fundamental<K>::value && std::is_fundamental<V>::value, "Type K, V must be primitive type");

		auto iter = m.cbegin();
		for (const auto& data : m)
		{
			os << "{ " << data.first << ", " << data.second << " }" << std::endl;
		}

		return os;
	}
}