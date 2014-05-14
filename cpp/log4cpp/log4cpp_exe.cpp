#include <iostream>
#include <cstdlib>
#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>

int main()
{
	log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &std::cout);
	log4cpp::PatternLayout* pLayout = new log4cpp::PatternLayout();
	pLayout->setConversionPattern("%d:%p %c %x: %m%n");
	osAppender->setLayout(pLayout);

	log4cpp::Category& root = log4cpp::Category::getRoot();
	log4cpp::Category& infoCategory = root.getInstance("infoCategory");
	infoCategory.addAppender(osAppender);
	infoCategory.setPriority(log4cpp::Priority::INFO);

	infoCategory.info("system is runing");
	infoCategory.warn("system is runing");
	infoCategory.error("system is runing");

	log4cpp::Category::shutdown();

	char* endptr;
	char* src = "34";
	std::cout << strtol(src, &endptr, 10) << std::endl;

	return 0;
}
