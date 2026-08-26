#include "pch.h"
#include "PauseHook.h"

$on_mod(Loaded) {
    sharedStateBP().LoadSettings();
}
