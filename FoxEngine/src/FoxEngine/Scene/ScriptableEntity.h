#pragma once
#include "Entity.h"

namespace FoxEngine {
    class ScriptableEntity {
        private:
            Entity entity;
            friend class Scene;
        public:
            virtual ~ScriptableEntity() { }

            template<typename T>
            T& getComponent()
            {
                return entity.getComponent<T>();
            }
    protected:
        virtual void onCreate() {}
        virtual void onUpdate(TimeStep ts) {}
        virtual void onDestroy() {}
    };

}