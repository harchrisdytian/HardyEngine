#include "Bindable.h"

ID3D11DeviceContext* Bindable::GetContext(Graphics& _graphics)
{
	return _graphics.deviceContext.Get();
}

ID3D11Device* Bindable::GetDevice(Graphics& _graphics)
{
	return _graphics.device.Get();
}
DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx)
{

	return gfx.infoManager;


}
