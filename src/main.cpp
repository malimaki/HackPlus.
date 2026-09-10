#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCScheduler.hpp>
#include <Geode/binding/FMODAudioEngine.hpp>

using namespace geode::prelude;

class $modify(HPPlayLayer, PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* object) {
        if (Mod::get()->getSettingValue<bool>("noclip")) {
            return;
        }
        PlayLayer::destroyPlayer(player, object);
    }
};

class $modify(HPScheduler, CCScheduler) {
    void update(float dt) {
        auto mod = Mod::get();

        if (!mod->getSettingValue<bool>("speedhack-enabled")) {
            CCScheduler::update(dt);
            return;
        }

        float mult = static_cast<float>(mod->getSettingValue<double>("speedhack-multiplier"));
        CCScheduler::update(dt * mult);

        if (mod->getSettingValue<bool>("speedhack-audio")) {
            if (auto engine = FMODAudioEngine::sharedEngine()) {
                if (engine->m_globalChannel) {
                    engine->m_globalChannel->setPitch(mult);
                }
            }
        }
    }
};
