#pragma once

#include <exl/hook/trampoline.hpp>
#include <ml/Log/Log.h>
#include <vector>

#include "Library/Factory/Factory.h"
#include "Player/PlayerFactory.h"
#include "Scene/ProjectActorFactory.h"
#include "Scene/ProjectAreaFactory.h"
#include "Scene/ProjectCameraPoserFactory.h"

namespace ml {

/**
 * @brief A class for hooking into a factory and adding custom entries to it
 * @tparam TFactory The factory to hook into
 * @tparam TFactoryEntry The type of the factory entry
 */
template <typename TFactory, typename TFactoryEntry>
class FactoryHook : public exl::hook::impl::TrampolineHook<FactoryHook<TFactory, TFactoryEntry>> {
public:
    using Base = exl::hook::impl::TrampolineHook<FactoryHook>;
    using FactoryEntry = TFactoryEntry;
    friend Base;

    static void RegisterEntry(const TFactoryEntry& entry) {
        if (ContainsEntry(entry.name)) {
            return;
        }

        sCustomEntries.push_back(entry);
    }

    /**
     * @brief Installs the factory hook at the provided symbol, if the factory was not already installed
     * @param factoryName The name of the factory to install
     * @param symbol The symbol of the factory constructor to hook into
     */
    static void SafeInstall(const char* factoryName, const char* symbol) {
        if (!sIsInstalled) {
            LOG_INFORMATION("Installing %s factory at symbol %s", factoryName, symbol);
            Base::InstallAtSymbol(symbol);
            sIsInstalled = true;
        } else {
            LOG_VERBOSE("Factory %s was already installed, skipping installation at symbol %s", factoryName, symbol);
        }
    }

    /**
     * @brief Installs the factory hook at the provided offset, if the factory hook was not already installed
     * @param factoryName The name of the factory to install
     * @param offset The offset of the factory constructor to hook into
     */
    static void SafeInstallAtOffset(const char* factoryName, uint64_t offset) {
        if (!sIsInstalled) {
            LOG_INFORMATION("Installing %s factory at offset 0x%lx", factoryName, offset);
            Base::InstallAtOffset(offset);
            sIsInstalled = true;
        } else {
            LOG_VERBOSE("Factory %s was already installed, skipping installation at offset 0x%lx", factoryName, offset);
        }
    }

private:
    inline static std::vector<TFactoryEntry> sCustomEntries;
    inline static TFactoryEntry* sCombinedEntries;
    inline static bool sIsInstalled = false;

    static void Callback(TFactory* factory) {
        Base::Orig(factory);

        size_t customEntryCount = sCustomEntries.size();
        if (customEntryCount == 0) {
            return;
        }

        int vanillaEntryCount = factory->mNumFactoryEntries;
        int combinedEntryCount = vanillaEntryCount + customEntryCount;

        sCombinedEntries = new TFactoryEntry[combinedEntryCount]; // think the scene heap is set here so no need to free the buffer

        for (int i = 0; i < vanillaEntryCount; i++) {
            sCombinedEntries[i] = factory->mFactoryEntries[i];
        }

        for (int i = vanillaEntryCount, j = 0; j < customEntryCount; i++, j++) {
            sCombinedEntries[i] = sCustomEntries[j];
            LOG_TRACE("Added custom entry %s to factory", sCombinedEntries[i].name);
        }

        factory->mFactoryEntries = sCombinedEntries;
        factory->mNumFactoryEntries = combinedEntryCount;
    }

    template <typename B, typename D>
    static B* CreateEntryFunction(const char* entryName) {
        return new D(entryName);
    }

    static bool ContainsEntry(const char* entryName) {
        return std::find_if(sCustomEntries.begin(), sCustomEntries.end(), [entryName](const TFactoryEntry& entry) {
            return std::strcmp(entry.name, entryName) == 0;
        }) != sCustomEntries.end();
    }

    FactoryHook() {}
};

using ActorFactoryHook = ml::FactoryHook<ProjectActorFactory, al::NameToCreator<al::ActorCreatorFunction>>;
using AreaFactoryHook = ml::FactoryHook<ProjectAreaFactory, al::NameToCreator<al::AreaCreatorFunction>>;
using CameraPoserFactoryHook = ml::FactoryHook<ProjectCameraPoserFactory, al::NameToCreator<al::CameraPoserCreatorFunction>>;
using PlayerFactoryHook = ml::FactoryHook<PlayerFactory, al::NameToCreator<PlayerCreatorFunction>>;

}
