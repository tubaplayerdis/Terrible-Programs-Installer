#pragma once
#include <list>
#include <string>
namespace DebugTools {
	namespace Helpers {
		class StoreApplication
		{
		public:
			StoreApplication(bool available, std::string download, double version);
			bool Aviability;
			std::string Download;
			double Version;
		private:

		};		
	}


	class Startup
	{
		static void Init();
		static std::list<DebugTools::Helpers::StoreApplication> Applications;
	};
}


