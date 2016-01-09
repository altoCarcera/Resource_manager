#pragma once
#include <memory>
namespace sint
{
	namespace traits
	{
		template<typename Handle> struct handle_traits;
		
		template<typename TType>
		struct handle_traits<std::unique_ptr<TType>>
		{
			using Type = TType;
			using Handle = std::unique_ptr<Type>;
			using Share_type = Type*;
			using Load_type = std::unique_ptr<Type>;
		};

		template<typename TType>
		struct handle_traits<std::shared_ptr<TType>>
		{
			using Type = TType;
			using Handle = std::weak_ptr<Type>;
			using Share_type = std::shared_ptr<Type>;
			using Load_type = std::shared_ptr<Type>;
		};

		template<typename TType>
		struct handle_traits<TType*>
		{
			using Type = TType;
			using Handle = Type*;
			using Share_type = Type*;
			using Load_type = Type*;
		};
	}


}