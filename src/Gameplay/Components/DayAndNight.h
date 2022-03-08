#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Physics/TriggerVolume.h"

/// <summary>
/// Provides an example behaviour that uses some of the trigger interface to change the material
/// of the game object the component is attached to when entering or leaving a trigger
/// </summary>
class DayAndNight : public Gameplay::IComponent {

public:
	typedef std::shared_ptr<DayAndNight> Sptr;
	DayAndNight();
	virtual ~DayAndNight();

	// Inherited from IComponent

	virtual void Update(float deltaTime) override;
	virtual void Awake() override;

	virtual void RenderImGui() override;
	virtual nlohmann::json ToJson() const override;
	static DayAndNight::Sptr FromJson(const nlohmann::json& blob);
	MAKE_TYPENAME(DayAndNight);

	float radius = 100.0f;

protected:
	glm::vec3 startPos;
	float timer;
};