#pragma once

template<typename T>
void SafeDelete(T*& p)
{
	if (p == nullptr) return;

	delete p;
	p = nullptr;
}

template<typename T>
void SageDelete_Array(T*& p)
{
	if (p == nullptr) return;

	delete[] p;
	p = nullptr;
}