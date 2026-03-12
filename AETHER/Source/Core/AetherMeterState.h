#pragma once
#include <atomic>

struct AetherMeterState
{
    std::atomic<float> outRms { 0.0f };
    std::atomic<float> wetRms { 0.0f };
    std::atomic<float> dryRms { 0.0f };
    std::atomic<float> duckDb { 0.0f };
};
