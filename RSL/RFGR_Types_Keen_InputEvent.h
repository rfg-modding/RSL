#pragma once
#include "RFGR_Types_weapon_info.h"

namespace keen
{
    enum ControllerType
    {
        ControllerType_Unkown = 0x0,
        ControllerType_Keyboard = 0x1,
        ControllerType_Mouse = 0x2,
        ControllerType_PS3 = 0x3,
        ControllerType_DualShock4 = 0x4,
        ControllerType_Xbox360 = 0x5,
        ControllerType_3ds = 0x6,
        ControllerType_WiiUGamePad = 0x7,
        ControllerType_WiiMote = 0x8,
        ControllerType_OSX = 0x9,
        ControllerType_XBone = 0xA,
        ControllerType_PSVita = 0xB,
        ControllerType_Steam = 0xC,
        ControllerType_JoyConPair = 0xD,
        ControllerType_JoyConSingle = 0xE,
        ControllerType_SwitchProController = 0xF,
        ControllerType_Count = 0x10,
    };

    enum StandardButtonId
    {
        StandardButtonId_Unknown = 0x0,
        StandardButtonId_Left = 0x1,
        StandardButtonId_Right = 0x2,
        StandardButtonId_Up = 0x3,
        StandardButtonId_Down = 0x4,
        StandardButtonId_Confirm = 0x5,
        StandardButtonId_Exit = 0x6,
        StandardButtonId_StartPause = 0x7,
        StandardButtonId_Select = 0x8,
    };

    enum FlickDirection
    {
        FlickDirection_Left = 0x0,
        FlickDirection_Right = 0x1,
        FlickDirection_Up = 0x2,
        FlickDirection_Down = 0x3,
    };

    struct ConnectedEventData
    {
        keen::ControllerType controllerType;
        unsigned int features;
    };

    struct ButtonEventData
    {
        unsigned int buttonIndex;
        keen::StandardButtonId standardButton;
    };

    struct AxisEventData
    {
        unsigned int axisIndex;
        float value;
        float previousValue;
    };

    struct KeyEventData
    {
        unsigned int keyCode;
    };

    struct MouseEventData
    {
        keen::float2 position;
    };


    struct MouseWheelEventData
    {
        int wheelDelta;
    };

    struct TouchEventData
    {
        unsigned int touchId;
        keen::float2 position;
    };

    struct FlickEventData
    {
        keen::FlickDirection direction;
        float speed;
        keen::float2 startPosition;
    };

    struct DragEventData
    {
        keen::float2 startPosition;
        keen::float2 deltaPosition;
    };

    struct Axis2dEventData
    {
        unsigned int axisIndex;
        float x;
        float y;
    };

    union GyroEventData
    {
        keen::float3 acceleration;
        keen::float3 angularVelocity;
        keen::float4 orientation;
    };

    union InputEventData
    {
        keen::ConnectedEventData connected;
        keen::ButtonEventData button;
        keen::AxisEventData axis;
        keen::KeyEventData key;
        keen::MouseEventData mouse;
        keen::MouseWheelEventData wheel;
        keen::TouchEventData touch;
        keen::FlickEventData flick;
        keen::DragEventData drag;
        keen::Axis2dEventData axis2d;
        keen::GyroEventData gyro;
    };

    struct InputEvent
    {
        char controllerId;
        char controllerClass;
        char localPlayerId;
        char type;
        keen::InputEventData data;
    };
}
