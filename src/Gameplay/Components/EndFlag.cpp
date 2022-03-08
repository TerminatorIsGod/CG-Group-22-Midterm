#include "Gameplay/Components/EndFlag.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"
#include "Application/Application.h"
#include "Gameplay/Scene.h"
#include <Gameplay/Components/GUI/GuiPanel.h>

EndFlag::EndFlag() :
	IComponent()
{ }
EndFlag::~EndFlag() = default;

void EndFlag::Awake() {

}

void EndFlag::Update(float deltaTime) {

	glm::vec3 pos = GetGameObject()->GetPosition();

	if (isMoving && isLeft) {
		if (pos.x >= x1) {
			pos.x -= moveSpeed * deltaTime;
		}
		else {
			isLeft = false;
		}
	}
	else {
		if (pos.x <= x2) {
			pos.x += moveSpeed * deltaTime;
		}
		else {
			isLeft = true;
		}
	}
}


void EndFlag::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	LOG_INFO("Body has entered {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);

	if (body->GetGameObject()->Name == "Player") {
		Gameplay::Scene* _scene = GetGameObject()->GetScene();
		_scene->FindObjectByName("EndScreen")->Get<GuiPanel>()->IsEnabled = true;
	}

	_playerInTrigger = true;
}

void EndFlag::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) {
	LOG_INFO("Body has left {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);
	_playerInTrigger = false;
}

void EndFlag::RenderImGui() { }

nlohmann::json EndFlag::ToJson() const {
	return {
		{ "x1", x1},
		{ "x2", x2}
	};
}

EndFlag::Sptr EndFlag::FromJson(const nlohmann::json& blob) {
	EndFlag::Sptr result = std::make_shared<EndFlag>();
	result->x1 = JsonGet(blob, "x1", result->x1);
	result->x2 = JsonGet(blob, "x2", result->x2);
	return result;
}
