#ifndef H_RURU_SHOOTING_SYSTEM
#define H_RURU_SHOOTING_SYSTEM

#include "ruru/RuRu.h"
#include "ruru/entities/EntityManager.h"
#include "ruru/services/ServiceLocator.h"

#include <exception>

NS_RURU_BEGIN

////////////////////////////////////////////////////////////////////////////TEMPLATE HELPERS

// Checks if parameter pack is all true.
template<typename B1>
inline B1 isTrue(B1 b) { return b; }

template<typename B1 = bool, typename B2 = bool, typename... BArgs>
inline bool isTrue(B1 arg1, B2 arg2, BArgs... args) { return isTrue(arg1) && isTrue(arg2, args...); }

// Calls before method on pointer if type has a before method.

template<typename T>
inline auto callBefore(EntityManager& em, const ServiceLocator& sl, T* t) -> decltype(std::declval<T>().before(em, sl), void())
{
	t->before(em, sl);
}

inline void callBefore(EntityManager& em, const ServiceLocator& sl, ...)
{
}

// Calls After method on pointer if type has an after method.

template<typename T>
inline auto callAfter(EntityManager& em, const ServiceLocator& sl, T* t) -> decltype(std::declval<T>().after(em, sl), void())
{
	t->after(em, sl);
}

inline void callAfter(EntityManager& em, const ServiceLocator& sl, ...) 
{ 
}

// Represents not value passed in.

class nothing {};
////////////////////////////////////////////////////////////////////////////////////////////

template<typename S, typename T, typename T2 = nothing, typename ...Args>
class SystemMixin;

template<typename S, typename T, typename ...Args> 
class SystemMixin<S, T, nothing, Args...>
{
	protected:
		constexpr static const size_t ComponentCount = 1;

	public:
		void run(EntityManager& em, const ServiceLocator& sl)
		{
			auto iter = em.components().begin<T>();
			auto end = em.components().end<T>();

			callBefore(em, sl, static_cast<S*>(this));

			for (; iter != end; iter++)
				static_cast<S*>(this)->runSingle(em, sl, *iter);

			callAfter(em, sl, static_cast<S*>(this));
		}
};


template<typename S, typename T1, typename T2, typename ...Args> 
class SystemMixin
{
	protected:
		constexpr static const size_t ComponentCount = sizeof...(Args) + 2;

	public:
		void run(EntityManager& em, const ServiceLocator& sl)
		{
			callBefore(em, sl, static_cast<S*>(this));
	
			for(const Entity& e : em)
			{
				if (! isTrue(e.hasComponent<T1>(), e.hasComponent<T2>(), e.hasComponent<Args>()...)) continue;

				static_cast<S*>(this)->runSingle(em, sl, e.getComponent<T1>(), e.getComponent<T2>(), e.getComponent<Args>()...);
			}

			callAfter(em, sl, static_cast<S*>(this));
		}
};

template<typename S, typename T>
class PairWiseSystemMixin
{
	public:
		void run(EntityManager& em, const ServiceLocator& sl)
		{
			callBefore(em, sl, static_cast<S*>(this));

			auto iter = em.components().begin<T>();
			auto end = em.components().end<T>();

			for (; iter != end; iter++)
			{
				for (auto iter2 = iter + 1; iter2 != end; iter2++)
					static_cast<S*>(this)->runSingle(em, sl, *iter, *iter2);
			}

			callAfter(em, sl, static_cast<S*>(this));
		}

};



NS_RURU_END
#endif
