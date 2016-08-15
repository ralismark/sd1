#pragma once

#include <typeinfo>
#include <ostream>
#include <windows.h>

// All of this stuff is windows-only and might break at any point
namespace cxx_except
{
	// http://www.codeproject.com/Articles/175482/Compiler-Internals-How-Try-Catch-Throw-are-Interpr
	// http://members.gamedev.net/sicrane/articles/exception.html

	typedef void (__cdecl * _PMFN)(void); // despite the static typing, function pointers of 
	//   type _PMFN are usually used as pointers to other
	//   function types

	struct _PMD {
		int mdisp;  // member offset
		int pdisp;  // offset of the vtable 
		int vdisp;  // offset to displacment inside the vtable
	};

	struct _ctype {
		unsigned int      props;       // bit 1: is a simple type
		//   bit 2: can be caught by reference only
		//   bit 3: has virtual base
		std::type_info * pType;        // pointer to std::type_info object.
		_PMD             displacement; // displacement of the object for this type
		int              size;         // size of the type
		_PMFN            copy_ctor;    // pointer to copy constructor or 0
	};

	struct _ctypeArray {
		int              size;         // number of entries in ctypes
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc99-extensions"
		const _ctype * ctypes[]; // array of pointers to all base types of the object
		//   including types that it can be implicitly cast to
#pragma clang diagnostic pop
	};

	struct _ThrowInfo {
		unsigned int           attributes;           // bit 1 for const, bit 2 for volatile
		_PMFN                  unwind;               // function to destroy the exception object
		int         (__cdecl * fwd_compat)(...);
		const _ctypeArray * ctype_array;  // pointer to array of pointers to type information
	};

	struct einfo {
		void*                object;
		const _ThrowInfo* info;

		einfo(const EXCEPTION_RECORD& er);
	};

	void* exception_cast_worker(const einfo& e, const std::type_info& req);
	void get_exception_types(std::ostream& os, const einfo& e);

	template <typename T>
	T* exception_cast(const einfo& e) {
		return reinterpret_cast<T*>(exception_cast_worker(e, typeid(T)));
	}

}
