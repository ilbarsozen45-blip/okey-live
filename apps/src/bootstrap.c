#include "apps/apps.h"
#include "kernel/scheduler.h"
#include "kernel/console.h"

static void app_file_explorer(void) {
    while (1) {}
}

static void app_settings(void) {
    while (1) {}
}

static void app_text_viewer(void) {
    while (1) {}
}

static void app_system_monitor(void) {
    while (1) {}
}

void apps_bootstrap(void) {
    sched_spawn("file-explorer", app_file_explorer);
    sched_spawn("settings", app_settings);
    sched_spawn("text-viewer", app_text_viewer);
    sched_spawn("sys-monitor", app_system_monitor);
    kconsole_write("apps: default shell apps registered\n");
}
