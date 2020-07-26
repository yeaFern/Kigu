#pragma once

#include <array>

namespace Kigu
{
	// An EnumMap is a constant mapping between enum values and some data.
	// Example usage:
	//
	// enum class Item
	// {
	// 	  Sword,
	// 	  Shield,
	// 	  Potion,
	// 	  _Last
	// };
	// 
	// struct ItemData
	// {
	// 	  std::string_view Name;
	// 	  int Cost;
	// 	  
	// 	  ItemData() = default;
	// 	  ItemData(const std::string_view& name, int cost)
	// 	      : Name(name), Cost(cost)
	// 	  {
	// 	  }
	// };
	//
	// EnumMap<Item, ItemData> registry({
	//		{
	//			Item::Sword, {
	//				"sword",
	//				200
	//			}
	//		},
	//		{
	//			Item::Shield, {
	//				"shield",
	//				150
	//			}
	//		},
	//		{
	//			Item::Potion, {
	//				"potion",
	//				35
	//			}
	//		},
	// });
	//

	template<typename Key, typename Data>
	class EnumMap
	{
		struct InitializerEntry {
			Key k;
			Data d;
		};

	private:
		std::array<Data, static_cast<size_t>(Key::_Last)> m_Data;
	public:
		template<std::size_t N>
		EnumMap(const InitializerEntry(&list)[N])
		{
			static_assert(std::is_enum<Key>::value, "EnumMap key must be an enum");
			static_assert(N == static_cast<size_t>(Key::_Last), "EnumMap initializer size mismatch");

			for (size_t i = 0; i < N; i++)
			{
				m_Data[static_cast<size_t>(list[i].k)] = list[i].d;
			}
		}

		size_t Size() const { return m_Data.size(); }

		const Data& Get(Key k) const
		{
			return m_Data[static_cast<size_t>(k)];
		}

		template<Key K>
		const Data& Get() const
		{
			return Get(K);
		}
	};
}
