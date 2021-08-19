#pragma once

class FileManager : public Singleton<FileManager>
{
public:
	MapGroup ReadFile(const std::wstring& filePath);
	void WriteFile(MapGroup mapGroup, const std::wstring& filePath);
};

