#pragma once
#include <unordered_map>
#include <algorithm>
namespace sint
{
	template<
		typename TLoader,
		typename TContainer = std::unordered_map<
			typename TLoader::Identifier, typename TLoader::Handle>,
		typename THandle = typename TLoader::Handle> 
	class resource_manager
	{
	public:
		using This = resource_manager;
		using Loader = TLoader;
		using Handle = THandle;
		using Share_type = typename Loader::Share_type;
		using Identifier = typename Loader::Identifier;
		using Container = TContainer;
		using iterator = typename Container::iterator;


		resource_manager() = default;
		resource_manager(This&&) = default;
		resource_manager& operator=(This&&) = default;
		~resource_manager() = default;

		resource_manager(This const& rhs) = delete;
		This& operator=(This const& rhs) = delete;

		Share_type share(Identifier id)
		{
			auto found = container.find(id);
			if (found == container.end())
			{
				auto handle = loader.load(id);
				auto iter = container.emplace(id, std::move(handle));
				return loader.share(iter.first->second);
			}
			return loader.share(found->second);
		}

		void reset()
		{
			container.clear();
			loader = Loader{};
		}

		iterator begin()
		{
			return container.begin();
		}

		iterator end()
		{
			return container.end();
		}

	private:
		Container container;
		Loader loader;
	};

	template<typename TLoader, typename TContainer>//raw pointer
	class resource_manager<TLoader, TContainer, typename TLoader::Type*>
	{
	public:
		using This = resource_manager;
		using Loader = TLoader;
		using Handle = typename Loader::Type*;
		using Share_type = typename Loader::Share_type;
		using Identifier = typename Loader::Identifier;
		using Container = TContainer;
		using iterator = typename Container::iterator;

		resource_manager() = default;
		resource_manager(This&&) = default;
		resource_manager& operator=(This&&) = default;

		~resource_manager()
		{
			deallocate();
		}

		resource_manager(This const& rhs) = delete;
		This& operator=(This const& rhs) = delete;

		Share_type share(Identifier id)
		{
			auto found = container.find(id);
			if (found == container.end())
			{
				auto handle = loader.load(id);
				auto iter = container.emplace(id, std::move(handle));
				return loader.share(iter.first->second);
			}
			return loader.share(found->second);
		}

		void reset()
		{
			deallocate();
			loader = Loader{};
		}

		iterator begin()
		{
			return container.begin();
		}

		iterator end()
		{
			return container.end();
		}

	private:
		void deallocate()
		{
			std::for_each(std::begin(container), std::end(container),
				[this](typename Container::value_type& element)
			{
				loader.unload(element.second);
			});
		}

	private:
		Container container;
		Loader loader;
	};
}