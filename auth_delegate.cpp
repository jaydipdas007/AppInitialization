#include "auth_delegate.h"
#include <iostream>
using std::cout;
using std::cin;
using std::string;

bool AuthDelegateImpl::AcquireOAuth2Token(const mip::Identity& identity, const OAuth2Challenge& challenge, OAuth2Token& token)
{
    // Acquire a token manually, reuse previous token if same authority/resource. In production, replace with token acquisition code.
    string authority = challenge.GetAuthority();
    string resource = challenge.GetResource();
    if (mToken == "" || (authority != mAuthority || resource != mResource))
    {
        cout << "\nRun the PowerShell script to generate an access token using the following values, then copy/paste it below:\n";
        cout << "Set $authority to: " + authority + "\n";
        cout << "Set $resourceUrl to: " + resource + "\n";
        cout << "Sign in with user account: " + identity.GetEmail() + "\n";
        cout << "Enter access token: ";
        cin >> mToken;
        mAuthority = authority;
        mResource = resource;
        system("pause");
    }

    // Pass access token back to MIP SDK
    token.SetAccessToken(mToken);

    // True = successful token acquisition; False = failure
    return true;
}