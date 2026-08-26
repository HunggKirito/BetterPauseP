#include "pch.h"
#include "PauseHook.h"

// Geode owns DLL startup and hook installation.
$on_mod(Loaded) {
    sharedStateBP().LoadSettings();
}
