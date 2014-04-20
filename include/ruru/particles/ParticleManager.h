#ifndef H_RURU_PARTICLE_MANAGER
#define H_RURU_PARTICLE_MANAGER

#include "ruru/RuRu.h"

#include <vector>

NS_RURU_BEGIN

template<class T>
class ParticleManager
{
	private:
		std::vector<T> m_Particles;

		inline void remove(size_t deleteIndex)
		{
			size_t lastIndex = m_Particles.size() - 1;
			if (deleteIndex != lastIndex)
			{
				std::swap(m_Particles[deleteIndex], m_Particles[lastIndex]);
			}

			m_Particles.pop_back();
		}
		
	public:
		ParticleManager()
			: m_Particles() { }

		ParticleManager(size_t reserveSize)
			: m_Particles() 
		{
			m_Particles.reserve(reserveSize);
		}

		void add(T& particle)
		{
			m_Particles.push_back(particle);
		}

		template<typename ... Args>
		void emplace(Args&&... args)
		{
			m_Particles.emplace_back(std::forward<Args>(args)...);
		}

		void update() 
		{
			size_t i = 0;
			while (i < m_Particles.size())
			{
				bool particleAlive = m_Particles[i].update();

				if (!particleAlive)
					remove(i);
				else
					i++;
			}	
		}

		void render() const
		{
			for(auto& particle : m_Particles)
			{
				particle.render();
			}
		}
};


NS_RURU_END
#endif
