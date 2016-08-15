#include "terminal.hpp"

#include <windows.h>
#include <iomanip>
#include <iostream>
#include <typeinfo>

#include "cxx_except.hpp"

namespace
{

	void dump_bytes(std::ostream& os, const void* addr, size_t sz)
	{
		const unsigned char* mem = reinterpret_cast<const unsigned char*>(addr);
		os << std::hex << "[ ";
		for(size_t i = 0; i < sz; ++i) {
			os << std::setw(2) << (unsigned int)(mem[i]);
			if(i % 2 != 0) {
				os << ' ';
			}
		}
		if(sz % 2 != 0) {
			os << ' ';
		}
		os << ']';
	}

	void dump_er(EXCEPTION_RECORD* er)
	{
		std::cerr << "[0x";
		std::cerr << std::hex << std::setfill('0') << std::setw(sizeof(void*) * 2) << er->ExceptionCode;
		std::cerr << "] ";

		const char* msg = "Unknown Exception";

		switch(er->ExceptionCode) {
		case EXCEPTION_ACCESS_VIOLATION:
			msg = "Access Violation";
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			msg = "Array Bounds Exceeded";
			break;
		case EXCEPTION_BREAKPOINT:
			msg = "Breakpoint";
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			msg = "Datatype Misalignment";
			break;
		case EXCEPTION_FLT_DENORMAL_OPERAND:
			msg = "(fp) Denormal Operand";
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			msg = "(fp) Divide By Zero";
			break;
		case EXCEPTION_FLT_INEXACT_RESULT:
			msg = "(fp) Inexact Result";
			break;
		case EXCEPTION_FLT_INVALID_OPERATION:
			msg = "(fp) Invalid Operand";
			break;
		case EXCEPTION_FLT_OVERFLOW:
			msg = "(fp) Overflow";
			break;
		case EXCEPTION_FLT_STACK_CHECK:
			msg = "(fp) Stack Check";
			break;
		case EXCEPTION_FLT_UNDERFLOW:
			msg = "(fp) Underflow";
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			msg = "Illegal Instruction";
			break;
		case EXCEPTION_IN_PAGE_ERROR:
			msg = "In Page Error";
			break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			msg = "Int Divide By Zero";
			break;
		case EXCEPTION_INT_OVERFLOW:
			msg = "Int Overflow";
			break;
		case EXCEPTION_INVALID_DISPOSITION:
			msg = "Invalid Disposition";
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			msg = "Noncontinuable Exception";
			break;
		case EXCEPTION_PRIV_INSTRUCTION:
			msg = "Priv Instruction";
			break;
		case EXCEPTION_SINGLE_STEP:
			msg = "Single Step";
			break;
		case EXCEPTION_STACK_OVERFLOW:
			msg = "Stack Overflow";
			break;

		case 0xe06d7363:
			msg = "C++ EH exception";
			break;
		}
		std::cerr << msg << '\n';
		std::cerr << "  at 0x" << std::setw(sizeof(void*) * 2) << std::setfill('0') << er->ExceptionAddress << '\n';

		if(er->ExceptionCode == 0xe06d7363) {
			cxx_except::einfo ce = *er;

			auto* eint = cxx_except::exception_cast<std::exception>(ce);
			if(eint) {
				std::cerr << "  " << typeid(*eint).name() << " was thrown:\n    .what(): " << eint->what() << '\n';
			} else {
				std::cerr << "  Could not get information, type one of:\n";

				const cxx_except::_ctypeArray& ca = *ce.info->ctype_array;
				for(int i = 0; i < ca.size; ++i) {
					std::cerr << "    " << ca.ctypes[i]->pType->name() << ' ';
					dump_bytes(std::cerr, cxx_except::exception_cast_worker(ce, *ca.ctypes[i]->pType), ca.ctypes[i]->size);
					std::cerr << '\n';
				}
			}
		} else if(er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION || er->ExceptionCode == EXCEPTION_IN_PAGE_ERROR) {
			const char* access_type = "access";
			switch(er->ExceptionInformation[0]) {
			case 0:
				access_type = "read";
				break;
			case 1:
				access_type = "write";
				break;
			case 8:
				access_type = "execution";
				break;
			}
			std::cerr << "  attempted " << access_type << " of address 0x" << std::setw(sizeof(void*) * 2) << std::setfill('0') << er->ExceptionInformation[1] << '\n';
			if(er->ExceptionCode == EXCEPTION_IN_PAGE_ERROR) {
				std::cerr << "  NTSTATUS: " << er->ExceptionInformation[2];
			}
		} else {
			for(size_t i = 0; i < er->NumberParameters; ++i) {
				std::cerr << "  [" << i << "] " << er->ExceptionInformation[i] << '\n';
			}
		}
	}

	LONG WINAPI ue_filter(EXCEPTION_POINTERS* ei)
	{
		std::cerr << "An uncaught exception was raised during execution.\n";
		for(EXCEPTION_RECORD* er = ei->ExceptionRecord; er != 0; er = er->ExceptionRecord) {
			dump_er(er);
		}

		return EXCEPTION_EXECUTE_HANDLER;
	}

	bool def_terminal()
	{
		SetUnhandledExceptionFilter(&ue_filter);
		return true;
	}

}

bool _teriminal_decl_ = def_terminal();
