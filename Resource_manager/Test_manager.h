#pragma once
#include "Test_loader.h"
#include "resource_manager.h"

namespace sint
{
	namespace test
	{
		struct raw_loader
		{
			using Type = int;
			using Traits = traits::handle_traits<Type*>;
			using Handle = Type*;
			using Load_type = Type*;
			using Share_type = Type*;
			using Identifier = Tag;

			Load_type load(Identifier id)
			{
				std::cout << "allocated" << std::endl;
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
				std::cout << "deleted = " << *handle << std::endl;
				delete handle;
				handle = nullptr;
			}

			Share_type share(Handle& handle)
			{
				return Share_type{ handle };
			}
		};

		using Unique_manager = resource_manager<Unique_loader>;
		using Shared_manager = resource_manager<Shared_loader>;
		using Raw_manager = resource_manager<raw_loader>;

		void run_unique_manager_test()
		{
			using namespace std;

			Unique_manager manager;

			auto up1 = manager.share(Tag::one);
			auto up2 = manager.share(Tag::two);

			cout << "up1 = " << *up1 << endl;
			cout << "up2 = " << *up2 << endl;
		}

		void run_shared_manager_test()
		{
			using namespace std;

			Shared_manager manager;
			auto sp1 = manager.share(Tag::one);
			auto sp2 = manager.share(Tag::two);
			auto sp11 = manager.share(Tag::one);

			cout << "sp1 = " << *sp1 << endl;
			cout << "sp2 = " << *sp2 << endl;
			cout << "count sp1 = " << sp1.use_count() << endl;
			cout << "count sp2 = " << sp2.use_count() << endl;
			cout << "count sp11 = " << sp11.use_count() << endl;

			for (const auto& x : manager)
			{
				cout << x.second.use_count() << endl;
			}
		}

		void run_raw_manager_test()
		{
			using namespace std;

			Raw_manager manager;
			auto rp1 = manager.share(Tag::one);
			auto rp2 = manager.share(Tag::two);
			auto rp11 = manager.share(Tag::one);

			cout << "rp1 = " << *rp1 << endl;
			cout << "rp2 = " << *rp2 << endl;
			cout << "rp11 = " << *rp11 << endl;
		}

		void run_managers_tests()
		{
			//run_unique_manager_test();
			run_shared_manager_test();
			//run_raw_manager_test();
		}
	}
}