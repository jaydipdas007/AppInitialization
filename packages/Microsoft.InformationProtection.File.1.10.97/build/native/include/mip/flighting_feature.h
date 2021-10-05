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
 * @brief A file containing the FlightingFeature definition
 * 
 * @file flighting_feature.h
 */

#ifndef API_MIP_FLIGHTING_FEATURE_H_
#define API_MIP_FLIGHTING_FEATURE_H_

#include <map>

#include "mip/mip_namespace.h"

MIP_NAMESPACE_BEGIN

/**
* @brief Defines new features by name
*/
enum FlightingFeature : unsigned int {
  ServiceDiscovery                            = 0,  /**< Rely on separate HTTP call to determine RMS service endpoints */
  AuthInfoCache                               = 1,  /**< Cache OAuth2 challenges per domain/tenant to reduce unnecessary 401 responses. Disable for apps/services that manage their own HTTP auth (like SPO, Edge) */
  LinuxEncryptedCache                         = 2,  /**< Enable encrypted caching for Linux platforms (Please read the prerequisites for this feature) */
  SingleDomainName                            = 3,  /**< Enable single company name for dns lookup. e.g. https://corprights */
  PolicyAuth                                  = 4,  /**< Enable automatic HTTP authentication for requests sent to Policy service. Disable for apps/services that manage their own HTTP auth (like SPO, Edge) */
  UrlRedirectCache                            = 5,  /**< Cache URL redirects to reduce number of HTTP operations */
  PreLicensing                                = 6,  /**< Enable pre license api check */
  DoubleKey                                   = 7,  /**< Enable double key protection feature to use a customer key to encrypt with */
  VariablePolicyTtl                           = 8,  /**< Enable variable policy time to live, disabling reverts to infinite policy*/
  VariableTextMarking                         = 9,  /**< Enable variable text marking*/
  OptimizePdfMemory                           = 10, /**< Enable Optimize PDF Memory Creator in protect and unprotect PDF files */
  RemoveDeletedLabelMd                        = 11, /**< Enable removing delete label's meta data */
  EnforceTls12                                = 12, /**< Enforce TLS 1.2 for non-ADRMS HTTPS connections */
  MatchCloudType                              = 13, /**< Enable matching of cloud type settings during of engines creation */
  EnableAuditAndTelemetryForSovereignClouds   = 14, /**< Enable telemetry and audit events for sovereign clouds */
  EnableActionIdForV0Metadata                 = 15, /**< Write ActionID metadata for content using version 0 */
  PowerBiCustomSettings                       = 16, /**< Whether or not to add power bi settings to custom settings */
  KeyStoreBasedOnStoragePath                  = 17,  /**< Whether or not to use storage path in keystore */
  EventDateTimeTokenUseUtc                    = 18, /**< Whether to replace ${Event.DateTime} with a UTC timestamp */
};

/**
 * @brief Gets whether or not a feature is enabled by default
 * 
 * @return Default state of flighting features
 */
inline const std::map<FlightingFeature, bool>& GetDefaultFeatureSettings() {
  static std::map<FlightingFeature, bool> kDefaultFeatureSettings = {
    // Feature name                             Default value
    { FlightingFeature::ServiceDiscovery,                           false },
    { FlightingFeature::AuthInfoCache,                              true  },
    { FlightingFeature::LinuxEncryptedCache,                        false },
    { FlightingFeature::SingleDomainName,                           true  },
    { FlightingFeature::PolicyAuth,                                 true  },
    { FlightingFeature::UrlRedirectCache,                           true  },
    { FlightingFeature::PreLicensing,                               true  },
    { FlightingFeature::DoubleKey,                                  false },
    { FlightingFeature::VariablePolicyTtl,                          true  },
    { FlightingFeature::VariableTextMarking,                        true  },
    { FlightingFeature::OptimizePdfMemory,                          true  },
    { FlightingFeature::RemoveDeletedLabelMd,                       true  },
    { FlightingFeature::EnforceTls12,                               true  },
    { FlightingFeature::MatchCloudType,                             false },
    { FlightingFeature::EnableAuditAndTelemetryForSovereignClouds,  false },
    { FlightingFeature::EnableActionIdForV0Metadata,                true  },
    { FlightingFeature::PowerBiCustomSettings,                      true  },
    {FlightingFeature::KeyStoreBasedOnStoragePath,                  true  },
    { FlightingFeature::EventDateTimeTokenUseUtc,                   false },

  };
  return kDefaultFeatureSettings;
}

MIP_NAMESPACE_END
#endif  // API_MIP_FLIGHTING_FEATURE_H_

