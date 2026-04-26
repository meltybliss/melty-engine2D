#pragma once
#include "SceneLogicRegistry.h"
#include "BehaviourRegistry.h"

template<typename T>
struct BehaviourAutoRegister {
	BehaviourAutoRegister(const std::string& name) {
		BehaviourRegistry::Get().Register<T>(name);
	}
};


template<typename T>
struct SceneLogicAutoRegister {
	SceneLogicAutoRegister(const std::string& name) {
		SceneLogicRegister::Get().Register<T>(name);
	}
};



#define REGISTER_BEHAVIOUR(TYPE, NAME) \
    static BehaviourAutoRegister<TYPE> auto_reg_behaviour_##TYPE(NAME)

#define REGISTER_SCENELOGIC(TYPE, NAME) \
	static SceneLogicAutoRegister<TYPE> auto_reg_scenelogic_##TYPE(NAME) 