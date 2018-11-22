/**
 * Copyright 2018 Hu Peng
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
 */

#include "window.h"
#include <iostream>

namespace openglexample {

Window::Window(Proxy* proxy) : proxy_(proxy) {}

Window::~Window() {
  glfwTerminate();
}

bool Window::Init(int width, int height, const char* title) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // for mac os
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  this->window_ = glfwCreateWindow(width, height, title, NULL, NULL);
  if (this->window_ == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    return false;
  }

  glfwMakeContextCurrent(this->window_);

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(this->window_,
                                 Window::FrameBufferSizeCallback);

  return true;
}

void Window::FrameBufferSizeCallback(GLFWwindow* window,
                                     int width,
                                     int height) {
  glViewport(0, 0, width, height);
}

void Window::Loop() {
  while (!glfwWindowShouldClose(this->window_)) {
    this->ProcessInput();

    this->Draw();

    glfwSwapBuffers(this->window_);
    glfwPollEvents();
  }
}

void Window::ProcessInput() {
  if (this->proxy_ != NULL) {
    this->proxy_->ProcessInput();
  } else {
    if (glfwGetKey(this->window_, GLFW_KEY_SPACE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(this->window_, true);
    }
  }
}

void Window::Draw() {
  if (this->proxy_ != NULL) {
    this->proxy_->Draw();
  } else {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}

}  // namespace openglexample