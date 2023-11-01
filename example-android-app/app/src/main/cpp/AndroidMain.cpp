#include <android/log.h>
#include "VulkanMain.hpp"

void handle_cmd(android_app* app, int32_t cmd) {
  switch (cmd) {
    case APP_CMD_INIT_WINDOW:
      init_window(app);
      break;
    case APP_CMD_TERM_WINDOW:
      terminate_window();
      break;
    default:
      __android_log_print(ANDROID_LOG_INFO, "Vulkan Tutorials", "event not handled: %d", cmd);
  }
}

void android_main(struct android_app* app) {
  // Set the callback to process system events
  app->onAppCmd = handle_cmd;

  do {
    int events;
    android_poll_source* source;

    if (ALooper_pollAll(IsVulkanReady() ? 1 : 0, nullptr, &events, (void**)&source) >= 0) {
      if (source != nullptr) source->process(app, source);
    }

    if (IsVulkanReady()) draw_frame();
  } while (app->destroyRequested == 0);
}
