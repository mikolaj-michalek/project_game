#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <memory>
#include "State.h"

namespace Engine
{
    class StateManager
    {
    private:
        std::stack<std::unique_ptr<State>> m_stateStack;
        std::unique_ptr<State> m_newState;

        bool m_add;
        bool m_replace;
        bool m_remove;

    public:
        StateManager();
        ~StateManager();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void ProcessStateChange();
        std::unique_ptr<State>& GetCurrent();

    };

} // namespace Engine

#endif // STATEMANAGER_H
