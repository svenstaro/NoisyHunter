#include <cmath>
#include <vector>

#define PI 3.14159264

namespace Engine {
namespace Math {
	float BounceBoth(const float value1, const float value2, const float amount, const float overshoot = 20);
	float BounceIn(const float value1, const float value2, const float amount, const float overshoot = 20);
	float BounceOut(const float value1, const float value2, const float amount, const float overshoot = 20);
	float Clamp(const float value, const float minval, const float maxval);
	float Hermite(const float value1, const float tangent1, const float value2, const float tangent2, const float amount);
	float Lerp(const float value1, const float value2, const float amount);
	float Lerp2(const float value1, const float value2, const float amount);
	float MultiLerp(const std::vector<float>& values, const float amount);
	float NextPow2(const float value);
	float SmoothStep(const float value1, const float value2, const float amount);
	float SmoothStep2(const float value1, const float value2, const float amount);
	float DegToRad(const float degrees);
	float RadToDeg(const float radians);
} // namespace Math
} // namespace Engine
