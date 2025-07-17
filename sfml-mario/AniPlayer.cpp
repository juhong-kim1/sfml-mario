#include "stdafx.h"
#include "AniPlayer.h"
#include "HitBox.h"
#include "GroundTileMap.h"
#include "SceneDev2.h"
#include "Block.h"
#include "Enemy.h"
#include "Flag.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name), mario(Mario::Small)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);

	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	//body.setScale({ 1.f, 1.f });
	//SetPosition({ 100.f, 416.f });
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	mario = Mario::Small;
	animator.Play("animations/idle.csv");
	SetOrigin(Origins::BC);

	currentJumpTime = 0;

	isMarioDie = false;
	deathProcessed = false;
	dieCurrentTime = 0.0f;
	isMarioDown = false;
	isFlagCleared = false;
	clearStep = 0;
	clearTimer = 0.0f;
	formChangeTime = 0.0f;

	body.setScale({ 1.f, 1.f });
	SetPosition({ 100.f, 416.f });
}

void AniPlayer::Update(float dt)
{
	if (isFlagCleared)
	{
		animator.Update(dt);
		clearTimer += dt;

		if (clearStep == 1)
		{
			if (mario == Mario::Small)
			{
				animator.Play("animations/flag.csv");
			}
			else if (mario == Mario::Big)
			{
				animator.Play("animations/big_flag.csv");
			}
			position.y += 80 * dt;
			SetPosition(position);

			if (position.y >= 416.f)
			{
				clearStep = 2;
				clearTimer = 0.0f;
			}
		}
		else if (clearStep == 2)
		{
			if (mario == Mario::Small)
			{
				animator.Play("animations/run.csv");
			}
			else if (mario == Mario::Big)
			{
				animator.Play("animations/big_run.csv");
			}

			position.x += 60 * dt;
			SetPosition(position);

			if (clearTimer >= 3.0f)
			{
				clearStep = 3;
			}
		}
		else if (clearStep == 3)
		{
			animator.Play("animations/idle.csv");
			SetOrigin(Origins::BC);
			SCENE_MGR.ChangeScene(SceneIds::Dev2);
		}

		hitBox.UpdateTransform(body, body.getLocalBounds());
		return;
	}

	if (isInvincible)
	{
		invincibleTime += dt;
		if (invincibleTime < maxInvincibleTime)
		{
			speed = 80.f;
			float blinkTime = fmod(invincibleTime, 0.1f);
			if (blinkTime < 0.05f)
			{
				animator.Play("animations/big_idle.csv");
			}
			else
			{
				animator.Play("animations/idle.csv");
			}
			SetOrigin(Origins::BC);
		}
		else
		{
			isInvincible = false;
			invincibleTime = 0.0f;
			speed = 220.f;
		}
	}
	if (isFormChanging)
	{
		formChangeTime += dt;

		if (formChangeTime >= formChangeMaxTime)
		{
			mario = Mario::Big;
			animator.Play("animations/big_idle.csv");
			SetOrigin(Origins::BC);
			isFormChanging = false;
			formChangeTime = 0.f;
		}
		else
		{
			float blinkTime = fmod(formChangeTime, 0.2f);
			if (blinkTime < 0.1f)
			{
				animator.Play("animations/idle.csv");
			}
			else
			{
				animator.Play("animations/big_idle.csv");
			}
			SetOrigin(Origins::BC);
		}
	}


	if (isMarioDie)
	{
		animator.Update(dt);

		dieCurrentTime += dt;

		if (dieCurrentTime < 0.3f)
		{
			velocity.y = -200.f;
		}
		else
		{
			velocity.y += gravity.y * dt;
		}

		position += velocity * dt;
		SetPosition(position);
	}
	if (!isMarioDie)
	{
		animator.Update(dt);

		float h = 0.f;

		if (!isMarioDown)
		{
			h = InputMgr::GetAxis(Axis::Horizontal);
			velocity.x = h * speed;
		}
		else
		{
			float friction = 200.f;

			if (velocity.x > 0)
			{
				velocity.x -= friction * dt;
				if (velocity.x < 0) velocity.x = 0;
			}
			else if (velocity.x < 0)
			{
				velocity.x += friction * dt;
				if (velocity.x > 0) velocity.x = 0;
			}
		}

		if (InputMgr::GetKey(sf::Keyboard::Space) && currentJumpTime < maxJumpTime && velocity.y < 0)
		{
			velocity += gravity * 0.3f * dt;
			currentJumpTime += dt;
		}
		else
		{
			velocity += gravity * dt;
		}

		isWallCheck();
		isBlockCheck();
		isEnemyCheck();
		isFlagCheck();

		SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
		if (scene)
		{
			auto items = scene->GetItems();
			sf::FloatRect playerBounds = body.getGlobalBounds();

			for (auto* item : items)
			{
				if (item->GetActive() && playerBounds.intersects(item->GetHitBoxMushroom()))
				{
					if (item->GetItemType() == ItemType::Mushroom && mario == Mario::Small && !isFormChanging)
					{
						/*animator.Play("animations/big_idle.csv");
						SetOrigin(Origins::BC);*/
						mario = Mario::Big;
						isFormChanging = true;
					}
					item->SetActive(false);
				}
			}
		}

		position += velocity * dt;

		isGroundedCheck();
		SetPosition(position);

		if (h != 0.f && !isFormChanging)
		{
			SetScale(h > 0.f ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(-1.f, 1.f));
		}

		// Ani
		switch (mario)
		{
		case Mario::Small:
			if (animator.GetCurrentClipId() == "Idle")
			{
				if (h != 0.f)
				{
					animator.Play("animations/run.csv");
				}
			}
			else if (animator.GetCurrentClipId() == "Run")
			{
				if (h > 0.f && InputMgr::GetKeyDown(sf::Keyboard::A))
				{
					animator.Play("animations/stop.csv");
				}
				if (h < 0.f && InputMgr::GetKeyDown(sf::Keyboard::D))
				{
					animator.Play("animations/stop.csv");
				}
				if (h == 0.f)
				{
					animator.Play("animations/idle.csv");
				}
			}
			else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
			{
				if (h == 0.f)
				{
					animator.Play("animations/idle.csv");
				}
				else
				{
					animator.Play("animations/run.csv");
				}
			}
			if (animator.GetCurrentClipId() == "Stop")
			{
				if (velocity.x < 0.3f && velocity.x > -0.3f)
				{
					animator.Play("animations/idle.csv");
				}
			}
			if (InputMgr::GetKeyDown(sf::Keyboard::Space) && isGrounded)
			{
				currentJumpTime = 0.0f;
				isGrounded = false;
				velocity.y = -340.f;
				animator.Play("animations/jump.csv");
			}

			break;
		case Mario::Big:
			if (animator.GetCurrentClipId() == "Big_Idle")
			{
				if (h != 0.f)
				{
					animator.Play("animations/big_run.csv");
				}
			}
			else if (animator.GetCurrentClipId() == "Big_Run")
			{
				if (h > 0.f && InputMgr::GetKeyDown(sf::Keyboard::A))
				{
					animator.Play("animations/big_stop.csv");
				}
				if (h < 0.f && InputMgr::GetKeyDown(sf::Keyboard::D))
				{
					animator.Play("animations/big_stop.csv");
				}
				if (h == 0.f)
				{
					animator.Play("animations/big_idle.csv");
				}
			}
			else if (animator.GetCurrentClipId() == "Big_Jump" && isGrounded)
			{
				if (h == 0.f)
				{
					animator.Play("animations/big_idle.csv");
				}
				else
				{
					animator.Play("animations/big_run.csv");
				}
			}
			if (animator.GetCurrentClipId() == "Big_Stop")
			{
				if (velocity.x < 0.3f && velocity.x > -0.3f)
				{
					animator.Play("animations/big_idle.csv");
				}
			}
			if (InputMgr::GetKeyDown(sf::Keyboard::Space) && isGrounded)
			{
				if (currentJumpTime < maxJumpTime)
				{
					currentJumpTime += dt;
					isGrounded = false;
					velocity.y = -340.f;
					animator.Play("animations/big_jump.csv");
				}
			}
			if (InputMgr::GetKey(sf::Keyboard::S))
			{
				//speed 변경해야할듯?
				animator.Play("animations/big_sitdown.csv");
				SetOrigin(Origins::BC);
				//velocity.x = 0.f;
				isMarioDown = true;

			}
			if (InputMgr::GetKeyUp(sf::Keyboard::S))
			{

				animator.Play("animations/big_idle.csv");
				//position.y -= 20;
				SetOrigin(Origins::BC);
				isMarioDown = false;
			}
			break;
		}
	}
		if (body.getPosition().y >= 2000.f && !deathProcessed)
		{
			deathProcessed = true;
			MarioDie();

			isMarioDie = false;
			return;
		}
	
	hitBox.UpdateTransform(body, body.getLocalBounds());
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

sf::FloatRect AniPlayer::GetHitBoxBottom() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	return sf::FloatRect(globalBounds.left + 4.f, globalBounds.top + globalBounds.height - 4.f, globalBounds.width - 8.f, 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxTop() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	return sf::FloatRect(globalBounds.left + 2.f, globalBounds.top, globalBounds.width - 4.f, 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxLeft() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	if (mario == Mario::Small)
	{
		return sf::FloatRect(globalBounds.left, globalBounds.top + 2.f, 4.f, globalBounds.height - 4.f);
	}
	else
	{
		return sf::FloatRect(globalBounds.left, globalBounds.top + 4.f, 6.f, globalBounds.height - 8.f);
	}
}

sf::FloatRect AniPlayer::GetHitBoxRight() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	if (mario == Mario::Small)
	{
		return sf::FloatRect(globalBounds.left + globalBounds.width - 4.f, globalBounds.top + 2.f, 4.f, globalBounds.height - 4.f);
	}
	else
	{
		return sf::FloatRect(globalBounds.left + globalBounds.width - 8.f, globalBounds.top + 4.f, 6.f, globalBounds.height - 8.f);
	}

}

void AniPlayer::isGroundedCheck()
{
	if (!ground)
	{
		return;
	}

	sf::FloatRect bottomBox = GetHitBoxBottom();

	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (scene)
	{
		auto blocks = scene->GetBlocks();

		for (auto* block : blocks)
		{
			sf::FloatRect blockBounds = block->GetGlobalBounds();
			if (bottomBox.intersects(blockBounds) && block->GetActive())
			{
				return;
			}
		}
	}

	if (velocity.y >= 0)
	{
		bool foundGround = false;

		for (float i = bottomBox.left; i < bottomBox.left + bottomBox.width; ++i)
		{
			if (ground->IsGroundAt({ i, bottomBox.top + bottomBox.height }))
			{
				
				int tileY = static_cast<int>((bottomBox.top + bottomBox.height) / 32.f);
				float tileTopY = tileY * 32.f;
				position.y = tileTopY;
				velocity.y = 0;
				isGrounded = true;
				currentJumpTime = 0;
				foundGround = true;
				return;
			}
		}
		if (!foundGround)
		{
			isGrounded = false;
		}
	}
}

void AniPlayer::isWallCheck()
{
	if (!ground)
	{
		return;
	}

	if (velocity.x > 0)
	{
		sf::FloatRect rightBox = GetHitBoxRight();
		for (float y = rightBox.top; y < rightBox.top + rightBox.height; y += 8.f)
		{
			if (ground->IsWallAt({ rightBox.left + rightBox.width, y }))
			{
				velocity.x = 0;
				return;
			}
		}
	}
	else if (velocity.x < 0)
	{
		sf::FloatRect leftBox = GetHitBoxLeft();
		for (float y = leftBox.top; y < leftBox.top + leftBox.height; y += 8.f)
		{
			if (ground->IsWallAt({ leftBox.left, y }))
			{
				velocity.x = 0;
				return;
			}
		}
	}
}

void AniPlayer::isBlockCheck()
{
	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	auto blocks = scene->GetBlocks();

	for (auto* block : blocks)
	{
		sf::FloatRect blockBounds = block->GetGlobalBounds();

		sf::FloatRect bottomBox = GetHitBoxBottom();
		sf::FloatRect topBox = GetHitBoxTop();
		sf::FloatRect leftBox = GetHitBoxLeft();
		sf::FloatRect rightBox = GetHitBoxRight();

		if (velocity.y > 0 && bottomBox.intersects(blockBounds) && block->GetActive())
		{
			//position.y = blockBounds.top;

			velocity.y = 0;
			isGrounded = true;
			currentJumpTime = 0;
			return;
		}
		if (velocity.y < 0 && topBox.intersects(blockBounds) && position.x > blockBounds.left - 4.f && position.x < blockBounds.left + blockBounds.width + 4.f && block->GetActive())
		{
			if (mario == Mario::Big && block->GetBlockType()==BlockType::GeneralBlock)
			{
				block->BlockBreakAnimationStart();
			}
			if (!block->IsShaking())
			{
				velocity.y = 0;
				currentJumpTime = maxJumpTime;
				block->BlockShakeAnimationStart();
				block->ReleaseItem();
				block->CheckEnemiesOnTop();
				return;
			}
		}
		if (velocity.x > 0 && rightBox.intersects(blockBounds) && block->GetActive())
		{
			velocity.x = 0;
			return;
		}
		if (velocity.x < 0 && leftBox.intersects(blockBounds) && block->GetActive())
		{
			velocity.x = 0;
			return;
		}
	}
}

void AniPlayer::isEnemyCheck()
{
	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	auto enemies = scene->GetEnemies();

	sf::FloatRect bottomBox = GetHitBoxBottom();
	sf::FloatRect playerBounds = body.getGlobalBounds();

	for (auto* enemy : enemies)
	{
		if (!enemy->GetActive() || enemy->IsDying() || enemy->IsDyingOnTop())
		{
			continue;
		}

		sf::FloatRect enemyBounds = enemy->GetHitBoxEnemy();

		if (velocity.y > 0 && bottomBox.intersects(enemyBounds) && !isMarioDie && !isInvincible)
		{
			enemy->Die();
			velocity.y = -200.f;
			return;
		}

		else if (playerBounds.intersects(enemyBounds) && invincibleTime == 0)
		{
			if (mario == Mario::Small)
			{
				isMarioDie = true;
				animator.Play("animations/mario_die.csv");
				dieCurrentTime = 0.0f;
				originPosition = GetPosition();
				velocity = { 0.f, 0.f };
				SetOrigin(Origins::BC);
			}
			if (mario == Mario::Big)
			{
				isInvincible = true;
				mario = Mario::Small;
				animator.Play("animations/idle.csv");
				invincibleTime = 0.0f;
				SetOrigin(Origins::BC);
			}
		}
	}
}

void AniPlayer::isFlagCheck()
{
	if (!flag || isFlagCleared)
	{
		return;
	}

	sf::FloatRect flagBounds = flag->GetGlobalBounds();
	sf::FloatRect rightBox = GetHitBoxRight();

	if (rightBox.intersects(flagBounds))
	{
		isFlagCleared = true;
		clearStep = 1;
		clearTimer = 0.0f;
		velocity.x = 0.f;
		position.x += 20.f;
	}
}

void AniPlayer::MarioDie()
{
	SCENE_MGR.ChangeScene(SceneIds::Dev2);
}
