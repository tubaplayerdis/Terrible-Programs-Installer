#pragma once
#include <list>
#include <string>
namespace DebugTools {
	namespace Helpers {
		class StoreApplication
		{
		public:
			StoreApplication(std::string name, bool available, std::string download, double version);
			std::string Name;
			bool Aviability;
			std::string Download;
			double Version;
		private:
			
		};		
	}


	class Startup
	{
	public:
		static void Init();
		static bool UpdateAssets;
		static std::list<DebugTools::Helpers::StoreApplication> Applications;
	
	};
}


