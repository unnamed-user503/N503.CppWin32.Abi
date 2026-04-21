#pragma once

#include <N503/Abi/Exception.hpp>
#include <utility>

#define N503_THROW_IF_FAILED(ResultExpression)                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        auto &&__TemporaryResource = (ResultExpression);                                                               \
        if (__TemporaryResource.IsFailed())                                                                            \
        {                                                                                                              \
            throw ::N503::Abi::Exception(__TemporaryResource.Status);                                                  \
        }                                                                                                              \
    } while (false)

#define N503_THROW_IF_FAILED_AND_GET(ResultExpression)                                                                 \
    (                                                                                                                  \
        [&]()                                                                                                          \
        {                                                                                                              \
            auto &&__TemporaryResource = (ResultExpression);                                                           \
            if (__TemporaryResource.IsFailed())                                                                        \
            {                                                                                                          \
                throw ::N503::Abi::Exception(__TemporaryResource.Status);                                              \
            }                                                                                                          \
            return std::move(__TemporaryResource.Value);                                                               \
        }()                                                                                                            \
    )
