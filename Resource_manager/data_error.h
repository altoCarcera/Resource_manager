#pragma once
#include <stdexcept>
#include <type_traits>
namespace sint
{
	template<typename TData>
	class data_error : public std::runtime_error
	{
	public:
		using Base = std::runtime_error;
		using Data = TData;

		data_error()
			: Base{ default_message }
		{

		}

		data_error(const data_error&) = default;
		data_error(data_error&&) = default;
		data_error& operator=(const data_error&) = default;
		data_error& operator=(data_error&&) = default;
		virtual ~data_error() = default;

		template<typename UData, typename = std::enable_if_t<!std::is_same<std::decay_t<UData>, data_error>::value>>
		explicit data_error(UData&& data)
			: Base{ default_message }, data{ std::forward<UData>(data) }
		{

		}

		template<typename UData, typename UMessage>
		data_error(UData&& data, UMessage&& message)
			: Base{ std::forward<UMessage>(message) }, data{ std::forward<UData>(data) }
		{

		}

		const Data& get_data()const
		{
			return data;
		}

	private:
		Data data;
		static constexpr const char* default_message = "data error";
	};

	template<>
	class data_error<void> : public std::runtime_error
	{
	public:
		using Base = std::runtime_error;
		using This = data_error<void>;

		data_error()
			: Base{ default_message }
		{

		}

		template<typename UMessage,
			typename = std::enable_if_t<!std::is_same<std::decay_t<UMessage>, This>::value >>
			explicit data_error(UMessage&& message)
			: Base{ std::forward<UMessage>(message) }
		{

		}

		data_error(const data_error&) = default;
		data_error(data_error&&) = default;
		data_error& operator=(const data_error&) = default;
		data_error& operator=(data_error&&) = default;
		virtual ~data_error() = default;

	private:
		static constexpr const char* default_message = "data error";
	};
}