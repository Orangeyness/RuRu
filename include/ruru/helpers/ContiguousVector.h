#ifndef H_CONTIGUOUS_VECTOR
#define H_CONTIGUOUS_VECTOR

#include <utility>
#include <vector>
#include <unordered_map>

#include "ruru/RuRu.h"
NS_RURU_BEGIN

class IContiguousVector 
{
	public:
		virtual size_t size() const = 0;
		virtual size_t nextId() const = 0;
		virtual void remove(int id) = 0;
		virtual bool has(int id) const = 0;
		virtual ~IContiguousVector() { }
};

template<typename T>
class ContiguousVector : public IContiguousVector
{

	private:
		int m_NextId;
		std::vector<T> m_Data;
		std::unordered_map<int, size_t> m_IdToIndex;
		std::unordered_map<size_t, int> m_IndexToId;
	
	public:
		ContiguousVector()
			: m_NextId(0) { }

		ContiguousVector(size_t initialCapacity)
			: m_NextId(0)
		{
			m_Data.reserve(initialCapacity);
		}

		int add(T val)
		{
			m_IdToIndex[m_NextId] = m_Data.size();
			m_IndexToId[m_Data.size()] = m_NextId;

			m_Data.push_back(val);
			
			return m_NextId++;
		}

		template<typename ...Params>
		int emplace(Params &&... params)
		{
			m_IdToIndex[m_NextId] = m_Data.size();
			m_IndexToId[m_Data.size()] = m_NextId;

			m_Data.emplace_back(std::forward<Params>(params)...);

			return m_NextId++;
		}

		virtual bool has(int id) const
		{
			return (m_IdToIndex.find(id) != m_IdToIndex.end());
		}

		T& get(int id)
		{
			return m_Data[m_IdToIndex.at(id)];
		}

		T* tryGet(int id)
		{
			if (! has(id)) return nullptr;

			return &m_Data[m_IdToIndex[id]];
		}

		virtual void remove(int id)
		{
			size_t deleteIndex = m_IdToIndex.at(id);
			size_t lastIndex = m_Data.size() - 1;

			if (deleteIndex != lastIndex)
			{
				std::swap(m_Data[deleteIndex], m_Data[lastIndex]);

				// Fix Id lookup map
				int movedId = m_IndexToId[lastIndex];
				m_IdToIndex[movedId] = deleteIndex;
				m_IndexToId[deleteIndex] = movedId;
			}

			m_IndexToId.erase(lastIndex);
			m_IdToIndex.erase(id);			
			m_Data.pop_back();
		}

		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;

		iterator begin() { return m_Data.begin(); }
		iterator end() { return m_Data.end(); }
		const_iterator cbegin() const { return m_Data.cbegin(); }
		const_iterator cend() const { return m_Data.cend(); }

		virtual size_t size() const { return m_Data.size(); }
		inline size_t nextId() const { return m_NextId; }
};

NS_RURU_END
#endif
