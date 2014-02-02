#pragma once

#define SINGLETON_DEFINE(class_name)	static class_name* GetInstance() { static class_name instance; return &instance; }

// ACCESSOR
#define SET_ACCESSOR(n, t, mv)			inline void Set##n(t p)		{ mv = p; }
#define GET_ACCESSOR(n, t, mv)			inline t Get##n()const		{ return mv; }
#define GET_SET_ACCESSOR(n, t, mv)		SET_ACCESSOR(n, t, mv) GET_ACCESSOR(n, t, mv)

#define IS_ACCESSOR(n, t, mv)			inline t Is##n()const		{ return mv; }
#define IS_SET_ACCESSOR(n, t, mv)		SET_ACCESSOR(n, t, mv) IS_ACCESSOR(n, t, mv)

#define SETP_ACCESSOR(n, pt, mv)		inline void Set##n(pt* p)	{ mv = *p; }
#define GETP_ACCESSOR(n, pt, mv)		inline pt* Get##n()			{ return &mv; }
#define GETP_SETP_ACCESSOR(n, pt, mv)	SETP_ACCESSOR(n, pt, mv) GETP_ACCESSOR(n, pt, mv)

#define ISP_ACCESSOR(n, pt, mv)			inline pt* Is##n()			{ return &mv; }
#define ISP_SETP_ACCESSOR(n, pt, mv)	SETP_ACCESSOR(n, pt, mv) ISP_ACCESSOR(n, pt, mv)

#define DEFINE_GET_SET_ACCESSOR(n, t, mv)		private: t mv; public: GET_SET_ACCESSOR(n, t, mv)
#define DEFINE_IS_SET_ACCESSOR(n, t, mv)		private: t mv; public: IS_SET_ACCESSOR(n, t, mv)
#define DEFINE_P_GET_SET_ACCESSOR(n, pt, mv)	private: pt* mv; public: GETP_SETP_ACCESSOR(n, pt, mv)
#define DEFINE_P_IS_SET_ACCESSOR(n, pt, mv)		private: pt* mv; public: ISP_SETP_ACCESSOR(n, pt, mv)

#define SET_INTERFACE		= 0