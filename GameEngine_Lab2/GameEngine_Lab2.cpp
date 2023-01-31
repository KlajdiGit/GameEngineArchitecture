#include "Asset.h"
#include "AssetController.h"

int main()
{
	AssetController::Instance().Initialize(10000000);
	Asset* asset = AssetController::Instance().GetAsset("Emoji.jpg");
	cout << "Bytes used by imgage.bmp: " << AssetController::Stack->GetBytesUsed() << endl;
}

