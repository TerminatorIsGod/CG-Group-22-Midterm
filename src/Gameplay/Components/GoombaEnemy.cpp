#include "Gameplay/Components/GoombaEnemy.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"
#include "Application/Application.h"

GoombaEnemy::GoombaEnemy() :
	IComponent(),
	isLeft(true),
	x1(0.0f),
	x2(100.0f),
	moveSpeed(100.0f)
{ }
GoombaEnemy::~GoombaEnemy() = default;

void GoombaEnemy::Awake() {

}

void GoombaEnemy::Update(float deltaTime) {

	glm::vec3 pos = GetGameObject()->GetPosition();

	//std::cout << "isLeft: " << isLeft << " Movespeed" << moveSpeed << " dt" << deltaTime << "\n\n";

	if (isLeft) {
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


void GoombaEnemy::OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body)
{
	LOG_INFO("Body has entered {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);

	if (body->GetGameObject()->Name == "Player") {
		Application& app = Application::Get();
		app.RestartScene("scene");
	}

	_playerInTrigger = true;
}

void GoombaEnemy::OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) {
	LOG_INFO("Body has left {} trigger volume: {}", GetGameObject()->Name, body->GetGameObject()->Name);
	_playerInTrigger = false;
}

void GoombaEnemy::RenderImGui() { }

nlohmann::json GoombaEnemy::ToJson() const {
	return {
		{ "x1", x1},
		{ "x2", x2}
	};
}

GoombaEnemy::Sptr GoombaEnemy::FromJson(const nlohmann::json& blob) {
	GoombaEnemy::Sptr result = std::make_shared<GoombaEnemy>();
	result->x1 = JsonGet(blob, "x1", result->x1);
	result->x2 = JsonGet(blob, "x2", result->x2);
	return result;
}
