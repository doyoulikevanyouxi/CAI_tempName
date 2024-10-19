//���ļ������˿ؼ��������ֶ�
//��Щ��涨�˿ؼ�����Ӧ�������������Ͳ��ң���ע�ᵽһ��ϵͳ�н��й���

#pragma once
#include "Object.h"
class Property : public Object
{
public:
	Property() noexcept { invalid = true; }
};

template<typename _Ty>
class DependencyProperty : public Property {
public:
	DependencyProperty() = delete;
	DependencyProperty(const std::string& name) noexcept:name(name) {}
public:
	void set(const _Ty& value) noexcept { this->value = value; invalid = false; }
	_Ty& get() const noexcept{ return value; }
public:
	DependencyProperty<_Ty>& operator=(const _Ty& value) { this->value = value; return *this; }
private:
	mutable _Ty value;
	std::string name;
};

template<typename _Ty>
class AttachedProperty : public Property {
public:
	AttachedProperty() = delete;
	AttachedProperty(const std::string& name) noexcept :name(name) {}
public:
	void set(const _Ty& value) noexcept { this->value = value; invalid = false; }
	_Ty& get() const noexcept { return value; }
public:
	_Ty& Value() { return value; }
private:
	mutable _Ty value;
	std::string name;
};