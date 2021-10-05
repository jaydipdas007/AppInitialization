#pragma once
#include <memory>
#include "mip/protection/protection_engine.h"
using std::shared_ptr;
using std::exception_ptr;

class ProtectionHandlerObserver final : public mip::ProtectionHandler::Observer
{
public:
    ProtectionHandlerObserver()
    {
    }
    void OnCreateProtectionHandlerSuccess(const shared_ptr<mip::ProtectionHandler>& protectionHandler, const shared_ptr<void>& context) override;
    void OnCreateProtectionHandlerFailure(const exception_ptr& Failure, const shared_ptr<void>& context) override;
};

