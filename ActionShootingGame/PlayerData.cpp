#include "Header.h"

void PlayerData::SaveData(PData data)
{
	this->data = data;
}

PData PlayerData::LoadData()
{
	return data;
}

