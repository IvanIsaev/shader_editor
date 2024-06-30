#include "vulkan_instance.h"

#include <QWidget>
#include <QApplication>
#include <QLoggingCategory>
#include <QSurface>
#include <QVulkanInstance>
#include <QVulkanWindow>

#include <algorithm>
#include <ranges>
#include <vector>

#include <range/v3/view/transform.hpp>
#include <range/v3/range/conversion.hpp>

namespace
{
    std::vector<const char*> extractSupportedExtensions(const QVulkanInstance& instance)
    {
        const auto suppurtedExtensions = instance.supportedExtensions();
        const auto extractExtensionName = [](const auto& qVulkanExtension) noexcept { return qVulkanExtension.name.data(); };

        return suppurtedExtensions | ranges::views::transform(extractExtensionName) | ranges::to<std::vector>();
    }

    std::vector<const char*> extractSupportedLayers(const QVulkanInstance& instance)
    {
        const auto suppurtedLayers = instance.supportedLayers();
        const auto extractLayerName = [](const auto& qVulkanLayer) { return qVulkanLayer.name.data(); };

        return suppurtedLayers | ranges::views::transform(extractLayerName) | ranges::to<std::vector>();
    }
}

int main(int argc, char *argv[])
{
    auto app = QApplication{argc, argv};
    QLoggingCategory::setFilterRules(QStringLiteral("qt.vulkan=true"));

    auto w2 = QWidget();
	w2.resize(512, 512);
	w2.show();
    
    w2.setUpdatesEnabled(false);
    

    //auto w = QVulkanWindow{};
    //w.resize(1024, 512);
    //w.setSurfaceType(QSurface::VulkanSurface);
    //w.show();

    auto windowSize = VkExtent2D{ static_cast<uint32_t>(w2.width()), static_cast<uint32_t>(w2.height()) };
    
    /*auto inst = QVulkanInstance{};
    extractSupportedExtensions(inst);
    extractSupportedLayers(inst);*/
    
    auto vulkanInstance = VulkanInstance{};
    vulkanInstance.initVulkan((HWND)w2.winId(), windowSize);
    //inst.setVkInstance(vulkanInstance.m_instance);

    //w.setVulkanInstance(&inst);
    
    vulkanInstance.drawFrame();

    return app.exec();
}

// Recording the command buffer
