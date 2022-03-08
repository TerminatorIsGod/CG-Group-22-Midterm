#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"

/// <summary>
/// Provides an example behaviour that uses some of the trigger interface to change the material
/// of the game object the component is attached to when entering or leaving a trigger
/// </summary>
class GoombaEnemy : public Gameplay::IComponent {

public:
	typedef std::shared_ptr<GoombaEnemy> Sptr;
	GoombaEnemy();
	virtual ~GoombaEnemy();

	// Inherited from IComponent

	virtual void OnTriggerVolumeEntered(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void OnTriggerVolumeLeaving(const std::shared_ptr<Gameplay::Physics::RigidBody>& body) override;
	virtual void Update(float deltaTime) override;
	virtual void Awake() override;

	virtual void RenderImGui() override;
	virtual nlohmann::json ToJson() const override;
	static GoombaEnemy::Sptr FromJson(const nlohmann::json& blob);
	MAKE_TYPENAME(GoombaEnemy);

	float x1 = 0.0f;
	float x2 = 0.0f;
	float moveSpeed = 1.0f;

protected:
	bool _playerInTrigger;

	bool isLeft = true;
};