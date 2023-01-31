#include "Asset.h"
#include "AssetController.h"

int main()
{
	AssetController::Instance().Initialize(100000000);
	Asset* asset = AssetController::Instance().GetAsset("emoji.jpg");
	cout << "Bytes used by imgae.bmp: " << AssetController::Stack->GetBytesUsed() << endl;
}

