#pragma once

#include <N503/Abi/Exception.hpp>
#include <N503/Abi/Status.hpp>

#include <type_traits>

namespace N503::Abi
{

    /// @brief
    /// @tparam T
    template <typename T>
        requires std::is_void_v<T> || std::is_move_constructible_v<T>
    struct [[nodiscard]] Result final
    {
        /// @brief
        T Value;

        /// @brief
        N503::Abi::Status Status;

        /// @brief
        /// @return
        constexpr auto IsSuccess() const noexcept -> bool
        {
            return Status == Status::Success;
        }

        /// @brief
        /// @return
        constexpr auto IsFailed() const noexcept -> bool
        {
            return Status != Status::Success;
        }

        /// @brief
        constexpr explicit operator bool() const noexcept
        {
            return IsSuccess();
        }

        /// @brief
        /// @return
        constexpr auto operator->() -> T *
        {
            if (Status != Status::Success)
            {
                throw N503::Abi::Exception(Status);
            }

            return &Value;
        }

        /// @brief
        /// @return
        constexpr auto operator->() const -> const T *
        {
            if (Status != Status::Success)
            {
                throw N503::Abi::Exception(Status);
            }

            return &Value;
        }

        /// @brief
        /// @return
        constexpr auto operator*() & -> T &
        {
            if (Status != Status::Success)
            {
                throw N503::Abi::Exception(Status);
            }

            return Value;
        }
    };

    /// @brief
    template <> struct [[nodiscard]] Result<void> final
    {
        /// @brief
        N503::Abi::Status Status;

        /// @brief
        /// @return
        constexpr auto IsSuccess() const noexcept -> bool
        {
            return Status == Status::Success;
        }

        /// @brief
        /// @return
        constexpr auto IsFailed() const noexcept -> bool
        {
            return Status != Status::Success;
        }

        /// @brief
        constexpr explicit operator bool() const noexcept
        {
            return IsSuccess();
        }
    };

} // namespace N503::Abi
