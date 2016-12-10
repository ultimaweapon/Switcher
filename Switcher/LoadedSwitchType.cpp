#include "PCH.h"
#include "LoadedSwitchType.h"

std::weak_ptr<switch_type_map> switch_types;

loaded_switch_type::loaded_switch_type(ISwitchType *stype, SwitchTypeProperties *props) :
	stype(stype),
	props(props)
{
	_ASSERTE(props);
}

SwitchTypeProperties * loaded_switch_type::properties() const
{
	return props;
}
