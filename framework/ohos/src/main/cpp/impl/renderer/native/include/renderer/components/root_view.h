/*
 *
 * Tencent is pleased to support the open source community by making
 * Hippy available.
 *
 * Copyright (C) 2019 THL A29 Limited, a Tencent company.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "renderer/components/base_view.h"
#include "renderer/components/div_view.h"

namespace hippy {
inline namespace render {
inline namespace native {

class RootView : public DivView {
public:
  RootView(std::shared_ptr<NativeRenderContext> &ctx);
  ~RootView();

  void CreateArkUINodeImpl() override;
  void DestroyArkUINodeImpl() override;
  bool SetPropImpl(const std::string &propKey, const HippyValue &propValue) override;

  void OnDisappear() override;

private:
  void HandleRootEvent(const std::string &event, bool enable);
};

} // namespace native
} // namespace render
} // namespace hippy
