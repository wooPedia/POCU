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

		// vector keys, values를 합쳐 map<K, V>를 만든다.
		// K와 V는 기본 자료형만 사용한다.
		// 키가 중복될 경우 첫 번째 키만 허용한다.

		std::map<K, V> m;

		auto keysIter = keys.cbegin();
		auto valuesIter = values.cbegin();
		std::pair<typename std::map<K, V>::iterator, bool> pair;

		// 두 벡터 중 하나 이상 끝에 도달할 때 까지 반복합니다.
		while (keysIter != keys.end() && valuesIter != values.end())
		{
			pair = m.insert(std::pair<K, V>(*keysIter, *valuesIter));

			// insert가 성공할 경우
			if (pair.second)
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

		// map의 keys를 모두 벡터에 저장하여 반환

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

		// map의 values를 모두 벡터에 저장하여 반환

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

		// 벡터를 새 벡터에 역순으로 저장하여 반환합니다.

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

		// 두 벡터를 합쳐 반환합니다.
		// 합쳐진 벡터에 중복되는 값이 존재하지 않도록 합니다.
		std::vector<T> combined;
		std::map<T, char> filter;
		std::pair<typename std::map<T, char>::iterator, bool> pair;

		for (const auto& data : v1)
		{
			pair = filter.insert(std::pair<T, char>(data, NULL));
			if (!pair.second)
			{
				continue;
			}
			combined.push_back(data);
		}

		for (const auto& data : v2)
		{
			pair = filter.insert(std::pair<T, char>(data, NULL));
			if (!pair.second)
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

		// 두 맵을 합쳐 반환합니다.
		// 중복되는 키가 존재하면 안됩니다.
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
		auto iter = m.cbegin();

		for (const auto& data : m)
		{
			os << "{ " << data.first << ", " << data.second << " }" << std::endl;
		}

		return os;
	}
}