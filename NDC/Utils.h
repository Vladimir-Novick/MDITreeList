#pragma once

namespace NDC {

	class Utils
	{
	public:		

		/// <summary>
		/// Checking background color and return optimal font color
		/// </summary>
		/// <param name="color">The color.</param>
		/// <returns></returns>
		static COLORREF CheckTextColor(COLORREF backgroundColor);
	};
}

