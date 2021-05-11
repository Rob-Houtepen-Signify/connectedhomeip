#ifndef LOCK_MANAGER_H
#define LOCK_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

#include "AppEvent.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h" // provides FreeRTOS timer support

class BoltLockManager
{
public:
    enum Action_t
    {
        LOCK_ACTION = 0,
        UNLOCK_ACTION,

        INVALID_ACTION
    } Action;

    enum State_t
    {
        kState_LockingInitiated = 0,
        kState_LockingCompleted,
        kState_UnlockingInitiated,
        kState_UnlockingCompleted,
    } State;

    int  Init();
    bool IsUnlocked();
    void EnableAutoRelock(bool aOn);
    void SetAutoLockDuration(uint32_t aDurationInSecs);
    bool IsActionInProgress();
    bool InitiateAction(int32_t aActor, Action_t aAction);

    typedef void (*Callback_fn_initiated)(Action_t, int32_t aActor);
    typedef void (*Callback_fn_completed)(Action_t);
    void SetCallbacks(Callback_fn_initiated aActionInitiated_CB, Callback_fn_completed aActionCompleted_CB);

private:
    friend BoltLockManager &BoltLockMgr(void);
    State_t                 mState;

    Callback_fn_initiated mActionInitiated_CB;
    Callback_fn_completed mActionCompleted_CB;

    bool     mAutoRelock;
    uint32_t mAutoLockDuration;
    bool     mAutoLockTimerArmed;

    void CancelTimer(void);
    void StartTimer(uint32_t aTimeoutMs);

    static void TimerEventHandler(TimerHandle_t xTimer);
    static void AutoReLockTimerEventHandler(AppEvent *aEvent);
    static void ActuatorMovementTimerEventHandler(AppEvent *aEvent);

    static BoltLockManager sLock;
};

inline BoltLockManager &BoltLockMgr(void)
{
    return BoltLockManager::sLock;
}

#endif // LOCK_MANAGER_H
