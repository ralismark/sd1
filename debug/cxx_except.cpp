#include "cxx_except.hpp"

namespace cxx_except
{

	einfo::einfo(const EXCEPTION_RECORD& er)
		: object(reinterpret_cast<void*>(er.ExceptionInformation[1]))
		, info(reinterpret_cast<const _ThrowInfo*>(er.ExceptionInformation[2]))
	{ ; }

	void* exception_cast_worker(const einfo& e, const std::type_info& req)
	{
		for(int i = 0; i < e.info->ctype_array->size; ++i) {
			const _ctype& type = *e.info->ctype_array->ctypes[i];
			const std::type_info& ti = *type.pType;
			if(ti == req) {
				char* base = reinterpret_cast<char*>(e.object);
				base += type.displacement.mdisp;
				return base;
			}
		}
		return 0;
	}

	void get_exception_types(std::ostream& os, const einfo& e)
	{
		for(int i = 0; i < e.info->ctype_array->size; ++i) {
			const _ctype& type = *e.info->ctype_array->ctypes[i];
			const std::type_info& ti = *type.pType;
			os << ti.name() << ' ';
		}
	}

}
