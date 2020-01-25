/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef TESTS_TESTSCENE_H
#define TESTS_TESTSCENE_H

#include <string>
#include <unordered_map>

namespace android {
namespace uirenderer {
class RenderNode;

#if HWUI_NEW_OPS
class RecordingCanvas;
typedef RecordingCanvas TestCanvas;
#else
class DisplayListCanvas;
typedef DisplayListCanvas TestCanvas;
#endif

namespace test {

class TestScene {
public:
    struct Options {
        int count = 0;
        int reportFrametimeWeight = 0;
    };

    template <class T>
    static test::TestScene* simpleCreateScene(const TestScene::Options&) {
        return new T();
    }

    typedef test::TestScene* (*CreateScene)(const TestScene::Options&);

    struct Info {
        std::string name;
        std::string description;
        CreateScene createScene;
    };

    class Registrar {
    public:
        Registrar(const TestScene::Info& info) {
            TestScene::registerScene(info);
        }
    private:
        Registrar() = delete;
        Registrar(const Registrar&) = delete;
        Registrar& operator=(const Registrar&) = delete;
    };

    virtual ~TestScene() {}
    virtual void createContent(int width, int height, TestCanvas& renderer) = 0;
    virtual void doFrame(int frameNr) = 0;

    static std::unordered_map<std::string, Info>& testMap();
    static void registerScene(const Info& info);
};

} // namespace test
} // namespace uirenderer
} // namespace android

#endif /* TESTS_TESTSCENE_H */
