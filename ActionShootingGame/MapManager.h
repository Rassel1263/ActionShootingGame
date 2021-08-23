#pragma once

class MapManager : public Object
{
public:
	MapGroup bck_1_Group;
	MapGroup bck_2_Group;

	std::vector<Sprite> sprites;
	MapManager(const std::wstring map1, const std::wstring map2);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	void BlockCheck(std::string blockNum, RenderInfo ri);
	void Collocate();
	void ChangeMap(const std::wstring map1, const std::wstring map2);
};

