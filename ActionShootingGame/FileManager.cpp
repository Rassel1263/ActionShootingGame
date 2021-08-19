#include "Header.h"
#include "FileManager.h"

MapGroup FileManager::ReadFile(const std::wstring& filePath)
{
	MapGroup mg;

	mg.mapName = filePath;

	std::ifstream in(filePath);
	std::string s;

	if (in.is_open()) {
		in.seekg(0, std::ios::end);

		int size = in.tellg();

		s.resize(size);

		in.seekg(0, std::ios::beg);

		in.read(&s[0], size);
	}
	in.close();

	std::string data;
	std::stringstream ss;
	ss.str(s);

	int count = 1;
	mg.mapGroup.resize(count);

	while (ss >> data)
	{
		if (data == "\\n")
		{
			count++;
			mg.mapGroup.resize(count);
			continue;
		}

		mg.mapGroup[count - 1].push_back(data);
	}

	mg.ySize = mg.mapGroup.size();
	mg.xSize = mg.mapGroup[0].size();


	return mg;
}

void FileManager::WriteFile(MapGroup mapGroup, const std::wstring& filePath)
{
	std::ofstream file(filePath);

	for (int y = 0; y < mapGroup.ySize; ++y)
	{
		for (int x = 0; x < mapGroup.xSize; ++x)
		{
			file << mapGroup.mapGroup[y][x] << " ";
		}

		if (y != mapGroup.ySize - 1)
			file << " \\n" << std::endl;
	}

	file.close();
}
