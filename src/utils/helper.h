#ifndef HELPER_H
#define HELPER_H

namespace SSR 
{

class Helper 
{

public:
	/**
	* This function calculates the transfered linear_value to dB. This is done
	* with the formula: `20 * log10(linear_value)`
	* 
	* @param 		linear_value 		The linear value that shall be converted
	*									to dB.
	* @return  		the linear value converted to dB.
	**/
	static float linear_to_dB(const float linear_value);

	/**
	* This function calculates the transfered dB_value to linear. This is done
	* with the formula: `10^(dB_value / 20)`
	*
	* When you ask yourself: Why 20? I have to refer to the SSR developers. 
	* Long story short: They decided to assign 1V to the reference value:
	* `Bel = log10 * (P / P0) | P0 -> Reference Value`
	*
	* @param 		dB_value 			The dB value that shall be converted to
	*									linear. 
	* @return 		the dB value converted to linear.
	**/
	static float dB_to_linear(const float dB_value);

	//TODO: Documentation
	static std::string get_environment_variable(const std::string& key);
};

}

#endif
