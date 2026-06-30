#pragma once

#include "../util/config/config.h"

#include "../dxvk/dxvk_include.h"

#include "dxgi_include.h"

namespace dxvk {

  /**
   * \brief DXGI options
   * 
   * Per-app options that control the
   * behaviour of some DXGI classes.
   */
  struct DxgiOptions {
    DxgiOptions(const Config& config);

    /// Override PCI vendor and device IDs reported to the
    /// application. This may make apps think they are running
    /// on a different GPU than they do and behave differently.
    int32_t customVendorId;
    int32_t customDeviceId;
    std::string customDeviceDesc;
    
    /// Override maximum reported VRAM size. This may be
    /// useful for some 64-bit games which do not support
    /// more than 4 GiB of VRAM.
    VkDeviceSize maxDeviceMemory;
    VkDeviceSize maxSharedMemory;

    /// Reports Nvidia GPUs running on the proprietary driver as a different
    /// vendor (usually AMD). Proton will generally disable this option.
    bool hideNvidiaGpu;

    /// Reports Nvidia GPUs running on NVK as a different vendor (usually AMD)
    bool hideNvkGpu;

    /// Reports AMD GPUs as a different vendor (usually Nvidia)
    bool hideAmdGpu;

    /// Reports Intel GPUs as a different vendor (usually AMD)
    bool hideIntelGpu;

    /// Enable HDR
    bool enableHDR;

    /// Enable support for dummy composition swapchains
    bool enableDummyCompositionSwapchain;

    /// Limit frame rate
    int32_t maxFrameRate;

    /// Sync interval. Overrides the value
    /// passed to IDXGISwapChain::Present.
    int32_t syncInterval;

    /// Forced refresh rate, disable other modes
    uint32_t forceRefreshRate;

    /// Fake exclusive fullscreen as borderless: when a game enters fullscreen, do NOT change the
    /// real display mode — keep the desktop resolution/refresh and just cover the monitor with the
    /// window, letting the swapchain scale. Required for Streamline frame generation, which needs
    /// the native refresh headroom (a mode-set to e.g. 1080p@60 starves DLSS-G's generated frames)
    /// and is disrupted by the exclusive-fullscreen transition. Defaults on in this build.
    bool fakeFullscreen;

    /// EXPERIMENTAL: do a REAL exclusive-fullscreen mode change (keeping the game's resolution) but force
    /// the desktop's native refresh rate instead of the game-requested one — so the swapchain is the game
    /// resolution (the display engine stretches it to the panel) while DLSS-G keeps its refresh headroom.
    /// Takes precedence over fakeFullscreen.
    bool fullscreenNativeRefresh;
  };
  
}
