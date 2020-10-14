#pragma once

#include <string>
#include <cassert>

namespace inceptionengine
{
	class PathHelper
	{
	public:
		enum class FileType
		{
			File,
			Directory,
			SoftLink,
			HardLink
		};
		static std::string Normalize(std::string const& path)
		{
			std::string copy = path;
			for (auto& c : copy)
			{
				if (c == '\\')
				{
					c = '/';
				}
			}
			return copy;
		}

		static void SetEngineDirectory(std::string& path)
		{
			mEnginePath = path;
		}

		static bool IsAbsolutePath(std::string const& path)
		{
			return path.length() >= 2 && isupper(path[0]) && path[1] == ':';
		}

		static bool IsFileExist(std::string const& path)
		{
			return true;
		}

		static FileType GetFileType(std::string const& path)
		{
			return FileType::File;
		}

		static std::string GetFileExtension(std::string const& path)
		{
			for (int i = path.length() - 1; i >= 0; i--)
			{
				if (path[i] == '.')
				{
					return path.substr(i + 1, path.length());
				}
			}
			return "";
		}

		static std::string GetAbsolutePath(std::string const& path)
		{
			if (IsAbsolutePath(path)) return path;
			return mEnginePath + path;
		}

		static std::string GetEnginePath(std::string const& path)
		{
			int location = -1;
			for (int i = 0; i < path.length(); i++)
			{
				if (path[i] == '\\')
				{
					for (int j = i + 1; j < path.length(); j++)
					{
						if (path[j] == '\\')
						{
							std::string word = path.substr(i + 1, j - i - 1);
							if (word == std::string("build_x64"))
							{
								location = i;
							}
							break;
						}
					}
				}
			}
			assert(location != -1);
			return path.substr(0, location + 1);
		}

	private:
		/*
		This should be the path of the folder "Inception Engine", 
		Examples are D:\\InceptionEngine 
		*/
		static std::string mEnginePath;  
	};


}