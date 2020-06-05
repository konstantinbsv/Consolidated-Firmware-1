#pragma once

#define STATIC_DEFINE_APP_SET_PERIODIC_CAN_SIGNALS_IN_RANGE_CHECK(             \
    CAN_TX_INTERFACE)                                                          \
    static void App_SetPeriodicCanSignals_InRangeCheck(                        \
        struct CAN_TX_INTERFACE *  can_tx,                                     \
        const struct InRangeCheck *in_range_check,                             \
        void (*const can_signal_setter)(struct CAN_TX_INTERFACE *, float),     \
        void (*const out_of_range_setter)(struct CAN_TX_INTERFACE *, uint8_t), \
        uint8_t ok_choice, uint8_t underflow_choice, uint8_t overflow_choice)  \
    {                                                                          \
        float                    value;                                        \
        enum InRangeCheck_Status status =                                      \
            App_InRangeCheck_GetValue(in_range_check, &value);                 \
                                                                               \
        switch (status)                                                        \
        {                                                                      \
            case VALUE_IN_RANGE:                                               \
            {                                                                  \
                out_of_range_setter(can_tx, ok_choice);                        \
            }                                                                  \
            break;                                                             \
            case VALUE_UNDERFLOW:                                              \
            {                                                                  \
                out_of_range_setter(can_tx, underflow_choice);                 \
            }                                                                  \
            break;                                                             \
            case VALUE_OVERFLOW:                                               \
            {                                                                  \
                out_of_range_setter(can_tx, overflow_choice);                  \
            }                                                                  \
            break;                                                             \
        }                                                                      \
                                                                               \
        can_signal_setter(can_tx, value);                                      \
    }

#define STATIC_DEFINE_APP_SET_PERIODIC_CAN_SIGNALS_BINARY_STATUS(            \
    CAN_TX_INTERFACE)                                                        \
    static void App_SetPeriodicCanSignals_SharedBinaryStatus(                \
        struct CAN_TX_INTERFACE *  can_tx,                                   \
        const struct BinaryStatus *binary_status,                            \
        void (*const can_signal_setter)(struct CAN_TX_INTERFACE *, uint8_t), \
        uint8_t on_choice, uint8_t off_choice)                               \
    {                                                                        \
        if (App_SharedBinaryStatus_IsActive(binary_status))                  \
        {                                                                    \
            can_signal_setter(can_tx, on_choice);                            \
        }                                                                    \
        else                                                                 \
        {                                                                    \
            can_signal_setter(can_tx, off_choice);                           \
        }                                                                    \
    }
