#pragma once

#include "pch.h"
#include "Utils.h"
#include "BetterPause.h"
#include "BetterPauseManager.h"

#include <Geode/modify/AppDelegate.hpp>
#include <Geode/modify/CurrencyRewardLayer.hpp>
#include <Geode/modify/CustomSongWidget.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/IDManager.hpp>
#include <array>

using namespace geode::prelude;

namespace {
    void collectModButtons(cocos2d::CCNode* node,
        std::vector<CCMenuItemSpriteExtra*>& buttons) {
        if (auto button = typeinfo_cast<CCMenuItemSpriteExtra*>(node)) {
            static constexpr std::array<std::string_view, 7> vanillaIDs {
                "edit-button", "full-restart-button", "practice-button",
                "play-button", "exit-button", "retry-button", "options-button"
            };
            auto const id = button->getID().view();
            if (std::find(vanillaIDs.begin(), vanillaIDs.end(), id) == vanillaIDs.end()) {
                auto image = button->getNormalImage();
                auto const size = image ? image->boundingBox().size : button->boundingBox().size;
                if (size.width <= 80.f && size.height <= 80.f) {
                    buttons.push_back(button);
                    return;
                }
            }
        }

        for (auto child : node->getChildrenExt<cocos2d::CCNode*>()) {
            collectModButtons(child, buttons);
        }
    }

    bool hideVanillaPauseBranch(cocos2d::CCNode* node) {
        auto const id = node->getID().view();

        if (id == "background" ||
            typeinfo_cast<cocos2d::CCLayerColor*>(node) != nullptr) {
            node->setVisible(true);
            return true;
        }

        if (id.find('/') != std::string_view::npos) {
            node->setVisible(true);
            return true;
        }

        bool containsModNode = false;
        for (auto child : node->getChildrenExt<cocos2d::CCNode*>()) {
            containsModNode |= hideVanillaPauseBranch(child);
        }

        node->setVisible(containsModNode);
        return containsModNode;
    }
}

class $modify(BetterPauseLayerHook, PauseLayer) {
    static void onModify(auto& self) {
        (void)self.setHookPriorityAfterPost(
            "PauseLayer::customSetup", "elohmrow.death_tracker"
        );
        (void)self.setHookPriorityAfterPost(
            "PauseLayer::customSetup", "khronophobia.inputs_viewer"
        );
    }

    void customSetup() {
        PauseLayer::customSetup();

        NodeIDs::provideFor(this);

        auto const useBetterPause =
            BetterPauseManager::sharedState()->m_pSwitchPause.m_uOffset == 0;
        std::vector<CCMenuItemSpriteExtra*> modButtons;
        if (useBetterPause) {
            collectModButtons(this, modButtons);

            for (auto child : this->getChildrenExt<cocos2d::CCNode*>()) {
                hideVanillaPauseBranch(child);
            }
        }

        auto menu = BetterPause::create(this, false, useBetterPause);
        this->addChild(menu, 100);

        if (useBetterPause && menu) {
            menu->setupScrollableButtons(modButtons);
        }
    }
};

class $modify(BetterPauseSongWidgetHook, CustomSongWidget) {
    void updateSongInfo() {
        auto const oldScale = this->getScale();
        auto const paused = Utils::getplayLayerA() && Utils::getplayLayerA()->m_isPaused;
        if (paused) this->setScale(1.f);
        CustomSongWidget::updateSongInfo();
        if (paused) this->setScale(oldScale);
    }
};

class $modify(BetterPauseCurrencyRewardHook, CurrencyRewardLayer) {
    bool init(int orbs, int stars, int moons, int diamonds,
        CurrencySpriteType demonKey, int keyCount, CurrencySpriteType shardType,
        int shardsCount, cocos2d::CCPoint position, CurrencyRewardType rewardType,
        float yOffset, float time) {
        if (!CurrencyRewardLayer::init(orbs, stars, moons, diamonds, demonKey,
            keyCount, shardType, shardsCount, position, rewardType, yOffset, time)) {
            return false;
        }

        if (auto playLayer = Utils::getplayLayerA();
            playLayer && playLayer->m_isPaused && this->getChildren()->count() > 2) {
            if (auto node = typeinfo_cast<cocos2d::CCNode*>(this->getChildren()->objectAtIndex(2))) {
                node->setPositionX(node->getPositionX() - 61.f);
                auto const desiredY = Utils::winSize().height + 170.f;
                node->setPositionY(node->getParent()->convertToNodeSpace({ 0.f, desiredY }).y);
            }
        }
        return true;
    }
};

class $modify(BetterPauseMoreOptionsHook, MoreOptionsLayer) {
    bool init() {
        BetterPause::quickSettings_Name.clear();
        BetterPause::quickSettings_Desc.clear();
        BetterPause::quickSettings_Key.clear();
        return MoreOptionsLayer::init();
    }

    void addToggle(char const* name, char const* key, char const* info) {
        MoreOptionsLayer::addToggle(name, key, info);
        BetterPause::quickSettings_Name.emplace_back(name ? name : "");
        BetterPause::quickSettings_Desc.emplace_back(info ? info : "");
        BetterPause::quickSettings_Key.emplace_back(key ? key : "");
    }
};

class $modify(BetterPauseAppDelegateHook, AppDelegate) {
    void trySaveGame(bool force) {
        BetterPauseManager::sharedState()->save();
        AppDelegate::trySaveGame(force);
    }
};
