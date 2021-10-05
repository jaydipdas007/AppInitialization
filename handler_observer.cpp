#include "handler_observer.h"
using std::shared_ptr;
using std::promise;
using std::exception_ptr;

void ProtectionHandlerObserver::OnCreateProtectionHandlerSuccess(
    const shared_ptr<mip::ProtectionHandler>& protectionHandler, const shared_ptr<void>& context)
{
    auto createProtectionHandlerPromise = static_cast<promise<shared_ptr<mip::ProtectionHandler>>*>(context.get());
    createProtectionHandlerPromise->set_value(protectionHandler);
};

void ProtectionHandlerObserver::OnCreateProtectionHandlerFailure(
    const exception_ptr& Failure, const shared_ptr<void>& context)
{
    auto createProtectionHandlerPromise = static_cast<promise<shared_ptr<mip::ProtectionHandler>>*>(context.get());
        createProtectionHandlerPromise->set_exception(Failure);
};