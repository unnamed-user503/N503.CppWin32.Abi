#pragma once

#include <N503/Abi/Status.hpp>

#include <Windows.h>
#include <format>
#include <source_location>
#include <stdexcept>
#include <string>

namespace N503::Abi
{

    /// @brief
    class Exception : public std::runtime_error
    {
    public:
        /// @brief
        /// @param status
        /// @param location
        Exception(N503::Abi::Status status, std::source_location location = std::source_location::current())
            : std::runtime_error(FormatMessage(status, location)), m_Status(status)
        {
        }

        /// @brief
        /// @return
        [[nodiscard]]
        auto GetStatus() const noexcept -> N503::Abi::Status
        {
            return m_Status;
        }

    private:
        /// @brief
        /// @param status
        /// @param location
        /// @return
        static auto FormatMessage(Status status, const std::source_location& location) -> std::string
        {
            return std::format(
                "N503 ABI Error: {:08X}\n"
                "Location: {}({}:{}) \n"
                "Function: {}",
                static_cast<int>(status),
                location.file_name(),
                location.line(),
                location.column(),
                location.function_name()
            );
        }

    private:
        /// @brief
        N503::Abi::Status m_Status;
    };

} // namespace N503::Abi
