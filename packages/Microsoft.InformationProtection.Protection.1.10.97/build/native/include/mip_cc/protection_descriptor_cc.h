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
 * @brief Defines C-Style ProtectionDescriptor interface
 * 
 * @file protection_descriptor_cc.h
 */

#ifndef API_MIP_PROTECTION_DESCRIPTOR_CC_H_
#define API_MIP_PROTECTION_DESCRIPTOR_CC_H_

#include <time.h>

#include "mip_cc/common_types_cc.h"
#include "mip_cc/dictionary_cc.h"
#include "mip_cc/error_cc.h"
#include "mip_cc/result_cc.h"

typedef mip_cc_handle* mip_cc_protection_descriptor;

/**
 * @brief A description of whether protection is defined by a template or ad-hoc
 */
typedef enum {
  MIP_PROTECTION_TYPE_TEMPLATE_BASED = 0, /**< Based on an RMS template */
  MIP_PROTECTION_TYPE_CUSTOM = 1,         /**< Custom, ad-hoc protection */
} mip_cc_protection_type;

/**
 * @brief A group of users and the rights associated with them
 */
typedef struct {
  const char** users;  /**< List of users */
  int64_t usersCount;  /**< Number of users */
  const char** rights; /**< List of rights */
  int64_t rightsCount; /**< Number of rights */
} mip_cc_user_rights;

/**
 * @brief A group of users and the roles associated with them
 */
typedef struct {
  const char** users;  /**< List of users */
  int64_t usersCount;  /**< Number of users */
  const char** roles; /**< List of roles */
  int64_t rolesCount; /**< Number of roles */
} mip_cc_user_roles;

/**
 * @brief Creates a protection descriptor whose access permissions are defined by an RMS template
 *
 * @param templateId Template ID
 * @param signedAppData App-specific data (cleartext) that is signed into the publishing license
 * @param protectionDescriptor [Output] Newly-created protection descriptor instance
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 *
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_CreateProtectionDescriptorFromTemplate(
    const char* templateId,
    const mip_cc_dictionary signedAppData,
    mip_cc_protection_descriptor* protectionDescriptor,
    mip_cc_error* errorInfo);

/**
 * @brief Creates a protection descriptor whose access permissions are defined by users and rights
 *
 * @param userRights Groups of users and their rights
 * @param userRightsCount Number of user/rights groups
 * @param name Protection name
 * @param referrer Referrer address (a URI displayable to a user that provides information on how to gain access)
 * @param contentValidUntil Protection expiration time
 * @param allowOfflineAccess Determines whether a license to consume content can be cached locally
 * @param encryptedAppData App-specific data (cleartext) that is encrypted into the publishing license
 * @param signedAppData App-specific data (cleartext) that is signed into the publishing license
 * @param protectionDescriptor [Output] Newly-created protection descriptor instance
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 *
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_CreateProtectionDescriptorFromUserRights(
    const mip_cc_user_rights* userRights,
    const int64_t userRightsCount,
    const char* name,
    const char* description,
    const char* referrer,
    const time_t* contentValidUntil,
    const bool allowOfflineAccess,
    const mip_cc_dictionary encryptedAppData,
    const mip_cc_dictionary signedAppData,
    mip_cc_protection_descriptor* protectionDescriptor,
    mip_cc_error* errorInfo);

/**
 * @brief Creates a protection descriptor whose access permissions are defined by users and roles
 *
 * @param userRoles Groups of users and their roles
 * @param userRolesCount Number of user/roles groups
 * @param name Protection policy name
 * @param referrer Referrer address (a URI displayable to a user that provides information on how to gain access)
 * @param contentValidUntil Protection expiration time
 * @param allowOfflineAccess Determines whether a license to consume content can be cached locally
 * @param encryptedAppData App-specific data (cleartext) that is encrypted into the publishing license
 * @param signedAppData App-specific data (cleartext) that is signed into the publishing license
 * @param protectionDescriptor [Output] Newly-created protection descriptor instance
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 *
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_CreateProtectionDescriptorFromUserRoles(
    const mip_cc_user_roles* userRoles,
    const int64_t userRolesCount,
    const char* name,
    const char* description,
    const char* referrer,
    const time_t* contentValidUntil,
    const bool allowOfflineAccess,
    const mip_cc_dictionary encryptedAppData,
    const mip_cc_dictionary signedAppData,
    mip_cc_protection_descriptor* protectionDescriptor,
    mip_cc_error* errorInfo);

/**
 * @brief Gets type of protection, whether it is defined by an RMS template or not
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param protectionType [Output] Protection type
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetProtectionType(
    const mip_cc_protection_descriptor protectionDescriptor,
    mip_cc_protection_type* protectionType,
    mip_cc_error* errorInfo);

/**
 * @brief Gets size of buffer required to store owner
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param ownerSize [Output] Size of buffer to hold owner (in number of chars)
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetOwnerSize(
    const mip_cc_protection_descriptor protectionDescriptor,
    int64_t* ownerSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets protection owner
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param ownerBuffer [Output] Buffer the owner will be copied into.
 * @param ownerBufferSize Size (in number of chars) of the ownerBuffer.
 * @param actualOwnerSize [Output] Number of chars written to the buffer
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 * 
 * @note If ownerBuffer is null or insufficient, MIP_RESULT_ERROR_INSUFFICIENT_BUFFER will be returned and
 *       actualOwnerSize will be set to the minimum required buffer size.
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetOwner(
    const mip_cc_protection_descriptor protectionDescriptor,
    char* ownerBuffer,
    const int64_t ownerBufferSize,
    int64_t* actualOwnerSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets size of buffer required to store name
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param nameSize [Output] Size of buffer to hold name (in number of chars)
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetNameSize(
    const mip_cc_protection_descriptor protectionDescriptor,
    int64_t* nameSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets protection name
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param nameBuffer [Output] Buffer the name will be copied into.
 * @param nameBufferSize Size (in number of chars) of the nameBuffer.
 * @param actualNameSize [Output] Number of chars written to the buffer
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 * 
 * @note If nameBuffer is null or insufficient, MIP_RESULT_ERROR_INSUFFICIENT_BUFFER will be returned and
 *       actualNameSize will be set to the minimum required buffer size.
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetName(
    const mip_cc_protection_descriptor protectionDescriptor,
    char* nameBuffer,
    const int64_t nameBufferSize,
    int64_t* actualNameSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets size of buffer required to store description
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param descriptionSize [Output] Size of buffer to hold description (in number of chars)
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetDescriptionSize(
    const mip_cc_protection_descriptor protectionDescriptor,
    int64_t* descriptionSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets protection description
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param descriptionBuffer [Output] Buffer the description will be copied into.
 * @param descriptionBufferSize Size (in number of chars) of the descriptionBuffer.
 * @param actualDescriptionSize [Output] Number of chars written to the buffer
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 * 
 * @note If descriptionBuffer is null or insufficient, MIP_RESULT_ERROR_INSUFFICIENT_BUFFER will be returned and
 *       actualDescriptionSize will be set to the minimum required buffer size.
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetDescription(
    const mip_cc_protection_descriptor protectionDescriptor,
    char* descriptionBuffer,
    const int64_t descriptionBufferSize,
    int64_t* actualDescriptionSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets template ID
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param templateId [Output] Template ID associated with protection
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetTemplateId(
    const mip_cc_protection_descriptor protectionDescriptor,
    mip_cc_guid* templateId,
    mip_cc_error* errorInfo);

/**
 * @brief Gets label ID
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param labelId [Output] Label ID associated with protection
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetLabelId(
    const mip_cc_protection_descriptor protectionDescriptor,
    mip_cc_guid* labelId,
    mip_cc_error* errorInfo);

/**
 * @brief Gets content ID
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param contentId [Output] Content ID associated with protection
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetContentId(
    const mip_cc_protection_descriptor protectionDescriptor,
    mip_cc_guid* contentId,
    mip_cc_error* errorInfo);

/**
 * @brief Gets whether or not content has an expiration time or not
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param doesContentExpire [Output] Whether or not content expires
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_DoesContentExpire(
    const mip_cc_protection_descriptor protectionDescriptor,
    bool* doesContentExpire,
    mip_cc_error* errorInfo);

/**
 * @brief Gets protection expiration time (in seconds since epoch)
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param contentValidUntil [Output] Content expiration time (in seconds since epoch)
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetContentValidUntil(
    const mip_cc_protection_descriptor protectionDescriptor,
    int64_t* contentValidUntil,
    mip_cc_error* errorInfo);

/**
 * @brief Gets whether or not offline access is allowed
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param doesAllowOfflineAccess [Output] Whether or not offline access is allowed
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_DoesAllowOfflineAccess(
    const mip_cc_protection_descriptor protectionDescriptor,
    bool* doesAllowOfflineAccess,
    mip_cc_error* errorInfo);

/**
 * @brief Gets size of buffer required to store referrer
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param referrerSize [Output] Size of buffer to hold referrer (in number of chars)
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetReferrerSize(
    const mip_cc_protection_descriptor protectionDescriptor,
    int64_t* referrerSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets protection referrer
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param referrerBuffer [Output] Buffer the referrer will be copied into.
 * @param referrerBufferSize Size (in number of chars) of the referrerBuffer.
 * @param actualReferrerSize [Output] Number of chars written to the buffer
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 * 
 * @note If referrerBuffer is null or insufficient, MIP_RESULT_ERROR_INSUFFICIENT_BUFFER will be returned and
 *       actualReferrerSize will be set to the minimum required buffer size.
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetReferrer(
    const mip_cc_protection_descriptor protectionDescriptor,
    char* referrerBuffer,
    const int64_t referrerBufferSize,
    int64_t* actualReferrerSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets size of buffer required to store double key URL
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param url [Output] Size of buffer to hold double key URL (in number of chars)
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetDoubleKeyUrlSize(
    const mip_cc_protection_descriptor protectionDescriptor,
    int64_t* urlSize,
    mip_cc_error* errorInfo);

/**
 * @brief Gets double key URL
 * 
 * @param protectionDescriptor Descriptor associated with protected content
 * @param urlBuffer [Output] Buffer the url will be copied into.
 * @param urlBufferSize Size (in number of chars) of the urlBuffer.
 * @param actualUrlSize [Output] Number of chars written to the buffer
 * @param errorInfo [Output] (Optional) Failure info if operation result is error
 * 
 * @return Result code indicating success or failure
 * 
 * @note If urlBuffer is null or insufficient, MIP_RESULT_ERROR_INSUFFICIENT_BUFFER will be returned and
 *       actualUrlSize will be set to the minimum required buffer size.
 */
MIP_CC_API(mip_cc_result) MIP_CC_ProtectionDescriptor_GetDoubleKeyUrl(
    const mip_cc_protection_descriptor protectionDescriptor,
    char* urlBuffer,
    const int64_t urlBufferSize,
    int64_t* actualUrlSize,
    mip_cc_error* errorInfo);

/**
 * @brief Release resources associated with a protection descriptor
 * 
 * @param protectionDescriptor Protection descriptor to be released
 */
MIP_CC_API(void) MIP_CC_ReleaseProtectionDescriptor(mip_cc_protection_descriptor protectionDescriptor);

#endif // API_MIP_PROTECTION_DESCRIPTOR_CC_H_