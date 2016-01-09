#pragma once
#include "handle_traits.h"
#include <iostream>
namespace sint
{
	namespace test
	{
		void run_traits_test()
		{
			/*sint::traits::handle_traits<std::unique_ptr<int>> tr;
			decltype(tr)::Handle uptr;

			traits::handle_traits<std::shared_ptr<int>> ts;
			decltype(ts)::Handle s;


			traits::handle_traits<int*> tp;
			decltype(tp)::Handle p;*/
		}

		enum class Tag { zero, one, two };

		template<typename TIdentifier, typename THandle>
		class loader;

		template<typename TIdentifier, typename TType>
		class loader<TIdentifier, std::unique_ptr<TType>>
		{
		public:
			using Type = TType;
			using Handle = std::unique_ptr<Type>;
			using Share_type = Type*;
			using Identifier = TIdentifier;

			Handle load(Identifier id)
			{
				switch (id)
				{
				case Tag::zero:
					return Handle{ new int{ 0 } };
					break;
				case Tag::one:
					return Handle{ new int{ 1 } };
					break;
				case Tag::two:
					return Handle{ new int{ 2 } };
					break;
				default:
					return Handle{};
					break;
				}
			}

			void unload(Handle& handle)
			{
				handle.reset();
			}

			Share_type share(Handle& handle)
			{
				return Share_type{ handle.get() };
			}
		};

		template<typename TIdentifier, typename TType>
		class loader<TIdentifier, std::shared_ptr<TType>>
		{
		public:
			using Type = TType;
			using Handle = std::weak_ptr<Type>;
			using Load_type = std::shared_ptr<Type>;
			using Share_type = std::shared_ptr<Type>;
			using Identifier = TIdentifier;

			Load_type load(Identifier id)
			{
				switch (id)
				{
				case Tag::zero:
					return Load_type{ new int{ 0 } };
					break;
				case Tag::one:
					return Load_type{ new int{ 1 } };
					break;
				case Tag::two:
					return Load_type{ new int{ 2 } };
					break;
				default:
					return Load_type{};
					break;
				}
			}

			void unload(Handle& handle)
			{
				handle.reset();
			}

			Share_type share(Handle& handle)
			{
				return Share_type{ handle };
			}
		};

		using Unique_loader = loader<Tag, std::unique_ptr<int>>;
		using Shared_loader = loader<Tag, std::shared_ptr<int>>;

		void run_loaders_test()
		{
			/*loader<Tag, std::unique_ptr<int>> up_loader;
			auto up = up_loader.load(Tag::one);
			auto up_share = up_loader.share(up);

			std::cout << "up = " << *up_share << std::endl;

			up_loader.unload(up);

			loader<Tag, std::shared_ptr<int>> sp_loader;
			auto sp = sp_loader.load(Tag::two);
			std::weak_ptr<int> wp{ sp };
			auto sp_share = sp_loader.share(wp);
			auto sp_share2 = sp_loader.share(wp);

			std::cout << "sp = " << *sp_share << std::endl;
			std::cout << "sp2 = " << *sp_share2 << std::endl;
			std::cout << "sp count = " << sp.use_count() << std::endl;

			sp_loader.unload(wp);*/
		}
	}
}