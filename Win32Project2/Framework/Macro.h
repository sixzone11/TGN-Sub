#pragma once

#define SINGLETON_DEFINE(class_name)	static class_name* GetInstance() { static class_name instance; return &instance; }

// ACCESSOR
#define SET_ACCESSOR(n, x, y)       inline void Set##n(x t)	{ y = t; }
#define GET_ACCESSOR(n, x, y)       inline x Get##n()const	{ return y; }
#define GET_SET_ACCESSOR(n, x, y)   SET_ACCESSOR(n, x, y) GET_ACCESSOR(n, x, y)

#define SETP_ACCESSOR(n, x, y)      inline void Set##n(x* t)	{ y = *t; }
#define GETP_ACCESSOR(n, x, y)      inline x* Get##n()	{ return &y; }
#define GETP_SETP_ACCESSOR(n, x, y) SETP_ACCESSOR(n, x, y) GETP_ACCESSOR(n, x, y)

#define DEFINE_GET_SET_ACCESSOR(n, x, y)   private: x y; public: SET_ACCESSOR(n, x, y) public: GET_ACCESSOR(n, x, y)


#define SET_INTERFACE		= 0