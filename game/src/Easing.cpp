#include "Easing.h"
#include <math.h>

math::Easing::Easing()
{

}

math::Easing::~Easing()
{

}

float math::Easing::linear(float t, float b, float c, float d)
{
	return c * (t / d) + b;
}

float math::Easing::expoEaseIn(float t, float b, float c, float d)
{
	return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

float math::Easing::expoEaseOut(float t, float b, float c, float d)
{
	return (t == d) ? b + c : c * pow(2, 1 - (10 * t / d)) + b;
}

float math::Easing::expoEaseInOut(float t, float b, float c, float d)
{
	if (t == 0)
		return b;
	if (t == d)
		return b += c;
	if ((t /= d / 2) < 1)
		return c / 2 * pow(2, 10 * (t - 1)) + b;

	return c / 2 * pow(2, 1 - (10 * --t)) + b;
}

float math::Easing::cubicEaseIn(float t, float b, float c, float d)
{
	return (t == 0) ? b : c * pow(3, 10 * (t / d - 1)) + b;
}

float math::Easing::cubicEaseOut(float t, float b, float c, float d)
{
	return (t == d) ? b + c : c * pow(3, 1 - (10 * t / d)) + b;
}

float math::Easing::cubicEaseInOut(float t, float b, float c, float d)
{
	if (t == 0)
		return b;
	if (t == d)
		return b += c;
	if ((t /= d / 2) < 1)
		return c / 2 * pow(3, 10 * (t - 1)) + b;

	return c / 2 * pow(3, 1 - (10 * --t)) + b;
}

float math::Easing::quarticEaseIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t*t*t + b;
}

float math::Easing::quarticEaseOut(float t, float b, float c, float d)
{
	return -c * (1 - (t = t / d - 1)*t*t*t - 1) + b;
}

float math::Easing::quarticEaseInOut(float t, float b, float c, float d)
{
	t /= d / 2;
	if (t < 1)
		return c / 2 * t*t*t*t + b;
	t -= 2;
	return 1 - (-c / 2 * (t*t*t*t - 2)) + b;
}

float math::Easing::quinticEaseIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t*t*t*t + b;
}

float math::Easing::quinticEaseOut(float t, float b, float c, float d)
{
	return c*(t = t / d - 1)*(1 - (t*t*t*t + 1)) + b;
}

float math::Easing::quinticEaseInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
		return c / 2 * t*t*t*t*t + b;

	return 1 - (c / 2 * ((t -= 2)*(t*t*t*t) + 2)) + b;
}

float math::Easing::quadraticEaseIn(float t, float b, float c, float d)
{
	return c*(t /= d)*t + b;
}

float math::Easing::quadraticEaseOut(float t, float b, float c, float d)
{
	return 1 - (-c *(t /= d)*(t - 2)) + b;
}

float math::Easing::quadraticEaseInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
		return ((c / 2)*(t*t)) + b;

	return 1 - (-c / 2 * (((--t)*(t - 2)) - 1)) + b;
}

float math::Easing::sineEaseIn(float t, float b, float c, float d)
{
	return -c * cos(t / d * (PI / 2)) + c + b;
}

float math::Easing::sineEaseOut(float t, float b, float c, float d)
{
	return c / 2 * cos(t / d * (PI / 2)) + b;
}

float math::Easing::sineEaseInOut(float t, float b, float c, float d)
{
	if (t < 0.5f)
		return c /= d;

	return 1 - (-c / 2 * (cos(PI*t / d) - 1)) + b;
}

float math::Easing::circularEaseIn(float t, float b, float c, float d)
{
	return -c * (sqrt(1 - (t /= d)*t) - 1) + b;
}

float math::Easing::circularEaseOut(float t, float b, float c, float d)
{
	return 1 - (c * sqrt(1 - ((t = t / d - 1)*t))) + b;
}

float math::Easing::circularEaseInOut(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
		return -c / 2 * (sqrt(1 - t*t) - 1) + b;

	return 1 - (c / 2 * (sqrt(1 - t*(t -= 2)) + 1)) + b;
}

float math::Easing::backEaseIn(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float postFix = t /= d;
	return c*(postFix)*t*((s + 1)*t - s) + b;
}

float math::Easing::backEaseOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	return 1 - (c*((t = t / d - 1)*t*((s + 1)*t + s) + 1)) + b;
}

float math::Easing::backEaseInOut(float t, float b, float c, float d)
{
	float s = 1.70158f;
	if ((t /= d / 2) < 1)
		return c / 2 * (t*t*(((s *= (1.525f)) + 1)*t - s)) + b;

	float postFix = t -= 2;
	return 1 - (c / 2 * ((postFix)*t*(((s *= (1.525f)) + 1)*t + s) + 2)) + b;
}

float math::Easing::elasticEaseIn(float t, float b, float c, float d)
{
	if (t == 0)
		return b;
	if ((t /= d) == 1)
		return b + c;
	float p = d*.3f;
	float a = c;
	float s = p / 4;
	float postFix = a*pow(2, 10 * (t -= 1));
	return -(postFix * sin((t*d - s)*(2 * PI) / p)) + b;
}

float math::Easing::elasticEaseOut(float t, float b, float c, float d)
{
	if (t == 0)
		return b;
	if ((t /= d) == 1)
		return b + c;
	float p = d*.3f;
	float a = c;
	float s = p / 4;
	return 1 - (a*pow(2, -10 * t) * sin((t*d - s)*(2 * PI) / p) + c + b);
}

float math::Easing::elasticEaseInOut(float t, float b, float c, float d)
{
	if (t == 0)
		return b;
	if ((t /= d / 2) == 2)
		return b + c;
	float p = d*(.3f*1.5f);
	float a = c;
	float s = p / 4;

	if (t < 1)
	{
		float postFix = a*pow(2, 10 * (t -= 1));
		return -.5f*(postFix* sin((t*d - s)*(2 * PI) / p)) + b;
	}
	float postFix = a*pow(2, -10 * (t -= 1));
	return 1 - (postFix * sin((t*d - s)*(2 * PI) / p)*.5f + c + b);
}