#pragma once

#include <Windows.h>
#include <cstdint>

namespace N503::Abi
{

    /// @brief
    enum class Status : std::uint32_t
    {
        Success = 0x00000000, ///<
        Failure = 0x00000001, ///<
        Unknown = 0xFFFFFFFF  ///<
    };

    /// @brief Win32エラーコードを N503::Abi::Status に翻訳します
    /// @note この関数自体は失敗しないため、Result ではなく Status を直接返します
    /// @param
    /// @return
    [[nodiscard]]
    inline auto CreateStatusFromWin32Error(std::uint32_t error) noexcept -> Status
    {
        switch (error)
        {
            case ERROR_SUCCESS:
                return Status::Success;

            case ERROR_IO_PENDING:
                return Status::Failure;

            case ERROR_ACCESS_DENIED:
                return Status::Failure;

            case ERROR_HANDLE_EOF:
                return Status::Failure;

            case ERROR_INVALID_HANDLE:
            case ERROR_INVALID_PARAMETER:
            case ERROR_INVALID_ADDRESS:
                return Status::Failure;

            case WAIT_TIMEOUT:
            case ERROR_TIMEOUT:
                return Status::Failure;

            case ERROR_NOT_ENOUGH_MEMORY:
            case ERROR_OUTOFMEMORY:
                return Status::Failure;

            case ERROR_OPERATION_ABORTED:
                return Status::Failure;

            default:
                return Status::Unknown;
        }
    }

} // namespace N503::Abi
