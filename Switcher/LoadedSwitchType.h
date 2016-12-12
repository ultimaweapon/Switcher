#pragma once

#include "SwitchTypeProperties.h"

class loaded_switch_type final
{
public:
	loaded_switch_type(ISwitchType *stype, SwitchTypeProperties *props);
	loaded_switch_type(const loaded_switch_type&) = delete;

	loaded_switch_type& operator=(const loaded_switch_type&) = delete;

	SwitchTypeProperties * properties() const;
	ISwitchType * switch_type() const;
private:
	CComPtr<ISwitchType> stype;
	CComPtr<SwitchTypeProperties> props;
};
