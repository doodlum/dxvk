#include "dxvk_options.h"

namespace dxvk {

  DxvkOptions::DxvkOptions(const Config& config) {
    enableDebugUtils      = config.getOption<bool>    ("dxvk.enableDebugUtils",       false);
    enableMemoryDefrag    = config.getOption<Tristate>("dxvk.enableMemoryDefrag",     Tristate::Auto);
    numCompilerThreads    = config.getOption<int32_t> ("dxvk.numCompilerThreads",     0);
    enableGraphicsPipelineLibrary = config.getOption<Tristate>("dxvk.enableGraphicsPipelineLibrary", Tristate::Auto);
    enableDescriptorHeap  = config.getOption<Tristate>("dxvk.enableDescriptorHeap",   Tristate::Auto);
    enableDescriptorBuffer = config.getOption<Tristate>("dxvk.enableDescriptorBuffer", Tristate::Auto);
    enableUnifiedImageLayout = config.getOption<bool> ("dxvk.enableUnifiedImageLayouts", true);
    enableImplicitResolves = config.getOption<bool>   ("dxvk.enableImplicitResolves", true);
    trackPipelineLifetime = config.getOption<Tristate>("dxvk.trackPipelineLifetime",  Tristate::Auto);
    useRawSsbo            = config.getOption<Tristate>("dxvk.useRawSsbo",             Tristate::Auto);
    hud                   = config.getOption<std::string>("dxvk.hud", "");
    tearFree              = config.getOption<Tristate>("dxvk.tearFree",               Tristate::Auto);
    latencySleep          = config.getOption<Tristate>("dxvk.latencySleep",           Tristate::Auto);
    latencyTolerance      = config.getOption<int32_t> ("dxvk.latencyTolerance",       1000);
    disableNvLowLatency2  = config.getOption<Tristate>("dxvk.disableNvLowLatency2",   Tristate::Auto);
    hideIntegratedGraphics = config.getOption<bool>   ("dxvk.hideIntegratedGraphics", false);
    zeroMappedMemory      = config.getOption<bool>    ("dxvk.zeroMappedMemory",       false);
    // Skyrim fork: FSE default OFF. With FSE acquired, the plain (frame-gen-off)
    // swapchain delivers newest-frame-wins at refresh while the FFX frame-gen
    // wrap's inner swapchain never gets FSE (its pNext chain is stripped and the
    // prebuilt FFX DLL has no acquire path) — the two states then present with
    // different semantics, and every FG toggle pays an extra FSE re-acquisition
    // recreate ~1s after the switch. Disallowing FSE everywhere keeps every
    // swapchain on identical (tearing/immediate) presentation. Opt back in via
    // dxvk.conf if exclusive scanout is ever preferred over consistency.
    allowFse              = config.getOption<bool>    ("dxvk.allowFse",               false);
    deviceFilter          = config.getOption<std::string>("dxvk.deviceFilter",        "");
    lowerSinCos           = config.getOption<Tristate>("dxvk.lowerSinCos",            Tristate::Auto);
    tilerMode             = config.getOption<Tristate>("dxvk.tilerMode",              Tristate::Auto);

    auto budget = config.getOption<int32_t>("dxvk.maxMemoryBudget", 0);
    maxMemoryBudget = VkDeviceSize(std::max(budget, 0)) << 20u;
  }

}
