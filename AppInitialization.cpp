// AppInitialization.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "mip/mip_context.h"  
#include "filehandler_observer.h" 
#include "mip/file/file_handler.h"
#include "mip/file/protection_settings.h"
#include "mip/protection/protection_descriptor_builder.h"
#include "mip/protection_descriptor.h"
#include "auth_delegate.h"
#include "consent_delegate.h"
#include "profile_observer.h"
#include "handler_observer.h"

using std::promise;
using std::future;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::cout;
using mip::ApplicationInfo;
using mip::FileProfile;
using mip::FileEngine;
using mip::FileHandler;
using mip::ProtectionSettings;
using mip::ProtectionDescriptor;
using mip::ProtectionDescriptorBuilder;
using mip::ProtectionHandler;
using mip::ProtectionEngine;
using std::endl;

int main()
{
    // Construct/initialize objects required by the application's profile object
    // ApplicationInfo object (App ID, name, version)
    ApplicationInfo mAppInfo { "64c62ae2-01c3-44af-871d-84d7cb1d039f",
                            "AppInitialization",
                            "1.1.0.0" };

    // Create MipConfiguration object.
    std::shared_ptr<mip::MipConfiguration> mipConfiguration = std::make_shared<mip::MipConfiguration>(mAppInfo,
        "mip_data",
        mip::LogLevel::Trace,
        false);


    std::shared_ptr<mip::MipContext> mMipContext = mip::MipContext::Create(mipConfiguration);

    auto profileObserver = make_shared<ProfileObserver>();                     // Observer object
    auto authDelegateImpl = make_shared<AuthDelegateImpl>("64c62ae2-01c3-44af-871d-84d7cb1d039f"); // Authentication delegate object (App ID)                 
    auto consentDelegateImpl = make_shared<ConsentDelegateImpl>();             // Consent delegate object

    // Construct/initialize profile object
    FileProfile::Settings profileSettings(
        mMipContext,
        mip::CacheStorageType::OnDisk,
        // authDelegateImpl,
        consentDelegateImpl,
        profileObserver);

    // Set up promise/future connection for async profile operations; load profile asynchronously
    auto profilePromise = make_shared<promise<shared_ptr<FileProfile>>>();
    auto profileFuture = profilePromise->get_future();

    try
    {
        mip::FileProfile::LoadAsync(profileSettings, profilePromise);
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... are the Settings and ApplicationInfo objects populated correctly?\n\n" << e.what() << "'\n";

        system("pause");
        return 1;
    }



    auto profile = profileFuture.get();

    // Construct/initialize engine object
    FileEngine::Settings engineSettings(
        mip::Identity("mstest_mugupt@renchow.onmicrosoft.com"), // Engine identity (account used for authentication)
        authDelegateImpl,
        "My App State",                  // User-defined engine state
        "en-US");                          // Locale (default = en-US)

// Set up promise/future connection for async engine operations; add engine to profile asynchronously
    auto enginePromise = make_shared<promise<shared_ptr<FileEngine>>>();
    auto engineFuture = enginePromise->get_future();
    profile->AddEngineAsync(engineSettings, enginePromise);
    std::shared_ptr<FileEngine> engine;
    try
    {
        engine = engineFuture.get();
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... is the access token incorrect/expired?\n\n" << e.what() << "'\n";

        system("pause");
        return 1;
    }

    
    // List sensitivity labels
    cout << "\nSensitivity labels for your organization:\n";
    auto labels = engine->ListSensitivityLabels();
    for (const auto& label : labels)
    {
        cout << label->GetName() << " : " << label->GetId() << endl;

        for (const auto& child : label->GetChildren())
        {
            cout << "->  " << child->GetName() << " : " << child->GetId() << endl;
        }
    }
    system("pause");
    


    
    // Set up async FileHandler for input file operations
    string inputFilePath = "C:\\Users\\jad\\Desktop\\MIP_Test_PDF.pdf";
    string actualFilePath = "C:\\Users\\jad\\Desktop\\MIP_Test_PDF.pdf";
    std::shared_ptr<FileHandler> handler;
    try
    {
        auto handlerPromise = std::make_shared<std::promise<std::shared_ptr<FileHandler>>>();
        auto handlerFuture = handlerPromise->get_future();
        engine->CreateFileHandlerAsync(
            inputFilePath,
            actualFilePath,
            true,
            std::make_shared<FileHandlerObserver>(),
            handlerPromise);
        handler = handlerFuture.get();
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... did you specify a valid input file path?\n\n" << e.what() << "'\n";
        system("pause");
        return 1;
    }

    auto protectionSettings = new ProtectionSettings();
    // Set a label on input file
    try
    {
        string labelId = "7316dcde-4749-48b3-894e-a1aa93a26114";
        cout << "\nApplying Label ID " << labelId << " to " << inputFilePath << endl;
        mip::LabelingOptions labelingOptions(mip::AssignmentMethod::PRIVILEGED);
        handler->SetLabel(engine->GetLabelById(labelId), labelingOptions, *protectionSettings);
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... did you specify a valid label ID?\n\n" << e.what() << "'\n";
        system("pause");
        return 1;
    }

    // Commit changes, save as a different/output file
    string filePathOut = "C:\\Users\\jad\\Desktop\\Labelled_MIP_Test_PDF.pdf";
    try
    {
        cout << "Committing changes" << endl;
        auto commitPromise = std::make_shared<std::promise<bool>>();
        auto commitFuture = commitPromise->get_future();
        handler->CommitAsync(filePathOut, commitPromise);
        if (commitFuture.get())
        {
            cout << "\nLabel committed to file: " << filePathOut << endl;
        }
        else
        {
            cout << "Failed to label: " + filePathOut << endl;
            return 1;
        }
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... did you specify a valid commit file path?\n\n" << e.what() << "'\n";
        system("pause");
        return 1;
    }
    system("pause");

    // Set up async FileHandler for output file operations
    actualFilePath = "C:\\Users\\jad\\Desktop\\MIP_Test_Excel.xlsx";
    try
    {
        auto handlerPromise = std::make_shared<std::promise<std::shared_ptr<FileHandler>>>();
        auto handlerFuture = handlerPromise->get_future();
        engine->CreateFileHandlerAsync(
            filePathOut,
            actualFilePath,
            true,
            std::make_shared<FileHandlerObserver>(),
            handlerPromise);

        handler = handlerFuture.get();
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... did you specify a valid output file path?\n\n" << e.what() << "'\n";
        system("pause");
        return 1;
    }

    // Get the label from output file
    try
    {
        cout << "\nGetting the label committed to file: " << filePathOut << endl;
        auto label = handler->GetLabel();
        cout << "Name: " + label->GetLabel()->GetName() << endl;
        cout << "Id: " + label->GetLabel()->GetId() << endl;
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... did you specify a valid label ID?\n\n" << e.what() << "'\n";
        system("pause");
        return 1;
    }
    system("pause");
    

    /*
    //Encrypt/Decrypt text:
    string templateId = "7316dcde-4749-48b3-894e-a1aa93a26114";//Template ID from previous QuickStart e.g. "bb7ed207-046a-4caf-9826-647cff56b990"
    string inputText = "cipher text";//Sample Text

    //Refer to ProtectionDescriptor docs for details on creating the descriptor
    auto descriptorBuilder = mip::ProtectionDescriptorBuilder::CreateFromTemplate(templateId);
    const std::shared_ptr<mip::ProtectionDescriptor>& descriptor = descriptorBuilder->Build();

    //Create Publishing settings using a descriptor
    mip::ProtectionHandler::PublishingSettings publishingSettings = mip::ProtectionHandler::PublishingSettings(descriptor);

    // Set up promise/future connection for async protection engine operations
    auto protectionEnginePromise = make_shared<promise<shared_ptr<ProtectionEngine>>>();
    auto protectionEngineFuture = protectionEnginePromise->get_future();
    std::shared_ptr<ProtectionEngine> protectionEngine;
    try
    {
        protectionEngine = protectionEngineFuture.get();
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... is the access token incorrect/expired?\n\n" << e.what() << "'\n";

        system("pause");
        return 1;
    }

    std::shared_ptr<ProtectionHandler> publishingHandler;
    try
    {
        auto protectionHandlerPromise = std::make_shared<std::promise<std::shared_ptr<ProtectionHandler>>>();
        auto protectionHandlerFuture = protectionHandlerPromise->get_future();

        //Create a publishing protection handler using Protection Descriptor
        auto handlerObserver = std::make_shared<ProtectionHandlerObserver>();
        protectionEngine->CreateProtectionHandlerForPublishingAsync(publishingSettings, handlerObserver, protectionHandlerPromise);
        publishingHandler = protectionHandlerFuture.get();
    }
    catch (const std::exception& e)
    {
        cout << "An exception occurred... is the access token incorrect/expired?\n\n" << e.what() << "'\n";

        system("pause");
        return 1;
    }

    std::vector<uint8_t> inputBuffer(inputText.begin(), inputText.end());

    //Show action plan
    cout << "Applying Template ID " + templateId + " to: " << endl << inputText << endl;

    //Encrypt buffer using Publishing Handler
    std::vector<uint8_t> encryptedBuffer;
    encryptedBuffer.resize(static_cast<size_t>(publishingHandler->GetProtectedContentLength(inputText.size(), true)));

    publishingHandler->EncryptBuffer(0,
        &inputBuffer[0],
        static_cast<int64_t>(inputBuffer.size()),
        &encryptedBuffer[0],
        static_cast<int64_t>(encryptedBuffer.size()),
        true);

    std::string encryptedText(encryptedBuffer.begin(), encryptedBuffer.end());
    cout << "Encrypted Text :" + encryptedText;

    //Show action plan
    cout << endl << "Decrypting string: " << endl << endl;

    //Generate publishing licence, so it can be used later to decrypt text.
    auto serializedPublishingLicense = publishingHandler->GetSerializedPublishingLicense();

    //Use same PL to decrypt the encryptedText.
    auto cHandlerPromise = std::make_shared<std::promise<std::shared_ptr<ProtectionHandler>>>();
    auto cHandlerFuture = cHandlerPromise->get_future();
    shared_ptr<ProtectionHandlerObserver> cHandlerObserver = std::make_shared<ProtectionHandlerObserver>();

    //Create consumption settings using serialised publishing licence.
    mip::ProtectionHandler::ConsumptionSettings consumptionSettings = mip::ProtectionHandler::ConsumptionSettings(serializedPublishingLicense);
    protectionEngine->CreateProtectionHandlerForConsumptionAsync(consumptionSettings, cHandlerObserver, cHandlerPromise);

    auto consumptionHandler = cHandlerFuture.get();

    //Use consumption handler to decrypt the text.
    std::vector<uint8_t> decryptedBuffer(static_cast<size_t>(encryptedText.size()));

    int64_t decryptedSize = consumptionHandler->DecryptBuffer(
        0,
        &encryptedBuffer[0],
        static_cast<int64_t>(encryptedBuffer.size()),
        &decryptedBuffer[0],
        static_cast<int64_t>(decryptedBuffer.size()),
        true);

    decryptedBuffer.resize(static_cast<size_t>(decryptedSize));

    std::string decryptedText(decryptedBuffer.begin(), decryptedBuffer.end());

    // Output decrypted content. Should match original input text.
    cout << "Decrypted Text :" + decryptedText << endl;
    */


    // Application shutdown. Null out profile and engine, call ReleaseAllResources();
    // Application may crash at shutdown if resources aren't properly released.
    // handler = nullptr; // This will be used in later quick starts.
    engine = nullptr;
    profile = nullptr;
    handler = nullptr;
    // publishingHandler = nullptr;
    // consumptionHandler = nullptr;
    mMipContext->ShutDown();
    mMipContext = nullptr;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
