#pragma once

template<class T>
class CGlobalRef
{
public:
	CGlobalRef(T*& p) : m_p(p)
	{
	}

	~CGlobalRef()
	{
		delete m_p;
		m_p = NULL;
	}

	CGlobalRef& operator=(T *p)
	{
		delete m_p;
		m_p = p;
		return *this;
	}
private:
	T*& m_p;
};
