# COMP3200 실습 8

<br>
저희는 얼마 전 수업에서 std::vector나 std::map 같은 STL 컨테이너들이 얼마나 유용하게 쓰이는지 살펴봤습니다. 
STL 컨테이너들은 제네릭형으로 되어 있어서 이 템플릿 클래스의 인스턴스를 만들 때 자료형을 결정할 수 있습니다. 
예를 들어 int, float, double에 사용할 벡터 클래스를 따로 구현할 필요 없이 아래처럼 std::vector 템플릿 클래스의 인스턴스를 만들어 주면 되죠.
<br><br>

```C++
std::vector<int> intVector;
std::vector<float> floatVector;
std::vector<double> doubleVector;
```


이렇듯 std::vector는 매우 훌륭합니다만 한 가지 단점이 있습니다. 바로 요소를 추가할수록 메모리가 증가한다는 것이죠. 때로는 고정된 메모리를 사용하고 싶을 때도 있습니다. 그럴 때 단순 배열을 사용할 수도 있지만, 그러면 메모리나 현재 요소 개수를 나타내는 변수 등을 손수 관리해 줘야 해서 실수하기 쉽죠. 이런 문제들을 해결하기 위해 직접 FixedVector라는 클래스를 만들어 봅시다.

본 실습에서 여러분이 할 일은 다양한 벡터 연산에 사용될 C++ 템플릿 클래스 FixedVector<T, size_t N>와 특수화된 클래스 FixedVector<bool, size_t N>를 작성하는 것입니다.
