$authority = 'https://login.windows.net/common'                   # Specified when SDK calls AcquireOAuth2Token()
$resourceUrl = 'https://aadrm.com'                  # Specified when SDK calls AcquireOAuth2Token()
$appId = '64c62ae2-01c3-44af-871d-84d7cb1d039f'  # App ID of the Azure AD app registration
$redirectUri = 'https://login.microsoftonline.com/common/oauth2/nativeclient'                # Redirect URI of the Azure AD app registration
$response = Get-ADALToken -Resource $resourceUrl -ClientId $appId -RedirectUri $redirectUri -Authority $authority -PromptBehavior:RefreshSession
$response.AccessToken | clip                     # Copy the access token text to the clipboard