#pragma once
#include "GameObject.h"

class DynamicObject : public GameObject
{
private:
	float m_timer = 0;
	float m_delay;
	bool m_life = false;
	bool m_destroy_tile = false; // only for Destroyer Ball is relevant
	bool m_build_tile = false; // only for Conquer Ball is relevant
public:
	using GameObject::GameObject;
	~DynamicObject();
	virtual void move(const dynamicO&, const staticO&) = 0;
	void setDelay(const float&);
	float getDelay() const;
	void setTimer(const float&);
	float getTimer() const;
	bool getLife() const;
	void setLife(const bool&);
	void setDestroyTile(const bool&);
	bool getDestroyTile() const;
	void setBuildTile(const bool&);
	bool getBuildTile() const;
	virtual bool collide(GameObject&, GameObject&) const = 0;
	template<typename T, typename Fn>
	void for_each_pair(T*, const dynamicO&, const staticO&, Fn);
};

// STL-like algorithm to run over all pairs
template<typename T, typename Fn>
inline void DynamicObject::for_each_pair(T* t, const dynamicO& mo, const staticO& so, Fn fn)
{
	for (auto second = mo.begin(); second != mo.end(); ++second)
				fn(t, *second);
	
	for (int i = 0; i < so.size(); i++)
		for (auto second = so[i].begin(); second != so[i].end(); ++second)
			fn(t, *second);
}
