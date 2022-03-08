#include "Gameplay/Components/DayAndNight.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"
#include "Application/Application.h"

DayAndNight::DayAndNight() :
	IComponent(),
	radius(100.0f),
	timer(0.0f)
{ }
DayAndNight::~DayAndNight() = default;

void DayAndNight::Awake() {
	startPos = GetGameObject()->GetPosition();
}

void DayAndNight::Update(float deltaTime) {
	
	timer += (deltaTime / 100);
	GetGameObject()->SetPostion(glm::vec3(startPos.x, startPos.y + sin(timer) * radius, startPos.z + cos(timer) * radius));

}

void DayAndNight::RenderImGui() { }

nlohmann::json DayAndNight::ToJson() const {
	return {
		{ "radius", radius}
	};
}

DayAndNight::Sptr DayAndNight::FromJson(const nlohmann::json& blob) {
	DayAndNight::Sptr result = std::make_shared<DayAndNight>();
	result->radius = JsonGet(blob, "radius", result->radius);
	return result;
}
