#ifndef _FACTORY_PARAMS_HH
#define _FACTORY_PARAMS_HH

#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

namespace log4cpp
{
	class FactoryParams;
	namespace details
	{
		class base_validator_data
		{
		public:
			base_validator_data(const char* tag, const FactoryParams* params)
				: tag_(tag), params_(params){}

		protected:
			const char* tag_;
			const FactoryParams* params_;

			template<typename T>
			void assign(const std::string& param_value, T& value)
			{
				assign_impl(param_value, value);
			}

			template<typename T>
			void assign_impl(const std::string& param_value, T& value)
			{
				std::stringstream s;
				s << param_value;
				s >> value;
			}

			void assign_impl(const std::string& param_value, std::string& value)
			{
				value = param_value;
			}

			void throw_error(const char* param_name) const
			{
				std::stringstream s;
				s << "Property '" << param_name << "' required to configure " << tag_;
				throw std::runtime_error(s.str());
		
			}
		};


	}
}

#endif // _FACTORY_PARAMS_HH
