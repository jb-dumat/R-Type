/*
** rtype
** Created on 26/11/18.
*/

#pragma once

namespace graphic
{
    enum class EventType {
        CLOSED,
        KEYPRESS,
        TEXT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        ENTER,
        ESCAPE,
        BACKSPACE,
        NONE
    };

    struct EventResult {
        EventType type;
        char key;
    };
    
    class IEvent
    {
    public:
        virtual ~IEvent() = default;

        virtual graphic::EventResult getEvent() = 0;
    };
}