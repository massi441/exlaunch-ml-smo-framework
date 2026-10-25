#pragma once

#include <exl/hook/trampoline.hpp>
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
     * @brief Installs the factory hook at the provided symbol
     * @param symbol The symbol of the factory constructor to hook into
     */
    static void Install(const char* symbol) {
        if (!sIsInstalled) {
            Base::InstallAtSymbol(symbol);
        }
    }

    /**
     * @brief Installs the factory hook at the provided offset
     * @param offset The offset of the factory constructor to hook into
     */
    static void InstallAtOffset(uint64_t offset) {
        if (!sIsInstalled) {
            Base::InstallAtOffset(offset);
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

void InstallFactoryHooks();

}
