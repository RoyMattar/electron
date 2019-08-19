// Copyright (c) 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_RENDERER_HOST_ELECTRON_RENDER_MESSAGE_FILTER_H_
#define SHELL_BROWSER_RENDERER_HOST_ELECTRON_RENDER_MESSAGE_FILTER_H_

#include <string>
#include <vector>

#include "content/public/browser/browser_context.h"
#include "content/public/browser/browser_message_filter.h"

class GURL;

namespace electron {
namespace api {
class Session;
}
}  // namespace electron

namespace predictors {
class PreconnectManager;
}

// This class filters out incoming Chrome-specific IPC messages for the renderer
// process on the IPC thread.
class ElectronRenderMessageFilter : public content::BrowserMessageFilter {
 public:
  explicit ElectronRenderMessageFilter(electron::api::Session* session);

  // content::BrowserMessageFilter methods:
  bool OnMessageReceived(const IPC::Message& message) override;

 private:
  ~ElectronRenderMessageFilter() override;

  void OnPreconnect(int render_frame_id,
                    const GURL& url,
                    bool allow_credentials,
                    int count);

  electron::api::Session* session_;

  DISALLOW_COPY_AND_ASSIGN(ElectronRenderMessageFilter);
};

#endif  // SHELL_BROWSER_RENDERER_HOST_ELECTRON_RENDER_MESSAGE_FILTER_H_