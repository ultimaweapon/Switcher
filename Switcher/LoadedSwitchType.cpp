#include "PCH.h"
#include "LoadedSwitchType.h"

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

ISwitchType * loaded_switch_type::switch_type() const
{
	return stype;
}
