#ifndef PRAC_CPP_H
#define PRAC_CPP_H

#include "forwards.h"
#include "config.h"
#include <vector>
#include <string>
#include <map>
#define USE_WEITM_API 1
#if USE_WEITM_API == 1
#include <map>
#else
# include <_dbdao.h>
#endif

#define WEITM_API
namespace weitm{
	enum eValueType{
		intvalue = 0,
		stringValue = 1,
		objValue = 2,
		nullValue =3
	};
	enum eCommentType{
		BEFORE = 0,
		AFTER,
		MIDDLE
	};

	class WEITM_API staticString
	{
	public:
		explicit staticString(const char *str):_str(str)
		{
			
		}

		operator const char* () const {return _str;}

	private:
		const char *_str;
	};

	class WEITM_API Value
	{
	public:
		typedef int Int;
		typedef unsigned int UInt;
		typedef std::vector<std::string> members;
		typedef std::map<std::string, Value> ObjectValues;
		Value(eValueType t):_type(t)
		{
			switch(t)
			{
			case intvalue:
				_value._int = 0;
			case stringValue:
				_value._str = 0;
			}
		}

	private:
		struct CommentInfo
		{
			CommentInfo();
			~CommentInfo();
			void setComment(char * c);
			char *_comment;
		};

		union ValueHolder
		{
			Int _int;
			UInt _uint;
			double _dbl;
			float _float;
			bool  _bool;
			char * _str;
			ObjectValues *map; // must be pointer
		} _value;
		eValueType _type:8;  // byte field is 8
		int allocated:1;
		CommentInfo *_comment;

	};
}

#endif