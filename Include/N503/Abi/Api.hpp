#pragma once

#ifdef N503_DLL_EXPORTS
#define N503_API __declspec(dllexport)
#else
#define N503_API __declspec(dllimport)
#endif

#include <N503/Abi/Result.hpp>
#include <N503/Abi/Status.hpp>

namespace N503::Abi
{
}
