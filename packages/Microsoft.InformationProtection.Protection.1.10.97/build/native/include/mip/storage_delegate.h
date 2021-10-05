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
 * @brief Defines StorageDelegate interface
 * 
 * @file storage_delegate.h
 */

#ifndef API_MIP_STORAGE_DELEGATE_H_
#define API_MIP_STORAGE_DELEGATE_H_

#include <string>
#include <vector>

#include "mip/delegate_response.h"
#include "mip/mip_namespace.h"
#include "mip/storage_table.h"

MIP_NAMESPACE_BEGIN

/**
 * @brief Describes the MIP component to be used in the application.
 */
enum class MipComponent : unsigned int {
  Policy   = 0, /* For Policy sdk */
  File    = 1, /* For File sdk */
  Protection = 2, /* For Protection sdk */
};

/**
* @brief A delegate response type for #StorageTable
*/
typedef mip::DelegateResponse<mip::StorageTable> StorageTableResult;

/**
* @brief A class that defines the interface to the MIP SDK storage for caching
*/
class StorageDelegate {
public:

  /**
   * @brief Creates an instance of a storage table that MIP uses for caching. If a table already exists & schema doesnt match with @p allColumns , implementatiion should drop the table and re-create new one.
   * 
   * @param path Default path for mip storage.
   * @param mipComponent #MipComponent associated with this table.
   * @param tableName Name of the table to create.
   * @param allColumns All columns represented in the table.
   * @param encryptedColumns Represents the set of columns within @p allColumns that need to be encrypted. This argument is only populated if #CacheStorageType (configured via the profile settings) is not @p OnDiskEncrypted, 
   * otherwise the MIP SDK will internally encrypt the column data for these columns and modify their name with an 'encrypt_' prefix.
   * @param keyColumns Key columns used to identify unique table entries.
   * 
   * @return A delegate response which either contains an instance of #StorageTable or an exception.
   */
  virtual mip::StorageTableResult CreateStorageTable(
      const std::string& path,
      const MipComponent mipComponent,
      const std::string& tableName,
      const std::vector<std::string>& allColumns,
      const std::vector<std::string>& encryptedColumns,
      const std::vector<std::string>& keyColumns) const = 0;

  /**
   * @brief Settings used by StorageDelegate
   */
  class StorageSettings {
  public:
    /**
     * @brief Interface for configuring the storage settings.
     * 
     * @param isRemoteStore represents if store is remote. This will be taken into account for internal encryption.
     * @param isInMemoryStorageSupported Declares whether the delegate supports in-memory storage.
     */
    StorageSettings(
        bool isRemoteStorage,
        bool isInMemoryStorageSupported)
        : mIsRemoteStorage(isRemoteStorage),
          mIsInMemoryStorageSupported(isInMemoryStorageSupported) {}

    /**
     * @brief Gets whether remote storage is used or not.
     *
     * @return whether remote storage is used or not.
     */
    bool IsRemoteStorage() const { return mIsRemoteStorage; }

    /**
     * @brief Gets whether the delegate supports in-memory storage.
     *
     * @return \p true if the delegate supports in-memory storage.
     */
    bool IsInMemoryStorageSupported() const { return mIsInMemoryStorageSupported; }
    
    /** @cond DOXYGEN_HIDE */
    ~StorageSettings() { }
    StorageSettings() : StorageSettings(false, true) {}
  private:
    bool mIsRemoteStorage;
    bool mIsInMemoryStorageSupported;
    /** @endcond */
  };

  /**
   * @brief Gets settings used by #StorageDelegate.
   * 
   * @return settings used by #StorageDelegate.
   */
  virtual StorageSettings GetSettings() const = 0;

  /** @cond DOXYGEN_HIDE */
  virtual ~StorageDelegate() {}

protected:
  StorageDelegate() {}
  /** @endcond */
};

MIP_NAMESPACE_END
#endif // API_MIP_STORAGE_DELEGATE_H_

