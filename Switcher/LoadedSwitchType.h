#pragma once

#include "SwitchTypeProperties.h"

class loaded_switch_type final
{
public:
	loaded_switch_type(ISwitchType *stype, SwitchTypeProperties *props);
	loaded_switch_type(const loaded_switch_type&) = delete;

	loaded_switch_type& operator=(const loaded_switch_type&) = delete;

	SwitchTypeProperties * properties() const;
private:
	CComPtr<ISwitchType> stype;
	CComPtr<SwitchTypeProperties> props;
};

typedef std::unordered_map<GUID, std::shared_ptr<loaded_switch_type>> switch_type_map;
extern std::weak_ptr<switch_type_map> switch_types;
