/*
 *
 * Copyright (c) Microsoft Corporation.
 * All rights reserved.
 *
 * This code is licensed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files(the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions :
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
/**
 * @brief Defines ProtectionCommonSettings interface
 * 
 * @file protection_common_settings.h
 */

#ifndef API_MIP_PROTECTION_COMMON_SETTINGS_H_
#define API_MIP_PROTECTION_COMMON_SETTINGS_H_

#include <string>

#include "mip/mip_namespace.h"

MIP_NAMESPACE_BEGIN

/**
 * @brief Settings to use for protection operations
 */
class ProtectionCommonSettings {
public:
  ProtectionCommonSettings(std::string applicationScenarioId = std::string()) : mApplicationScenarioId(applicationScenarioId) {};
  /**
   * @brief Gets the scenario Id provided by the application which is used to correlation with the server.
   *
   * @return Application scenario Id
   */
  std::string GetApplicationScenarioId() const {
    return mApplicationScenarioId;
  };

  /**
   * @brief Sets the scenario Id provided by the application
   * 
   * @param The application scenario Id
   */
  void SetApplicationScenarioId(std::string applicationScenarioId) { mApplicationScenarioId = applicationScenarioId; };
  
  /** @cond DOXYGEN_HIDE */
  virtual ~ProtectionCommonSettings() {}

private:
  std::string mApplicationScenarioId;

  /** @endcond */
};

MIP_NAMESPACE_END

#endif // API_MIP_PROTECTION_Common_SETTINGS_H_
