#pragma once

// User Message
#define WM_EYEBREAK_SYSTEM_TRAY (WM_USER + 100)
#define WM_EYEBREAK_MENU (WM_USER + 101)
#define WM_EYECARE_SETTING_APPLY (WM_USER + 102)


// Tray Menu
#define MIT_SHOW_EYEBREAK 100
#define MIT_EYEBREAK_SETTING 101
#define MIT_EYEBREAK_QUIT 102
#define MIT_EYEBREAK_ABOUT 103


// Timer
#define EYECARE_DISPLAY_TIMER 1000
#define EYECARE_RELAX_TIMER 1001
#define EYECARE_RELAX_COUNTDONW_TIMER 1002
#define EYECARE_APP_STATE_COUNTDONW_TIMER 1003



constexpr int kDefaultEyeCareTimer = 1;  // 1 minute to show EyeCare

constexpr int kDefaultRelaxTimer = 1;  // 1 minute to take rest